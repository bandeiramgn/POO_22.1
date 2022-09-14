#include <iostream>
#include <vector>
#include "aux.hpp"
using namespace aux;



int count(std::vector<int> vet, int x) {
    int cont {0};
    
    for(int value : vet) {
        if (value == x) {
            cont++;
        }
    } 
    return cont;
}

int sum(std::vector<int> vet) {
    int somatorio {};

    for(auto value : vet) {
        somatorio += abs(value);
    }
    return somatorio;
}

double average(const std::vector<int>& vet) { 
    double count {};
    
    for (int value : vet) {
        count += abs(value);
    }

    return (count / (int) vet.size()); 
}

std::string more_men(const std::vector<int>& vet) { 
    std::vector<int> womem;
    std::vector<int> man;

    for (auto value : vet) {
        if (value > 0) {
            man.push_back(value);
        } else {
            womem.push_back(value);
        }
    }

    if ((womem.size()) > (man.size())) {
        return "women";
    } else if (womem.size() < man.size()) {
        return "men";
    } else {
        return "draw";
    }
}   

std::string half_compare(const std::vector<int>& vet) { 
    int primeiraMetade { 0 };
    int segundaMetade { 0 };
    int tamVetor = (int) vet.size();

    for (int i = 0; i < tamVetor; i++) {
        auto value = std::abs(vet[i]);   
        if (tamVetor % 2 == 1 && i == (tamVetor/2)) { 
            continue;
        } else if(i < (tamVetor/2)){
            primeiraMetade += value;
        } else {
            segundaMetade += value;
        }
    }
    if (primeiraMetade > segundaMetade){ 
        return "first"; 
    } else if (primeiraMetade < segundaMetade){
        return "second"; 
    } else {
        return "draw";
    }
}


std::string sex_battle(const std::vector<int>& vet) { 
    double men {};
    double women {};
    int contMen {0};
    int contWomen {0};

    for(auto a : vet) {
        if (a > 0) {
            men += a;
            contMen++;
        } else {
            women += a;
            contWomen++;
        }
    }
    if ((men/contMen) > (abs(women)/contWomen)){
        return "men"; 
    } else if ((men/contMen) < (abs(women)/contWomen)){
        return "women";
    } else {
        return "draw";
    }

 }




//loop principal
int main(){
    Chain chain;
    Param ui;

    chain["count"]        = [&] { show <<        count(to_vet<int>(ui[1]), to<int>(ui[2])); };
    chain["sum"]          = [&] { show <<          sum(to_vet<int>(ui[1])                ); };
    chain["average"]      = [&] { show <<      average(to_vet<int>(ui[1])                ); };
    chain["more_men"]     = [&] { show <<     more_men(to_vet<int>(ui[1])                ); };
    chain["half_compare"] = [&] { show << half_compare(to_vet<int>(ui[1])                ); };
    chain["sex_battle"]   = [&] { show <<   sex_battle(to_vet<int>(ui[1])                ); };

    execute(chain, ui);
}
