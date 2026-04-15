#ifndef CLIENTE_HPP
#define CLIENTE_HPP

class Cliente 
{
    private:
        int id;
        
    public:
        Cliente(int id);
        int getId();
        void comprarAcao();
        void venderAcao();
};

#endif