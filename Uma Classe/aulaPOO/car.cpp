#include <iostream>
#include <sstream>

struct Car {
    int pass;
    int passMax;

    Car() {
        pass = 0;
        passMax = 0;
    }

    void entrar() {
        if (pass == passMax) 
            std::cout << "fail: carro lotado!\n";
        else 
            pass++;
    }

    void sair() {
        if (pass == 0) {        
            std::cout << "fail: carro já está vazio!\n";
        }
        else 
            pass--;
    }

    std::string str() {
        std::stringstream ss;
        ss << "pass: " << pass << "/" << passMax << '\n';
        return ss.str();
    }
};

int main() {
    Car car;
    std::cou  
}
