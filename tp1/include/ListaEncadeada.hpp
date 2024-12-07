template <class TipoItem>
class TipoCelula {
    public:
        TipoCelula(){
            item.SetChave(-1);
            prox = NULL;
        }
    private:
        TipoItem item;
        TipoCelula* proximo;

    friend class ListaEncadeada<TipoItem>;
};

template <class TipoItem>
class ListaEncadeada : public Lista {
    public:
        ListaEncadeada();
        ~ListaEncadeada();

        TipoItem GetItem(int pos);
        void SetItem(TipoItem item, int pos);
        void InsereInicio(TipoItem item);
        void InsereFinal(TipoItem item);
        void InserePosicao(TipoItem item, int pos);
        bool Troca(int pos1, int pos2);
        TipoItem RemoveInicio();
        TipoItem RemoveFinal();
        TipoItem RemovePosicao(int pos);
        void Imprime();
        void Limpa();
    private:
        TipoCelula<TipoItem>* primeiro;
        TipoCelula<TipoItem>* ultimo;
        int tamanho;
        TipoCelula<TipoItem>* Posiciona(int pos, bool antes);
};
