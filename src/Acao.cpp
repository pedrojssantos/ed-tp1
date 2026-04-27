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
    // Cria a janela circular com o tamanho limite w
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
    // Protecao: se nao tem pelo menos 2 precos para comparar, o retorno e zero
    if (!_historico || _historico->getTamanho() < 2) return 0.0;

    // Calcula RET
    return (_historico->getMaisRecente() / _historico->getMaisAntigo()) - 1.0;
}

double Acao::calcAVGRET() const
{
    if (!_historico || _historico->getTamanho() < 2) return 0.0;

    int n = _historico->getTamanho() - 1;
    double somaRi = _historico->getSomaRi();

    // Calcula AVGRET
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

    // Calcula STAB
    double vol = std::sqrt((double)(somaDiferencasQuadrado) / (double)(n));

    return 1.0 / (1.0 + vol);
}

double Acao::calcCONS() const
{
    if (!_historico || _historico->getTamanho() < 2) return 0.0;

    int n = _historico->getTamanho() - 1;
    int qtdPos = _historico->getSomaRiPositivo();

    // Calcula CONS
    double cons = (double)(qtdPos) / (double)(n);

    return cons;
}