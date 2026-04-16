#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "Carteira.hpp"

class Cliente 
{
    private:
        int id;
        Carteira* carteira;
        
    public:
        Cliente(int id);
        ~Cliente();
        int getId();
        void comprarAcao(int id, int w);
        void venderAcao(int id);
};

#endif