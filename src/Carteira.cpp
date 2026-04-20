#include "Carteira.hpp"

Carteira::Carteira() : _primeiro(nullptr), _ultimo(nullptr), _qtdAcoes(0) {}

Carteira::~Carteira()
{
    NoCarteira* noAtual = _primeiro;
    NoCarteira* proxNo = nullptr;

    while (noAtual)
    {
        proxNo = noAtual->_prox;
        delete noAtual;
        noAtual = proxNo;
    }
}

int Carteira::getQtdAcoes() const 
{
    return _qtdAcoes;
}

void Carteira::inserir(int id)
{
    NoCarteira* novoNo = new NoCarteira();
    novoNo->_idAcao = id;
    novoNo->_prox = nullptr;

    if (!_primeiro)
    {
        _primeiro = novoNo;
        _ultimo = _primeiro;
        _qtdAcoes++;

        return;
    }

    _ultimo->_prox = novoNo;
    _ultimo = novoNo;
    _qtdAcoes++;
}

void Carteira::remover(int id)
{
    NoCarteira* noAtual = _primeiro;
    NoCarteira* noAnterior = nullptr;

    while (noAtual)
    {
        if (noAtual->_idAcao == id)
        {
            if (noAnterior)
                noAnterior->_prox = noAtual->_prox;
            else
                _primeiro = noAtual->_prox;

            if (_ultimo == noAtual)
                _ultimo = noAnterior;

            delete noAtual;

            --_qtdAcoes;
            break;
        }

        noAnterior = noAtual;
        noAtual = noAtual->_prox;
    }
}

bool Carteira::buscar(int id) const
{
    NoCarteira* noAtual = _primeiro;

    bool existeId = false;

    while (noAtual)
    {
        if (noAtual->_idAcao == id)
        {
            existeId = true;
            break;
        }
        else
            noAtual = noAtual->_prox;
    }

    return existeId;
}