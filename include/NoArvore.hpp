#ifndef NO_ARVORE_HPP
#define NO_ARVORE_HPP

class NoArvore {
    private:
        int valor;
        NoArvore* filhoMenor;
        NoArvore* filhoMaior;

    public:
        NoArvore();
        
        int getValor();
        void setValor(int valor);

        NoArvore* getFilhoMenor();
        void setFilhoMenor(NoArvore* no);

        NoArvore* getFilhoMaior();
        void setFilhoMaior(NoArvore* no);
};

#endif