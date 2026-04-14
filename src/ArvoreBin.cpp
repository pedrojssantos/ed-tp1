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

void ArvoreBin::Remover(int valor)
{
    NoArvore* noAnteriorAtual = nullptr;
    NoArvore* noAtual = this->raiz;

    while (noAtual)
    {
        if (valor == noAtual->getValor()) break;

        noAnteriorAtual = noAtual;

        if (valor > noAtual->getValor())
            noAtual = noAtual->getFilhoMaior();
        else
            noAtual = noAtual->getFilhoMenor();
    }

    if (!noAtual) return;

    if (noAtual->getFilhoMaior() && noAtual->getFilhoMenor())
    {
        NoArvore* noAnteriorMaiorEsq = noAtual;
        NoArvore* noMaiorEsq = noAtual->getFilhoMenor();

        while (true)
        {
            if (!noMaiorEsq->getFilhoMaior()) break;
            noAnteriorMaiorEsq= noMaiorEsq;
            noMaiorEsq = noMaiorEsq->getFilhoMaior();
        }

        if (noAnteriorMaiorEsq->getFilhoMaior() == noMaiorEsq)
            noAnteriorMaiorEsq->setFilhoMaior(noMaiorEsq->getFilhoMenor());
        else
            noAnteriorMaiorEsq->setFilhoMenor(noMaiorEsq->getFilhoMenor());

        noMaiorEsq->setFilhoMaior(noAtual->getFilhoMaior());
        noMaiorEsq->setFilhoMenor(noAtual->getFilhoMenor());

        if (noAnteriorAtual)
        {
            if (valor > noAnteriorAtual->getValor())
                noAnteriorAtual->setFilhoMaior(noMaiorEsq);
            else
                noAnteriorAtual->setFilhoMenor(noMaiorEsq);
        }
        else
        {
            this->raiz = noMaiorEsq;
        }
    }
    else if (noAtual->getFilhoMaior())
    {
        if (noAnteriorAtual)
        {
            if (noAnteriorAtual->getFilhoMaior() == noAtual)
                noAnteriorAtual->setFilhoMaior(noAtual->getFilhoMaior());
            else
                noAnteriorAtual->setFilhoMenor(noAtual->getFilhoMaior());
        }
        else
        {
            this->raiz = noAtual->getFilhoMaior();
        }
    }
    else if (noAtual->getFilhoMenor())
    {
        if (noAnteriorAtual)
        {
            if (noAnteriorAtual->getFilhoMaior() == noAtual)
                noAnteriorAtual->setFilhoMaior(noAtual->getFilhoMenor());
            else
                noAnteriorAtual->setFilhoMenor(noAtual->getFilhoMenor());
        }
        else
        {
            this->raiz = noAtual->getFilhoMenor();
        }
    }
    else 
    {
        if (noAnteriorAtual)
        {
            if (noAnteriorAtual->getFilhoMaior() == noAtual)
                noAnteriorAtual->setFilhoMaior(nullptr);
            else
                noAnteriorAtual->setFilhoMenor(nullptr);
        }
        else
        {
            this->raiz = nullptr;
        }
    }

    noAtual->setFilhoMaior(nullptr);
    noAtual->setFilhoMenor(nullptr);

    delete noAtual;
}