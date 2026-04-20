#ifndef CARTEIRA_HPP
#define CARTEIRA_HPP

struct NoCarteira
{
    int idAcao;
    NoCarteira* prox;
};

class Carteira
{
    private:
        NoCarteira* primeiro;
        NoCarteira* ultimo;
        int qtdAcoes;

    public:
        Carteira();
        ~Carteira();

        int getQtdAcoes() const;

        void inserir(int id);
        void remover(int id);
        bool buscar(int id) const;
};

#endif