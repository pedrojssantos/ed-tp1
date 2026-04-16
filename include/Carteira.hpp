#ifndef CARTEIRA_HPP
#define CARTEIRA_HPP

#include "Acao.hpp"

class Carteira
{
    private:
        Acao* primeiro;
        Acao* ultimo;

    public:
        Carteira();
        ~Carteira();
        void Inserir(int id, int w);
        void Remover(int id);
        void Percorrer();
};

#endif