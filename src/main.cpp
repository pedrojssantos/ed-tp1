#include "Cliente.hpp"
#include "Carteira.hpp"
#include "Acao.hpp"
#include "Resultado.hpp"
#include "Ordenador.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

int main()
{
    // Define as capacidades iniciais para os vetores globais
    int capAcoes = 10;
    int capClientes = 10;

    // Define os vetores globais
    Acao** vetorGlobalAcoes = new Acao*[capAcoes];
    for (int i = 0; i < capAcoes; ++i) vetorGlobalAcoes[i] = nullptr;

    Cliente** vetorGlobalClientes = new Cliente*[capClientes];
    for (int i = 0; i < capClientes; ++i) vetorGlobalClientes[i] = nullptr;

    std::string linha;
    std::string comando;
    int w = 0;
    int N = 0;
    int u = 0;

    // Buffer para acumular as impressoes e formatar no final
    std::ostringstream saidaFinal;

    while (std::getline(std::cin, linha))
    {
        // Limpa o caractere \r
        if (!linha.empty() && linha.back() == '\r') 
        {
            linha.pop_back();
        }

        if (linha.empty()) continue;

        std::stringstream token(linha);
        token >> comando;

        if (comando == "M")
        {
            token >> w;
        }
        else if (comando == "A")
        {
            int idAcao = 0;
            token >> idAcao;

            // Realoca o vetor de acoes dobrando a capacidade se o ID estourar o limite
            if (idAcao >= capAcoes)
            {
                int novaCap = capAcoes * 2;
                while (idAcao >= novaCap) novaCap *= 2;
                Acao** vetorAux = new Acao*[novaCap];

                for (int i = 0; i < novaCap; ++i) 
                {
                    if (i < capAcoes) vetorAux[i] = vetorGlobalAcoes[i];
                    else vetorAux[i] = nullptr;
                }

                delete[] vetorGlobalAcoes;
                vetorGlobalAcoes = vetorAux;
                capAcoes = novaCap;
            }

            if (!vetorGlobalAcoes[idAcao])
            {
                vetorGlobalAcoes[idAcao] = new Acao();
                vetorGlobalAcoes[idAcao]->inicializar(idAcao, w);
            }

            // Atualiza o contador total de acoes
            if (idAcao >= N) N = idAcao + 1;
        }
        else if (comando == "U")
        {
            int idCliente = 0;
            token >> idCliente;

            // Realoca o vetor de clientes dobrando a capacidade se necessario
            if (idCliente >= capClientes)
            {
                int novaCap = capClientes * 2;
                while (idCliente >= novaCap) novaCap *= 2;
                Cliente** vetorAux = new Cliente*[novaCap];

                for (int i = 0; i < novaCap; ++i) 
                {
                    if (i < capClientes) vetorAux[i] = vetorGlobalClientes[i];
                    else vetorAux[i] = nullptr;
                }
                
                delete[] vetorGlobalClientes;
                vetorGlobalClientes = vetorAux;
                capClientes = novaCap;
            }

            if (!vetorGlobalClientes[idCliente])
            {
                vetorGlobalClientes[idCliente] = new Cliente();
                vetorGlobalClientes[idCliente]->setId(idCliente);
            }

            if (idCliente >= u) u = idCliente + 1;
        }
        else if (comando == "P")
        {
            int idAcao = 0;
            double precoAcao = 0.0;
            token >> idAcao >> precoAcao;

            vetorGlobalAcoes[idAcao]->adicionarPreco(precoAcao);
        }
        else if (comando == "B")
        {
            int idCliente = 0, idAcao = 0;
            token >> idCliente >> idAcao;
           
            vetorGlobalClientes[idCliente]->comprarAcao(idAcao);
        }
        else if (comando == "V")
        {
            int idCliente = 0, idAcao = 0;
            token >> idCliente >> idAcao;

            vetorGlobalClientes[idCliente]->venderAcao(idAcao);
        }
        else if (comando == "Q")
        {
            int idConsulta = 0, idCliente = 0;
            int numAcoes = 0, numMetricas = 0;
            token >> idConsulta >> idCliente >> numAcoes >> numMetricas;

            std::string metricasConsulta[4];
            double pesos[4];

            for (int j = 0; j < numMetricas; ++j)
            {
                token >> metricasConsulta[j] >> pesos[j];
            }

            if (N == 0) continue;

            Resultado* ranking = new Resultado[N];
            double* placarFinal = new double[N];

            for (int i = 0; i < N; ++i)
            {
                placarFinal[i] = 0.0;
            }

            Resultado* tempMetrica = new Resultado[N];

            // Calcula os pontos de cada metrica solicitada e soma no placar final
            for (int j = 0; j < numMetricas; ++j)
            {
                for (int i = 0; i < N; ++i)
                {
                    tempMetrica[i]._idAcao = i;
                    tempMetrica[i]._pontuacao = 0.0;

                    if (vetorGlobalAcoes[i]) 
                    {
                        tempMetrica[i]._idAcao = vetorGlobalAcoes[i]->getId();
                        if (metricasConsulta[j] == "RET") tempMetrica[i]._pontuacao = vetorGlobalAcoes[i]->calcRET();
                        else if (metricasConsulta[j] == "AVGRET") tempMetrica[i]._pontuacao = vetorGlobalAcoes[i]->calcAVGRET();
                        else if (metricasConsulta[j] == "STAB") tempMetrica[i]._pontuacao = vetorGlobalAcoes[i]->calcSTAB();
                        else if (metricasConsulta[j] == "CONS") tempMetrica[i]._pontuacao = vetorGlobalAcoes[i]->calcCONS();
                    }
                }

                Ordenador::ordenar(tempMetrica, N);

                // Distribui os pontos baseados na posição (N - pos) e multiplica pelo peso
                for (int pos = 0; pos < N; ++pos)
                {
                    int idDestaAcao = tempMetrica[pos]._idAcao;
                    double pontosDaPosicao = (N - pos);
                    placarFinal[idDestaAcao] += (pontosDaPosicao * pesos[j]);
                }
            }

            // Monta o vetor com a pontuacao global definitiva
            for (int i = 0; i < N; ++i)
            {
                ranking[i]._idAcao = i;
                ranking[i]._pontuacao = placarFinal[i];
                if (vetorGlobalAcoes[i]) 
                {
                    ranking[i]._idAcao = vetorGlobalAcoes[i]->getId();
                }
            }

            Ordenador::ordenar(ranking, N);

            for (int j = 0; j < N; ++j)
            {
                ranking[j]._posicaoGlobal = j;
            }

            // Desaloca memoria  
            delete[] tempMetrica;
            delete[] placarFinal;

            // Prepara a extracao das acoes que o cliente possui
            Cliente* cliente = idCliente < capClientes ? vetorGlobalClientes[idCliente] : nullptr;
            int numAcoesCliente = cliente ? cliente->getCarteira().getQtdAcoes() : 0;

            // Ajusta o limite caso a carteira tenha menos acoes que as numAcoes pedidas
            int limiteRetorno = numAcoesCliente < numAcoes ? numAcoesCliente : numAcoes;

            Resultado* melhores = nullptr;
            Resultado* piores = nullptr;

            if (limiteRetorno > 0) 
            {
                melhores = new Resultado[limiteRetorno];
                piores = new Resultado[limiteRetorno];
            }

            // Desce o ranking preenchendo as melhores
            int contMelhores = 0;
            for (int i = 0; i < N && contMelhores < limiteRetorno; ++i)
            {
                if (cliente && cliente->getCarteira().buscar(ranking[i]._idAcao))
                {
                    melhores[contMelhores] = ranking[i];
                    ++contMelhores;
                }
            }

            // Sobe o ranking (de baixo pra cima) preenchendo as piores
            int contPiores = 0;
            for (int i = N - 1; i >= 0 && contPiores < limiteRetorno; --i)
            {
                if (cliente && cliente->getCarteira().buscar(ranking[i]._idAcao))
                {
                    piores[contPiores] = ranking[i];
                    ++contPiores;
                }
            }

            // Mini-sort: desfaz a inversao de IDs causada pela leitura de baixo pra cima nos casos de empate
            double margem = 0.00001;
            for (int i = 0; i < contPiores - 1; ++i) 
            {
                for (int j = 0; j < contPiores - i - 1; ++j) 
                {
                    double diff = piores[j]._pontuacao - piores[j+1]._pontuacao;
                    if (diff < 0) diff = -diff;

                    if (diff <= margem) {
                        if (piores[j]._idAcao > piores[j+1]._idAcao) 
                        {
                            Resultado temp = piores[j];
                            piores[j] = piores[j+1];
                            piores[j+1] = temp;
                        }
                    }
                }
            }

            // Junta os resultados no buffer
            for (int i = 0; i < contMelhores; ++i)
            {
                saidaFinal << "R " << idConsulta << " M " << i << " " << melhores[i]._idAcao << " " << std::fixed << std::setprecision(2) << melhores[i]._pontuacao << "\r\n";
            }

            for (int i = 0; i < contPiores; ++i)
            {
                saidaFinal << "R " << idConsulta << " P " << i << " " << piores[i]._idAcao << " " << std::fixed << std::setprecision(2) << piores[i]._pontuacao << "\r\n";
            }

            delete[] melhores;
            delete[] piores;
            delete[] ranking;
        }
    }

    // Remove a ultima quebra de linha do buffer
    std::string textoFinal = saidaFinal.str();
    if (!textoFinal.empty()) 
    {
        if (textoFinal.back() == '\n') textoFinal.pop_back();
        if (textoFinal.back() == '\r') textoFinal.pop_back();
    }

    std::cout << textoFinal;

    // Desaloca memoria
    for (int i = 0; i < capAcoes; ++i) 
    {
        if (vetorGlobalAcoes[i]) delete vetorGlobalAcoes[i];
    }

    for (int i = 0; i < capClientes; ++i) 
    {
        if (vetorGlobalClientes[i]) delete vetorGlobalClientes[i];
    }

    delete[] vetorGlobalAcoes;
    delete[] vetorGlobalClientes;

    return 0;
}
