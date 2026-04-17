#include "../include/Acao.hpp"

#include <math.h>

Acao::Acao() : _id(-1), _w(-1) , historico(nullptr) {}

Acao::~Acao() { delete historico; }

void Acao::setId(int id) { _id = id; }
int Acao::getId() { return _id; }

void Acao::setW(int w) { _w = w; }

void Acao::adicionarPreco(double preco) { historico->inserir(preco); }

double Acao::calcRET()
{
    if (historico->getTamanho() < 2) return 0.0;

    return (historico->getMaisRecente() / historico->getMaisAntigo()) - 1;
}

double Acao::calcAVGRET()
{
    int n = historico->getTamanho() - 1;
    double somaRi = historico->getSomaRi();

    double avgret = somaRi / n;

    return avgret;
}

double Acao::calcSTAB()
{
    int n = historico->getTamanho() - 1;
    double somaQuadrados = historico->getSomaRiQuadrados();
    double media = calcAVGRET();

    double somaDiferencasQuadrado = somaQuadrados - (n * (media * media));

    double vol = std::sqrt(somaDiferencasQuadrado / n);

    return 1.0 / (1.0 + vol);
}

double Acao::calcCONS()
{
    int n = historico->getTamanho() - 1;
    int qtdPos = historico->getSomaRiPositivo();

    double cons = qtdPos / n;

    return cons;
}