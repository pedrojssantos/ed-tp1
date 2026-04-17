all: tp1.out

tp1.out: src/Acao.cpp src/ArvoreBin.cpp src/Carteira.cpp src/Cliente.cpp src/JanelaCotacoes.cpp src/NoArvore.cpp src/main.cpp
	g++ -std=c++11 src/Acao.cpp src/ArvoreBin.cpp src/Carteira.cpp src/Cliente.cpp src/JanelaCotacoes.cpp src/NoArvore.cpp src/main.cpp -o tp1.out

clean:
	rm -f tp1.out