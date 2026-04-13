#include "../include/ArvoreBin.hpp"

ArvoreBin::ArvoreBin() : raiz(nullptr) {}

void ArvoreBin::Inserir(int valor)
{
    NoArvore* novoNo = new NoArvore();
    novoNo->setValor(valor);

    if (!this->raiz)
    {
        this->raiz = novoNo;
        
        return;
    }

    NoArvore* noAtual = this->raiz;
    NoArvore* noAnterior = nullptr;

    while (noAtual)
    {
        noAnterior = noAtual;

        if (valor > noAtual->getValor())
            noAtual = noAtual->getFilhoMaior();
        else
            noAtual = noAtual->getFilhoMenor();
    }

    if (valor > noAnterior->getValor())
        noAnterior->setFilhoMaior(novoNo);
    else
        noAnterior->setFilhoMenor(novoNo);
}