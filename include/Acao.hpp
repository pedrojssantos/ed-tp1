#ifndef ACAO_HPP
#define ACAO_HPP

#include "JanelaCotacoes.hpp"

class Acao
{
    private:
        int _id;
        int _w;
        JanelaCotacoes* _historico;

    public:
        Acao();
        ~Acao();
        void inicializar(int id, int w);
        int getId() const;
        void adicionarPreco(double preco);
        double calcRET() const;
        double calcAVGRET() const;
        double calcSTAB() const;
        double calcCONS() const;
};

#endif