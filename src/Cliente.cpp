#include "../include/Cliente.hpp"

Cliente::Cliente(int id) : id(id)
{
    carteira = new Carteira();
}

Cliente::~Cliente() { delete carteira; }

void Cliente::comprarAcao(int w, int id) { carteira->Inserir(id, w); }
void Cliente::venderAcao(int id) { carteira->Remover(id); }