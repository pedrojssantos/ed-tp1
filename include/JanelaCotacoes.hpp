#ifndef JANELA_COTACOES_HPP
#define JANELA_COTACOES_HPP

class JanelaCotacoes {
    private:
        double* precos;
        int tamMax;
        int tamanho;
        int indiceAtual;

        double calcRi(int i);

    public:
        JanelaCotacoes(int w);
        ~JanelaCotacoes();

        void inserir(double preco);

        int getTamanho();
        double getMaisRecente();
        double getMaisAntigo();
        double somaRi();
        double positivoRi();
};

#endif