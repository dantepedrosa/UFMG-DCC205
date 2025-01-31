#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class Voo {
   public:
    std::string inputStr;
    std::string origem;
    std::string destino;
    float preco;
    int assentos;
    std::time_t partida;
    std::time_t chegada;
    int numParadas;
    std::time_t duracao;

    Voo(const std::string& linha) {
        inputStr = linha;

        std::istringstream ss(linha);
        std::string partidaStr, chegadaStr;

        ss >> origem >> destino >> preco >> assentos >> partidaStr >>
            chegadaStr >> numParadas;

        if (ss.fail()) {
            std::cerr << "Erro ao processar a linha de entrada: " << linha
                      << std::endl;
            throw std::runtime_error("Erro ao processar a linha de entrada.");
        }

        partida = parseTempo(partidaStr);
        chegada = parseTempo(chegadaStr);
        duracao = chegada - partida;
    }

   private:
    std::time_t parseTempo(const std::string& datetime) {
        std::tm tm = {};

        std::istringstream ss(datetime);
        ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");

        if (ss.fail()) {
            std::cerr << "Erro ao interpretar data/hora: " << datetime
                      << std::endl;
            throw std::runtime_error("Erro ao interpretar data/hora.");
        }

        std::cout << "Data/hora: " << std::put_time(&tm, "%c") << std::endl;

        std::time_t tt = std::mktime(&tm);
        return tt;
    }
};

// Lista encadeada para armazenar voos filtrados
struct ListaVoos {
    Voo* voo;
    ListaVoos* prox;
};

// Nó da árvore sintática
struct No1 {
    char tipo;  // 'O' = operador, 'P' = predicado
    char operador[3], atributo[10], valor[10];
    No1* esq;
    No1* dir;

    No1(const char* op, No1* e, No1* d) {
        tipo = 'O';
        strcpy(operador, op);
        esq = e;
        dir = d;
    }

    No1(const char* atr, const char* op, const char* val) {
        tipo = 'P';
        strcpy(atributo, atr);
        strcpy(operador, op);
        strcpy(valor, val);
        esq = dir = nullptr;
    }
};


struct No {
    std::string valor;
    No* esq;
    No* dir;

    No(std::string v, No* e = nullptr, No* d = nullptr) : valor(v), esq(e), dir(d) {}
};


// Função auxiliar para encontrar a posição do operador de menor precedência fora dos parênteses
int encontrarOperadorPrincipal(std::string expr) {
    int nivelParenteses = 0;
    int pos = -1;
    for (int i = 0; i < expr.size(); i++) {
        if (expr[i] == '(') nivelParenteses++;
        else if (expr[i] == ')') nivelParenteses--;
        else if (nivelParenteses == 0) { 
            if (expr.substr(i, 2) == "&&") return i; 
            if (expr.substr(i, 2) == "==" || expr.substr(i, 2) == "<=") pos = i;
        }
    }
    return pos;
}

// Função para construir a árvore sintática
No* construirArvore(std::string expr) {
    expr = expr.substr(expr.find_first_not_of(" "), expr.find_last_not_of(" ") + 1);

    if (expr[0] == '(' && expr.back() == ')') {
        int count = 0, i;
        for (i = 0; i < expr.size(); i++) {
            if (expr[i] == '(') count++;
            if (expr[i] == ')') count--;
            if (count == 0 && i != expr.size() - 1) break;
        }
        if (i == expr.size() - 1) return construirArvore(expr.substr(1, expr.size() - 2));
    }

    int opPos = encontrarOperadorPrincipal(expr);
    if (opPos == -1) return new No(expr);

    std::string op = (expr.substr(opPos, 2) == "&&") ? "&&" : expr.substr(opPos, 2);
    std::string esq = expr.substr(0, opPos);
    std::string dir = expr.substr(opPos + op.size());

    return new No(op, construirArvore(esq), construirArvore(dir));
}

// Função para imprimir a árvore (pós-ordem)
void imprimirArvore(No* raiz, int nivel = 0) {
    if (!raiz) return;
    imprimirArvore(raiz->dir, nivel + 1);
    std::cout << std::string(nivel * 4, ' ') << raiz->valor << std::endl;
    imprimirArvore(raiz->esq, nivel + 1);
}

// Adiciona um voo filtrado à lista encadeada
ListaVoos* adicionarVoo(ListaVoos* lista, Voo* voo) {
    ListaVoos* novo = new ListaVoos{voo, lista};
    return novo;
}

// Avalia um nó de predicado para um voo
bool avaliarPredicado(No1* no, Voo* voo) {
    if (strcmp(no->atributo, "org") == 0) {
        return strcmp(no->operador, "==") == 0 && voo->origem == no->valor;
    }
    if (strcmp(no->atributo, "dst") == 0) {
        return strcmp(no->operador, "==") == 0 && voo->destino == no->valor;
    }
    if (strcmp(no->atributo, "prc") == 0) {
        return strcmp(no->operador, "<=") == 0 &&
               voo->preco <= std::stof(no->valor);
    }
    if (strcmp(no->atributo, "dur") == 0) {
        return strcmp(no->operador, "<=") == 0 &&
               voo->duracao <= std::stoi(no->valor);
    }
    return false;
}

// Avalia a árvore para um voo
bool avaliarArvore(No1* no, Voo* voo) {
    if (!no) return false;
    if (no->tipo == 'P') return avaliarPredicado(no, voo);
    if (strcmp(no->operador, "&&") == 0)
        return avaliarArvore(no->esq, voo) && avaliarArvore(no->dir, voo);
    if (strcmp(no->operador, "||") == 0)
        return avaliarArvore(no->esq, voo) || avaliarArvore(no->dir, voo);
    return false;
}

// Filtra os voos usando a árvore sintática
ListaVoos* filtrarVoos(No1* raiz, Voo** voos, int numLinhas) {
    ListaVoos* lista = nullptr;
    for (int i = 0; i < numLinhas; i++) {
        if (avaliarArvore(raiz, voos[i])) {
            lista = adicionarVoo(lista, voos[i]);
        }
    }
    return lista;
}

// Imprime a lista de voos filtrados
void imprimirVoos(ListaVoos* lista) {
    while (lista) {
        std::cout << "Voo: " << lista->voo->origem << " -> "
                  << lista->voo->destino << ", Preço: " << lista->voo->preco
                  << std::endl;
        lista = lista->prox;
    }
}

// Libera memória da lista encadeada
void liberarLista(ListaVoos* lista) {
    while (lista) {
        ListaVoos* temp = lista;
        lista = lista->prox;
        delete temp;
    }
}

// Lê voos de um arquivo
void leVoosdeArquivo(std::ifstream& inputFile, Voo** voos, int numLinhas) {
    std::string line;

    for (int i = 0; i < numLinhas; i++) {
        std::getline(inputFile, line);
        voos[i] = new Voo(line);
    }
}

// Lê voos da entrada padrão
void leVoosdeEntrada(Voo** voos, int numLinhas) {
    std::string line;
    for (int i = 0; i < numLinhas; i++) {
        std::getline(std::cin, line);
        voos[i] = new Voo(line);
    }
}

/**/
int main(int argc, char const* argv[]) {
    // Leitura de dados
    // ---------------------------------------------------

    bool fileEnabled = false;
    std::string filePath;

    switch (argc) {
        case 1:
            fileEnabled = false;
            return 1;
        case 2:
            fileEnabled = true;
            filePath = argv[1];
            break;
        default:
            std::cerr << "Uso: " << argv[0] << " <caminho_para_arquivo> [-f]"
                      << std::endl;
            return 1;
    }

    std::string line;
    std::istringstream iss;
    int numLinhas;

    Voo** voos;

    if (fileEnabled) {
        std::ifstream inputFile(filePath);
        std::getline(inputFile, line);
        numLinhas = std::stoi(line);

        voos = new Voo*[numLinhas];
        leVoosdeArquivo(inputFile, voos, numLinhas);

        inputFile.close();
    } else {
        std::getline(std::cin, line);
        numLinhas = std::stoi(line);

        voos = new Voo*[numLinhas];
        leVoosdeEntrada(voos, numLinhas);
    }

    // Criando árvore ((org==DEN)&&(dst==ORD))&&((prc<=500)&&(dur<=8400))
    No1* raiz1 = new No1(
        "&&",
        new No1("&&", new No1("org", "==", "DEN"), new No1("dst", "==", "ORD")),
        new No1("&&", new No1("prc", "<=", "500"), new No1("dur", "<=", "8400"))
    );

    std::string expr = "((org==DEN)&&(dst==ORD))&&((prc<=500)&&(dur<=8400))";
    No* raiz = construirArvore(expr);
    imprimirArvore(raiz);
    ListaVoos* resultado = filtrarVoos(raiz1, voos, numLinhas);
    imprimirVoos(resultado);

    liberarLista(resultado);

    for (int i = 0; i < numLinhas; i++) delete voos[i];
    delete[] voos;

    return 0;
}
