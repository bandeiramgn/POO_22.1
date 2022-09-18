#include <iostream>
#include <vector>

struct Car {
    int pass;
    int passMax;
    Car() {
        std::cout << "Estou criando um carro \n"; 
    }
};




int main () {
    Car carro;

    if (2 > 1) {
        Car carro2;
        Car carro3;
    }

    std::cout << carro;
}