#include "Ordenador.hpp"

void Ordenador::ordenar(Resultado* res, int N)
{
    // Se nao existisse essa funcao extra a unica funcao ordenar retornaria
    // um vetor para quem chamou, mas quem chamou teria que liberar esse vetor da memoria
    // Visando a boa pratica, cria-se essa funcao extra, assim todo vetor criado aqui dentro e 
    // liberado da memoria
    Resultado* vetorOrdenado = ordernarRecursivamente(res, N);

    // Copia os dados ordenados de volta para o vetor original 
    for (int i = 0; i < N; ++i)
    {
        res[i] = vetorOrdenado[i];
    }

    delete[] vetorOrdenado;
}

Resultado* Ordenador::ordernarRecursivamente(Resultado* res, int N)
{
    // Base: um vetor de 1 elemento ja esta ordenado
    if (N <= 1)
    {
        Resultado* temp = new Resultado[1];
        temp[0] = res[0];

        return temp;
    }

    // Divisao: quebra o vetor no meio
    int n1 = N/2;
    int n2 = N - n1;

    // Conquista: resolve os dois subproblemas independentemente
    Resultado* temp1 = ordernarRecursivamente(res, n1);
    Resultado* temp2 = ordernarRecursivamente(res + n1, n2);
    Resultado* temp3 = new Resultado[n1 + n2];

    int v = 0, u = 0;

    // Junta as duas metades ordenadas em uma so
    for (int j = 0; j < n1 + n2; ++j)
    {
        if (v >= n1) 
        {
            temp3[j] = temp2[u];
            ++u;
        }
        else if (u >= n2) 
        {
            temp3[j] = temp1[v];
            ++v;
        }
        else if (temp1[v]._pontuacao >= temp2[u]._pontuacao) 
        {
            temp3[j] = temp1[v];
            ++v;
        }
        else 
        {
            temp3[j] = temp2[u];
            ++u;
        }
    }

    // Desaloca a memoria alocada nas chamadas anteriores
    delete[] temp1;
    delete[] temp2;

    return temp3;
}