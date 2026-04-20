#include "Cliente.hpp"

Cliente::Cliente() : _id(-1)
{
    _carteira = new Carteira();
}

Cliente::~Cliente() 
{
    delete _carteira; 
}

int Cliente::getId() const 
{
    return _id; 
}
void Cliente::setId(int id) 
{
    _id = id; 
}

const Carteira& Cliente::getCarteira() const
{
    return *_carteira;
}

void Cliente::comprarAcao(int id) 
{
    _carteira->inserir(id);
}
void Cliente::venderAcao(int id) 
{
    _carteira->remover(id); 
}