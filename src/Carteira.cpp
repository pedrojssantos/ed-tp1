#include "Carteira.hpp"

Carteira::Carteira() : primeiro(nullptr), ultimo(nullptr), qtdAcoes(0) {}

Carteira::~Carteira()
{
    NoCarteira* noAtual = primeiro;
    NoCarteira* proxNo = nullptr;

    while (noAtual)
    {
        proxNo = noAtual->prox;
        delete noAtual;
        noAtual = proxNo;
    }
}

int Carteira::getQtdAcoes() const { return qtdAcoes; }

void Carteira::inserir(int id)
{
    NoCarteira* novoNo = new NoCarteira();
    novoNo->idAcao = id;
    novoNo->prox = nullptr;

    if (!primeiro)
    {
        primeiro = novoNo;
        ultimo = primeiro;
        qtdAcoes++;

        return;
    }

    ultimo->prox = novoNo;
    ultimo = novoNo;
    qtdAcoes++;
}

void Carteira::remover(int id)
{
    NoCarteira* noAtual = primeiro;
    NoCarteira* noAnterior = nullptr;

    while (noAtual)
    {
        if (noAtual->idAcao == id)
        {
            if (noAnterior)
                noAnterior->prox = noAtual->prox;
            else
                primeiro = noAtual->prox;

            if (ultimo == noAtual)
                ultimo = noAnterior;

            delete noAtual;

            --qtdAcoes;
            break;
        }

        noAnterior = noAtual;
        noAtual = noAtual->prox;
    }
}

bool Carteira::buscar(int id) const
{
    NoCarteira* noAtual = primeiro;

    bool existeId = false;

    while (noAtual)
    {
        if (noAtual->idAcao == id)
        {
            existeId = true;
            break;
        }
        else
            noAtual = noAtual->prox;
    }

    return existeId;
}