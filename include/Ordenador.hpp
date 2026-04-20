#ifndef ORDENADOR_HPP
#define ORDENADOR_HPP

#include "Resultado.hpp"

class Ordenador
{
    private:
        static Resultado* ordernarRecursivamente(Resultado* resultados, int N);

    public:
        static void ordenar(Resultado* resultados, int N);
};

#endif