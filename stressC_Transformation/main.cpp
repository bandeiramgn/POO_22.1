#include <iostream>
#include <algorithm>
#include <vector>
#include "aux.hpp"

using namespace aux;

// Filter

std::vector<int> get_men(std::vector<int> vet) {
     std::vector<int> mens;
    
    for (auto elem : vet) {
        if (elem > 0) {
            mens.push_back(elem);
        }
    }
    return mens;
}


std::vector<int> get_calm_women(std::vector<int> vet) {
    std::vector<int> womenStressTen;

    for (auto elem : vet) {
        if (elem < 0 && elem > (-10)) {
            womenStressTen.push_back(elem);
        }
    }
    return womenStressTen;
} 

// Sort

std::vector<int> sort(std::vector<int> vet) {
    // std::vector<int> vetOrder {vet};
    // std::sort(vetOrder.begin(), vetOrder.end());
    // return vetOrder;

    int valueAux {};

    for (int i = 0; i < (int) vet.size(); i++) {
        for (int j = 0; j < (int) vet.size(); j++) {
            if (vet[i] < vet[j]){
                valueAux = vet[i];
                vet[i] = vet[j];
                vet[j] = valueAux;
            }
        }
    }
    return vet;
}

std::vector<int> sort_stress(std::vector<int> vet) {
    int valueAux {};

    for (int i = 0; i < (int) vet.size(); i++) {
        for (int j = 0; j < (int) vet.size(); j++) {
            if (abs(vet[i]) < abs(vet[j])) {
                valueAux = vet[i];
                vet[i] = vet[j];
                vet[j] = valueAux;
            }
        }
    }
    return vet;
}

// Reverse

std::vector<int> reverse(std::vector<int> vet) {
    std::vector<int> vet_reverse;
    if (vet.empty()) 
        return vet_reverse;

    for (int i = vet.size()-1; i >= 0; i--) {
        vet_reverse.push_back(vet[i]);
    }
    return vet_reverse;
}

void reverse_inplace(std::vector<int> &vet) {
    reverse(vet.begin(),vet.end());
}

// Set

std::vector<int> unique(std::vector<int> vet){
    std::vector<int> vet_unique;

    for (auto elem : vet) {
        if (!in(vet_unique, elem)) {
            vet_unique.push_back(elem);
        }
    }
    return vet_unique;
}

std::vector<int> repeated(std::vector<int> vet) {
    std::vector<int> vet_unique;
    std::vector<int> vet_repeated;

    for (auto elem : vet) {
        if (!in(vet_unique, elem)) 
            vet_unique.push_back(elem);
        else
            vet_repeated.push_back(elem);
    }

    return vet_repeated;
}



//loop principal
int main(){
    Chain chain;
    Param ui;

    chain["get_men"]         = [&] { show <<        get_men(to_vet<int>(ui[1])); };
    chain["get_calm_women"]  = [&] { show << get_calm_women(to_vet<int>(ui[1])); };
    chain["sort"]            = [&] { show <<           sort(to_vet<int>(ui[1])); };
    chain["sort_stress"]     = [&] { show <<    sort_stress(to_vet<int>(ui[1])); };
    chain["reverse"]         = [&] { show <<        reverse(to_vet<int>(ui[1])); };
    chain["reverse_inplace"] = [&] { 
        auto vet = to_vet<int>(ui[1]);
        reverse_inplace(vet);
        show << (vet);
    };
    chain["unique"]          = [&] { show <<         unique(to_vet<int>(ui[1])); };
    chain["repeated"]        = [&] { show <<       repeated(to_vet<int>(ui[1])); };

    execute(chain, ui);
}


