#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "aux.hpp"
using namespace aux;

std::vector<std::pair<int, int>> occurr(std::vector<int> vet) { 
    std::vector<int> noRepetad;
    std::vector<int> numbersAbs;
    std::vector<std::pair<int, int>> result;

    for (auto elem : vet) {
        if (!in(noRepetad, abs(elem))) {
            noRepetad.push_back(elem);
        }
        numbersAbs.push_back(abs(elem));
    }
    
    std::sort(noRepetad.begin(), noRepetad.end());

    for (int i = 0; i < (int) noRepetad.size(); i++) {
        result.push_back(std::make_pair(noRepetad[i], count(numbersAbs, noRepetad[i])));
    }

    return result;
}

std::vector<std::pair<int, int>> teams(std::vector<int> vet) {  
    std::vector<std::pair<int, int>> niveis;
    std::vector<int> noRepeat {};

    int acc {0};
    int prox {0};

    for (auto elem : vet) {
        if (!in(noRepeat, abs(elem))) {
            noRepeat.push_back(elem);
        }
    }

    for (auto i = prox; i < (int) noRepeat.size(); i++) {
        for (int j = prox; j < (int) vet.size();j++) {
            if (noRepeat[i] == vet[j]) {
                acc++;
                continue;
            } else {
                prox = j;
                break;
            }
        }
        niveis.push_back(std::make_pair(noRepeat[i], acc));
        acc = 0;
    }

    return niveis;
}

// std::vector<int> mnext(std::vector<int> vet) { // todo 
// }

// std::vector<int> alone(std::vector<int> vet) { // todo 
// }

// int couple(std::vector<int> vet) { // todo 
// }

// bool has_subseq(std::vector<int> vet, std::vector<int> seq, int pos) { // todo 
// }

// int subseq(std::vector<int> vet, std::vector<int> seq) { // todo 
// }

// std::vector<int> erase(std::vector<int> vet, std::vector<int> pos_list) { // todo 
// }

// std::vector<int> clear(std::vector<int> vet, int value) { // todo 
// }


//loop principal
int main(){
    Chain chain;
    Param ui;

    chain["occurr"] = [&] { show << occurr(to_vet<int>(ui[1])); };
    // chain["mnext"]  = [&] { show <<  mnext(to_vet<int>(ui[1])); };
    // chain["alone"]  = [&] { show <<  alone(to_vet<int>(ui[1])); };
    // chain["couple"] = [&] { show << couple(to_vet<int>(ui[1])); };
    chain["teams"]  = [&] { show <<  teams(to_vet<int>(ui[1])); };
    // chain["subseq"] = [&] { show << subseq(to_vet<int>(ui[1]), to_vet<int>(ui[2])); };
    // chain["erase"]  = [&] { show <<  erase(to_vet<int>(ui[1]), to_vet<int>(ui[2])); };
    // chain["clear"]  = [&] { show <<  clear(to_vet<int>(ui[1]), to<int>(ui[2])); };

    execute(chain, ui);
}