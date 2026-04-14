#ifndef ARVORE_BIN_HPP
#define ARVORE_BIN_HPP

#include "NoArvore.hpp"

class ArvoreBin {
    private:
        NoArvore* raiz;
        void destruirArvore(NoArvore* raiz);

    public:
        ArvoreBin();
        ~ArvoreBin();
        void Inserir(int valor);
        void Remover(int valor);
        NoArvore* Buscar(int valor);
};

#endif