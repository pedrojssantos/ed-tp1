#include "../include/Carteira.hpp"
#include <iostream>

Carteira::Carteira() : primeiro(nullptr), ultimo(nullptr) {}

Carteira::~Carteira()
{
    Acao* acaoAtual = primeiro;
    Acao* proxAcao = nullptr;

    while (acaoAtual)
    {
        proxAcao = acaoAtual->getProximo();
        delete acaoAtual;
        acaoAtual = proxAcao;
    }
}

void Carteira::Inserir(int id, int w)
{
    Acao* novaAcao = new Acao(id, w);

    if (!primeiro)
    {
        primeiro = novaAcao;
        ultimo = primeiro;

        return;
    }

    ultimo->setProximo(novaAcao);
    ultimo = novaAcao;
}

void Carteira::Remover(int id)
{
    Acao* acaoAnterior = nullptr;
    Acao* acaoAtual = primeiro;

    while (acaoAtual)
    {
        if (acaoAtual->getId() == id) break;

        acaoAnterior = acaoAtual;

        acaoAtual = acaoAtual->getProximo();
    }

    if (!acaoAtual) return;

    if (acaoAnterior)
    {
        acaoAnterior->setProximo(acaoAtual->getProximo());
    }
    else
    {
        primeiro = acaoAtual->getProximo();
    }

    if (acaoAtual == ultimo)
        ultimo = acaoAnterior;

    acaoAtual->setProximo(nullptr);

    delete acaoAtual;
}

void Carteira::Percorrer()
{
    Acao* acaoAtual = primeiro;

    while (acaoAtual)
    {
        std::cout << acaoAtual->getId() << std::endl;
        acaoAtual = acaoAtual->getProximo();
    }
}