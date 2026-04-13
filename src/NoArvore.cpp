#include "../include/NoArvore.hpp"

NoArvore::NoArvore() : valor(0), filhoMenor(nullptr), filhoMaior(nullptr) {}

int NoArvore::getValor() { return this->valor; }
void NoArvore::setValor(int valor) { this->valor = valor; }

NoArvore* NoArvore::getFilhoMenor() { return this->filhoMenor; }
void NoArvore::setFilhoMenor(NoArvore* no) { this->filhoMenor = no; }

NoArvore* NoArvore::getFilhoMaior() { return this->filhoMaior; }
void NoArvore::setFilhoMaior(NoArvore* no) { this->filhoMaior = no; }