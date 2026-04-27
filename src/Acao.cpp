#include "Acao.hpp"
#include <cmath>

Acao::Acao() : _id(-1), _w(-1) , _historico(nullptr) {}

Acao::~Acao() 
{
    delete _historico;
}

void Acao::inicializar(int id, int w)
{
    _id = id;
    _w = w;
    _historico = new JanelaCotacoes(_w);
}

int Acao::getId() const
{
    return _id;
}

void Acao::adicionarPreco(double preco) 
{
    _historico->inserir(preco); 
}

double Acao::calcRET() const
{
    if (!_historico || _historico->getTamanho() < 2) return 0.0;

    return (_historico->getMaisRecente() / _historico->getMaisAntigo()) - 1.0;
}

double Acao::calcAVGRET() const
{
    if (!_historico || _historico->getTamanho() < 2) return 0.0;

    int n = _historico->getTamanho() - 1;
    double somaRi = _historico->getSomaRi();

    double avgret = (double)(somaRi) / (double)(n); 

    return avgret;
}

double Acao::calcSTAB() const
{
    if (!_historico || _historico->getTamanho() < 2) return 0.0;

    int n = _historico->getTamanho() - 1;
    double somaQuadrados = _historico->getSomaRiQuadrados();
    double media = calcAVGRET();

    double somaDiferencasQuadrado = somaQuadrados - (n * (media * media));

    double vol = std::sqrt((double)(somaDiferencasQuadrado) / (double)(n));

    return 1.0 / (1.0 + vol);
}

double Acao::calcCONS() const
{
    if (!_historico || _historico->getTamanho() < 2) return 0.0;

    int n = _historico->getTamanho() - 1;
    int qtdPos = _historico->getSomaRiPositivo();

    double cons = (double)(qtdPos) / (double)(n);

    return cons;
}