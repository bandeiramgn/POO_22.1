#include <iostream>

int main() {
    int a = 8;
    int b = a;
    int& c = b; // Cria uma referencia c para a var b 
    int * d; // Crie um ponteiro para inteiro d
    d = &b; // D recebe o endereço de b

    std::cout << *d;


    /*
        Esquerda 
        * = ponteiro para
        & = referencia para

        Direita
        * = ir para valor de 
        & = endereço de 
    */
}