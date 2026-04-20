#ifndef CARTEIRA_HPP
#define CARTEIRA_HPP

struct NoCarteira
{
    int _idAcao;
    NoCarteira* _prox;
};

class Carteira
{
    private:
        NoCarteira* _primeiro;
        NoCarteira* _ultimo;
        int _qtdAcoes;

    public:
        Carteira();
        ~Carteira();
        int getQtdAcoes() const;
        void inserir(int id);
        void remover(int id);
        bool buscar(int id) const;
};

#endif