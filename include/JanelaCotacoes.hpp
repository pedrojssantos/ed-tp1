#ifndef JANELA_COTACOES_HPP
#define JANELA_COTACOES_HPP

class JanelaCotacoes {
    private:
        double* _precos;
        int _w;
        int _tamanho;
        int _indiceAtual;

        double calcRi(int i) const;

    public:
        JanelaCotacoes(int w);
        ~JanelaCotacoes();
        void inserir(double preco);
        int getTamanho() const;
        double getMaisRecente() const;
        double getMaisAntigo() const;
        double getSomaRiPositivo() const;
        double getSomaRi() const;
        double getSomaRiQuadrados() const;
};

#endif