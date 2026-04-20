#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "Carteira.hpp"

class Cliente 
{
    private:
        int _id;
        Carteira* _carteira;
        
    public:
        Cliente();
        ~Cliente();
        void setId(int id);
        int getId() const;
        const Carteira& getCarteira() const;
        void comprarAcao(int id);
        void venderAcao(int id);
};

#endif