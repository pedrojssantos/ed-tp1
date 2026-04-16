#include "../include/Acao.hpp"

#include <math.h>

Acao::Acao(int id, int w) : id(id), tamMaxHisto(w) 
{
    historico = new JanelaCotacoes(tamMaxHisto);
}

Acao::~Acao() { delete historico; }

int Acao::getId() { return id; }

void Acao::adicionarPreco(double preco) { historico->inserir(preco); }

double Acao::calcRET()
{
    if (historico->getTamanho() < 2) return 0.0;

    return (historico->getMaisAntigo() / historico->getMaisRecente()) - 1;
}

double Acao::calcAVGRET()
{
    int n = historico->getTamanho() - 1;
    double somaRi, somaQuadrados;
    historico->somasParaMetricas(somaRi, somaQuadrados);
    double media = somaRi / n;

    return media;
}

double Acao::calcSTAB()
{
    int n = historico->getTamanho() - 1;
    double somaRi, somaQuadrados;
    historico->somasParaMetricas(somaRi, somaQuadrados);
    double media = calcAVGRET();

    double somaDiferencasQuadrado = somaQuadrados - (n * (media * media));

    double vol = std::sqrt(somaDiferencasQuadrado / n);

    return 1.0 / (1.0 + vol);
}

double Acao::calcCONS()
{
    int n = historico->getTamanho() - 1;
    int qtdPos = historico->positivoRi();

    double cons = qtdPos / n;

    return cons;
}