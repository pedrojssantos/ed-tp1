#ifndef ACAO_HPP
#define ACAO_HPP

class Acao
{
    private:
        int id;

    public:
        Acao(int id);
        int getId();
        void adicionarCotacao();
};

#endif