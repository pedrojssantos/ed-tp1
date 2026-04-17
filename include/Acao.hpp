#ifndef ACAO_HPP
#define ACAO_HPP

#include "JanelaCotacoes.hpp"

class Acao
{
    private:
        int _id;
        int _w;
        JanelaCotacoes* historico;

    public:
        Acao();
        ~Acao();
        
        int getId();
        void setId(int id);
        void setW(int w);

        void adicionarPreco(double preco);

        double calcRET();
        double calcAVGRET();
        double calcSTAB();
        double calcCONS();
};

#endif