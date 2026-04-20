#include "JanelaCotacoes.hpp"

JanelaCotacoes::JanelaCotacoes(int w) : tamMax(w), tamanho(0), indiceAtual(0)
{
    precos = new double[tamMax];
}

JanelaCotacoes::~JanelaCotacoes() { delete[] precos; }

void JanelaCotacoes::inserir(double preco) 
{
    precos[indiceAtual] = preco;
    
    indiceAtual = (indiceAtual + 1) % tamMax;

    if (tamanho < tamMax) tamanho++;
}

int JanelaCotacoes::getTamanho() 
{
    return tamanho;
}

double JanelaCotacoes::getMaisRecente() 
{
    if (tamanho == 0) return 0.0;

    int indiceMaisRecente = (indiceAtual - 1 + tamMax) % tamMax;
    return precos[indiceMaisRecente];
}

double JanelaCotacoes::getMaisAntigo() 
{
    if (tamanho == 0) return 0.0;

    if (tamanho < tamMax) return precos[0];
    
    return precos[indiceAtual];
}

double JanelaCotacoes::getSomaRiPositivo()
{
    if (tamanho < 2) return 0.0;

    int contador = 0;

    for (int i = 1; i < tamanho; i++)
    {
        if (calcRi(i) > 0) contador++;
    }

    return contador;
}

double JanelaCotacoes::calcRi(int i)
{
    int inicio = (tamanho < tamMax) ? 0 : indiceAtual;
        
    int idxAnterior = (inicio + i - 1) % tamMax;
    int idxAtual = (inicio + i) % tamMax;

    return (precos[idxAtual] / precos[idxAnterior]) - 1.0;
}

double JanelaCotacoes::getSomaRi()
{
    if (tamanho < 2) return 0.0;

    double soma = 0.0;

    for (int i = 1; i < tamanho; ++i)
    {
        double ri = calcRi(i);

        soma += ri;
    }

    return soma;
}

double JanelaCotacoes::getSomaRiQuadrados()
{
    if (tamanho < 2) return 0.0;

    double soma = 0.0;

    for (int i = 1; i < tamanho; ++i)
    {
        double ri = calcRi(i);

        soma += (ri * ri);
    }

    return soma;
}