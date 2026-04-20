#include "Cliente.hpp"
#include "Carteira.hpp"
#include "Acao.hpp"
#include "Resultado.hpp"
#include "Ordenador.hpp"

#include <iostream>
#include <sstream>

int main()
{
    std::string acao = "";
    std::string comando = "";
    std::string historicoComandos = "";
    std::stringstream token;
    std::string metrica = "";
    std::string metricasGlobais = "";
    int w = 0;
    int N = 0, u = 0;

    std::getline(std::cin, acao);
    token.str(acao);
    token >> N >> u;
    token.clear();

    Acao* vetorGlobalAcoes = new Acao[N];
    Cliente* vetorGlobalClientes = new Cliente[u];
    Resultado* ranking = new Resultado[N];

    while (std::getline(std::cin, acao))
    {
        token.str(acao);
        token >> comando;
        historicoComandos += comando + " ";

        if (comando == "M")
        {
            token >> w;

            while (token >> metrica)
            {
                metricasGlobais += metrica + " ";
            }
        }
        else if (comando == "A")
        {
            int idAcao = 0;
            token >> idAcao;
        
            if (idAcao < N)
            {
                vetorGlobalAcoes[idAcao].inicializar(idAcao, w);
            }
        }
        else if (comando == "U")
        {
            int idCliente = 0;
            token >> idCliente;

            if (idCliente < u)
            {
                vetorGlobalClientes[idCliente].setId(idCliente);
            }
        }
        else if (comando == "P")
        {
            int idAcao = 0;
            double precoAcao = 0;
            token >> idAcao >> precoAcao;

            vetorGlobalAcoes[idAcao].adicionarPreco(precoAcao);
        }
        else if (comando == "B")
        {
            int idCliente = 0, idAcao = 0;
            token >> idCliente >> idAcao;

            vetorGlobalClientes[idCliente].comprarAcao(idAcao);
        }
        else if (comando == "V")
        {
            int idCliente = 0, idAcao = 0;
            token >> idCliente >> idAcao;

            vetorGlobalClientes[idCliente].venderAcao(idAcao);
            
        }
        else if (comando == "Q")
        {
            int idConsulta = 0, idCliente = 0;
            int numAcoes = 0, numMetricas = 0;
            token >> idConsulta >> idCliente >> numAcoes >> numMetricas;

            std::string metricasConsulta[4];
            int pesos[4];
            int qtdMetricas = 0;

            std::string metrica = "";
            int peso;

            while (token >> metrica >> peso)
            {
                metricasConsulta[qtdMetricas] = metrica;
                pesos[qtdMetricas] = peso;
                qtdMetricas++;
            }

            double* placarFinal = new double[N];
            for (int i = 0; i < N; ++i) {
                placarFinal[i] = 0.0;
            }

            Resultado* tempMetrica = new Resultado[N];

            for (int j = 0; j < qtdMetricas; ++j) 
            {
                for (int i = 0; i < N; ++i) 
                {
                    tempMetrica[i]._idAcao = vetorGlobalAcoes[i].getId();
                    
                    if (metricasConsulta[j] == "RET") {
                        tempMetrica[i]._pontuacao = vetorGlobalAcoes[i].calcRET();
                    } 
                    else if (metricasConsulta[j] == "AVGRET") {
                        tempMetrica[i]._pontuacao = vetorGlobalAcoes[i].calcAVGRET();
                    }
                    else if (metricasConsulta[j] == "STAB") {
                        tempMetrica[i]._pontuacao = vetorGlobalAcoes[i].calcSTAB();
                    }
                    else if (metricasConsulta[j] == "CONS") {
                        tempMetrica[i]._pontuacao = vetorGlobalAcoes[i].calcCONS();
                    }
                }

                Ordenador::ordenar(tempMetrica, N);

                for (int pos = 0; pos < N; ++pos) 
                {
                    int idDestaAcao = tempMetrica[pos]._idAcao;
                    double pontosDaPosicao = (N - pos); 
                    
                    placarFinal[idDestaAcao] += (pontosDaPosicao * pesos[j]);
                }
            }

            for (int i = 0; i < N; ++i) 
            {
                ranking[i]._idAcao = vetorGlobalAcoes[i].getId();
                ranking[i]._pontuacao = placarFinal[ranking[i]._idAcao];
            }

            Ordenador::ordenar(ranking, N);

            for (int j = 0; j < N; ++j)
            {
                ranking[j]._posicaoGlobal = j;
            }

            delete[] tempMetrica;
            delete[] placarFinal;

            Resultado* melhores = nullptr;
            Resultado* piores = nullptr;

            int nM = 0, nP = 0;

            Cliente& cliente = vetorGlobalClientes[idCliente];
            int numAcoesCliente = cliente.getCarteira().getQtdAcoes();

            if (numAcoesCliente < numAcoes)
            {
                nM = numAcoesCliente;
                melhores = new Resultado[nM];

                int k = 0;

                for (int i = 0; i < N; ++i)
                {
                    if (cliente.getCarteira().buscar(ranking[i]._idAcao))
                    {
                        melhores[k] = ranking[i];
                        ++k;
                    }
                }
            }
            else
            {
                nM = numAcoes; 
                nP = numAcoes;
                melhores = new Resultado[nM];
                piores = new Resultado[nP];

                int contMelhores = 0;
                for (int i = 0; i < N; ++i)
                {
                    if (contMelhores == numAcoes) break;

                    if (cliente.getCarteira().buscar(ranking[i]._idAcao))
                    {
                        melhores[contMelhores] = ranking[i];
                        contMelhores++;
                    }
                }

                int contPiores = 0;

                for (int i = N - 1; i >= 0; --i) 
                {
                    if (contPiores == numAcoes) break;
                    if (cliente.getCarteira().buscar(ranking[i]._idAcao))
                    {
                        piores[contPiores] = ranking[i]; 
                        contPiores++;
                    }
                }
            }

            for (int i = 0; i < nM; ++i)
            {
                std::cout << "R " << idConsulta 
                << " M " << i 
                << " " << melhores[i]._idAcao << " " << melhores[i]._pontuacao << std::endl;
            }

            for (int i = 0; i < nP; ++i)
            {
                std::cout << "R " << idConsulta 
                << " P " << i
                << " " << piores[i]._idAcao << " " << piores[i]._pontuacao << std::endl;
            }


            delete[] melhores;
            delete[] piores;
        }

        token.clear();
        comando = "";
    }

    delete[] vetorGlobalAcoes;
    delete[] vetorGlobalClientes;
    delete[] ranking;

    return 0;
}