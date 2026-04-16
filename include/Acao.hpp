#ifndef ACAO_HPP
#define ACAO_HPP

#include "JanelaCotacoes.hpp"

class Acao
{
    private:
        int id;
        int tamMaxHisto;
        JanelaCotacoes* historico;

    public:
        Acao(int id, int w);
        ~Acao();
        int getId();
        void adicionarPreco(double preco);
        double calcRET();
        double calcAVGRET();
        double calcSTAB();
        double calcCONS();
};

#endif