#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

// Estrutura de um voo
class Voo {
public:
    string origem, destino;
    float preco;
    int assentos, numParadas;
    time_t partida, chegada, duracao;

    Voo(const string& linha) {
        istringstream ss(linha);
        string partidaStr, chegadaStr;
        ss >> origem >> destino >> preco >> assentos >> partidaStr >> chegadaStr >> numParadas;

        if (ss.fail()) throw runtime_error("Erro ao processar a linha de entrada.");
        
        partida = parseTempo(partidaStr);
        chegada = parseTempo(chegadaStr);
        duracao = chegada - partida;
    }

private:
    time_t parseTempo(const string& datetime) {
        tm tm = {};
        char tzSign;
        int tzHour, tzMinute;
        istringstream ss(datetime);
        ss >> get_time(&tm, "%Y-%m-%dT%H:%M:%S") >> tzSign >> setw(2) >> tzHour;
        ss.ignore(1);
        ss >> setw(2) >> tzMinute;
        if (ss.fail()) throw runtime_error("Erro ao interpretar data/hora.");
        time_t tt = mktime(&tm);
        int tzOffset = (tzHour * 3600) + (tzMinute * 60);
        return (tzSign == '-') ? tt + tzOffset : tt - tzOffset;
    }
};

// Lista encadeada para armazenar voos filtrados
struct ListaVoos {
    Voo* voo;
    ListaVoos* prox;
};

// Nó da árvore sintática
struct No {
    char tipo;  // 'O' = operador, 'P' = predicado
    char operador[3], atributo[10], valor[10];
    No* esq;
    No* dir;

    No(const char* op, No* e, No* d) {
        tipo = 'O';
        strcpy(operador, op);
        esq = e;
        dir = d;
    }

    No(const char* atr, const char* op, const char* val) {
        tipo = 'P';
        strcpy(atributo, atr);
        strcpy(operador, op);
        strcpy(valor, val);
        esq = dir = nullptr;
    }
};

// Adiciona um voo filtrado à lista encadeada
ListaVoos* adicionarVoo(ListaVoos* lista, Voo* voo) {
    ListaVoos* novo = new ListaVoos{voo, lista};
    return novo;
}

// Avalia um nó de predicado para um voo
bool avaliarPredicado(No* no, Voo* voo) {
    if (strcmp(no->atributo, "org") == 0) {
        return strcmp(no->operador, "==") == 0 && voo->origem == no->valor;
    }
    if (strcmp(no->atributo, "dst") == 0) {
        return strcmp(no->operador, "==") == 0 && voo->destino == no->valor;
    }
    if (strcmp(no->atributo, "prc") == 0) {
        return strcmp(no->operador, "<=") == 0 && voo->preco <= stof(no->valor);
    }
    if (strcmp(no->atributo, "dur") == 0) {
        return strcmp(no->operador, "<=") == 0 && voo->duracao <= stoi(no->valor);
    }
    return false;
}

// Avalia a árvore para um voo
bool avaliarArvore(No* no, Voo* voo) {
    if (!no) return false;
    if (no->tipo == 'P') return avaliarPredicado(no, voo);
    if (strcmp(no->operador, "&&") == 0) return avaliarArvore(no->esq, voo) && avaliarArvore(no->dir, voo);
    if (strcmp(no->operador, "||") == 0) return avaliarArvore(no->esq, voo) || avaliarArvore(no->dir, voo);
    return false;
}

// Filtra os voos usando a árvore sintática
ListaVoos* filtrarVoos(No* raiz, Voo** voos, int numLinhas) {
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
        cout << "Voo: " << lista->voo->origem << " -> " << lista->voo->destino << ", Preço: " << lista->voo->preco << endl;
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
void leVoosdeArquivo(const string& filePath, Voo** voos, int numLinhas) {
    ifstream inputFile(filePath);
    string line;
    for (int i = 0; i < numLinhas; i++) {
        getline(inputFile, line);
        voos[i] = new Voo(line);
    }
    inputFile.close();
}

// Lê voos da entrada padrão
void leVoosdeEntrada(Voo** voos, int numLinhas) {
    string line;
    for (int i = 0; i < numLinhas; i++) {
        getline(cin, line);
        voos[i] = new Voo(line);
    }
}

int main(int argc, char const* argv[]) {
    bool fileEnabled = false;
    string filePath;
    
    if (argc == 2) {
        fileEnabled = true;
        filePath = argv[1];
    } else {
        cerr << "Uso: " << argv[0] << " <caminho_para_arquivo>" << endl;
        return 1;
    }

    string line;
    int numLinhas;
    if (fileEnabled) {
        ifstream inputFile(filePath);
        getline(inputFile, line);
        numLinhas = stoi(line);
        inputFile.close();
    } else {
        getline(cin, line);
        numLinhas = stoi(line);
    }

    Voo* voos[numLinhas];
    if (fileEnabled) {
        leVoosdeArquivo(filePath, voos, numLinhas);
    } else {
        leVoosdeEntrada(voos, numLinhas);
    }

    // Criando árvore ((org==DEN)&&(dst==ORD))&&((prc<=500)&&(dur<=8400))
    No* raiz = new No("&&",
        new No("&&",
            new No("org", "==", "DEN"),
            new No("dst", "==", "ORD")
        ),
        new No("&&",
            new No("prc", "<=", "500"),
            new No("dur", "<=", "8400")
        )
    );

    cout << "Filtrando voos..." << endl;
    ListaVoos* resultado = filtrarVoos(raiz, voos, numLinhas);
    imprimirVoos(resultado);

    liberarLista(resultado);
    for (int i = 0; i < numLinhas; i++) delete voos[i];

    return 0;
}
