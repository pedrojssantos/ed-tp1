#include "../include/Cliente.hpp"

Cliente::Cliente() : _id(-1)
{
    carteira = new Carteira();
}

Cliente::~Cliente() { delete carteira; }

int Cliente::getId() const { return _id; }
void Cliente::setId(int id) { _id = id; }

void Cliente::comprarAcao(int id) { carteira->inserir(id); }
void Cliente::venderAcao(int id) { carteira->remover(id); }