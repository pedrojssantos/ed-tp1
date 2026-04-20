#include "../include/Ordenador.hpp"

#include <iostream>

void Ordenador::ordenar(Resultado* res, int N)
{
    Resultado* vetorOrdenado = ordernarRecursivamente(res, N);

    for (int i = 0; i < N; ++i)
    {
        res[i] = vetorOrdenado[i];
    }

    delete[] vetorOrdenado;
}

Resultado* Ordenador::ordernarRecursivamente(Resultado* res, int N)
{
    if (N <= 1)
    {
        Resultado* temp = new Resultado[1];
        temp[0] = res[0];

        return temp;
    }

    int n1 = N/2;
    int n2 = N - n1;

    Resultado* temp1 = ordernarRecursivamente(res, n1);
    Resultado* temp2 = ordernarRecursivamente(res + n1, n2);
    Resultado* temp3 = new Resultado[n1 + n2];

    int v = 0, u = 0;

    for (int j = 0; j < n1 + n2; ++j)
    {
        if (v >= n1) {
            temp3[j] = temp2[u];
            ++u;
        }
        else if (u >= n2) {
            temp3[j] = temp1[v];
            ++v;
        }
        else if (temp1[v].pontuacao >= temp2[u].pontuacao) {
            temp3[j] = temp1[v];
            ++v;
        }
        else {
            temp3[j] = temp2[u];
            ++u;
        }
    }

    delete[] temp1;
    delete[] temp2;

    return temp3;
}