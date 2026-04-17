#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "Carteira.hpp"

class Cliente 
{
    private:
        int _id;
        Carteira* carteira;
        
    public:
        Cliente();
        ~Cliente();

        int getId() const;
        void setId(int id);

        void comprarAcao(int id);
        void venderAcao(int id);
};

#endif