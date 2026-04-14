#ifndef ARVORE_BIN_HPP
#define ARVORE_BIN_HPP

#include "NoArvore.hpp"

class ArvoreBin {
    private:
        NoArvore* raiz;
        
    public:
        ArvoreBin();
        void Inserir(int valor);
        void Remover(int valor);
        NoArvore* Buscar(int valor);
};

#endif