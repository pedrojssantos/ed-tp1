#include "JanelaCotacoes.hpp"

JanelaCotacoes::JanelaCotacoes(int w) : _w(w), _tamanho(0), _indiceAtual(0)
{
    // Aloca o vetor com o tamanho da janela
    _precos = new double[_w];
}

JanelaCotacoes::~JanelaCotacoes() 
{
    delete[] _precos;
}

void JanelaCotacoes::inserir(double preco) 
{
    _precos[_indiceAtual] = preco;
    
    // Quando _indiceAtual atinge _w, ele volta para 0, sobrescrevendo o preco mais antigo
    _indiceAtual = (_indiceAtual + 1) % _w;

    if (_tamanho < _w) _tamanho++;
}

int JanelaCotacoes::getTamanho() const
{
    return _tamanho;
}

double JanelaCotacoes::getMaisRecente() const
{
    if (_tamanho == 0) return 0.0;

    // O mais recente e o que acabou de ser inserido
    int indiceMaisRecente = (_indiceAtual - 1 + _w) % _w;
    return _precos[indiceMaisRecente];
}

double JanelaCotacoes::getMaisAntigo() const
{
    if (_tamanho == 0) return 0.0;

    // Se a janela ainda nao encheu, o mais antigo esta na primeira posicao
    if (_tamanho < _w) return _precos[0];
    
    // Se a janela ja deu a volta completa, a posicao do mais antigo e _indiceAtual
    return _precos[_indiceAtual];
}

double JanelaCotacoes::getSomaRiPositivo() const
{
    if (_tamanho < 2) return 0.0;

    int contador = 0;

    // Varre o historico limitando-se ao tamanho da janela
    for (int i = 1; i < _tamanho; i++)
    {
        if (calcRi(i) > 0) contador++;
    }

    return contador;
}

double JanelaCotacoes::calcRi(int i) const
{
    // Logica de mapeamento da fila
    int inicio = (_tamanho < _w) ? 0 : _indiceAtual;
        
    int idxAnterior = (inicio + i - 1) % _w;
    int idxAtual = (inicio + i) % _w;

    return (_precos[idxAtual] / _precos[idxAnterior]) - 1.0;
}

double JanelaCotacoes::getSomaRi() const
{
    if (_tamanho < 2) return 0.0;

    double soma = 0.0;

    for (int i = 1; i < _tamanho; ++i)
    {
        double ri = calcRi(i);
        soma += ri;
    }

    return soma;
}

double JanelaCotacoes::getSomaRiQuadrados() const
{
    if (_tamanho < 2) return 0.0;

    double soma = 0.0;
    
    for (int i = 1; i < _tamanho; ++i)
    {
        double ri = calcRi(i);
        soma += (ri * ri);
    }

    return soma;
}