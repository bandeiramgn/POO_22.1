#include <iostream>
#include <algorithm>
#include <vector>
#include <aux.hpp>

using namespace aux;

// Functions aux

bool in(std::vector<int> vet, int x)
{
    for (int i = 0; i < (int)vet.size(); i++)
    {
        if (vet[i] == x)
        {
            return true;
        }
    }
    return false;
}

// Filter

std::vector<int> get_men(std::vector<int> vet)
{
    std::vector<int> mens;

    for (auto elem : vet)
    {
        if (elem > 0)
        {
            mens.push_back(elem);
        }
    }
    return mens;
}

std::vector<int> get_calm_women(std::vector<int> vet)
{
    std::vector<int> womenStressTen;

    for (auto elem : vet)
    {
        if (elem < 0 && elem > (-10))
        {
            womenStressTen.push_back(elem);
        }
    }
    return womenStressTen;
}

// Sort

std::vector<int> sort(std::vector<int> vet)
{
    // std::vector<int> vetOrder {vet};
    // std::sort(vetOrder.begin(), vetOrder.end());
    // return vetOrder;

    int valueAux{};

    for (int i = 0; i < (int)vet.size(); i++)
    {
        for (int j = 0; j < (int)vet.size(); j++)
        {
            if (vet[i] < vet[j])
            {
                valueAux = vet[i];
                vet[i] = vet[j];
                vet[j] = valueAux;
            }
        }
    }
    return vet;
}

std::vector<int> sort_stress(std::vector<int> vet)
{
    int valueAux{};

    for (int i = 0; i < (int)vet.size(); i++)
    {
        for (int j = 0; j < (int)vet.size(); j++)
        {
            if (abs(vet[i]) < abs(vet[j]))
            {
                valueAux = vet[i];
                vet[i] = vet[j];
                vet[j] = valueAux;
            }
        }
    }
    return vet;
}

// Reverse

std::vector<int> reverse(std::vector<int> vet)
{
    std::vector<int> vet_reverse;
    if (vet.empty())
        return vet_reverse;

    for (int i = vet.size() - 1; i >= 0; i--)
    {
        vet_reverse.push_back(vet[i]);
    }
    return vet_reverse;
}

void reverse_inplace(std::vector<int> &vet)
{
    reverse(vet.begin(), vet.end());
}

// Set

std::vector<int> unique(std::vector<int> vet)
{
    std::vector<int> vet_unique;

    for (auto elem : vet)
    {
        if (!in(vet_unique, elem))
        {
            vet_unique.push_back(elem);
        }
    }
    return vet_unique;
}

std::vector<int> repeated(std::vector<int> vet)
{
    std::vector<int> vet_unique;
    std::vector<int> vet_repeated;

    for (auto elem : vet)
    {
        if (!in(vet_unique, elem))
            vet_unique.push_back(elem);
        else
            vet_repeated.push_back(elem);
    }

    return vet_repeated;
}

// loop principal
int main()
{
    Chain chain;
    Param ui;

    auto VET = LAMBDA(x, x | COPY(1, -1) | SPLIT(',') | MAP(STR2<int>())); // converte de string para vetor de int
    auto par2vet = LAMBDAE(&, index, VET(ui.at(index)));

    chain["get_men"] = [&]
    { get_men(par2vet(1)) | FMT() | PRINT(); };
    chain["get_calm_women"] = [&]
    { get_calm_women(par2vet(1)) | FMT() | PRINT(); };
    chain["sort"] = [&]
    { sort(par2vet(1)) | FMT() | PRINT(); };
    chain["sort_stress"] = [&]
    { sort_stress(par2vet(1)) | FMT() | PRINT(); };
    chain["reverse"] = [&]
    { reverse(par2vet(1)) | FMT() | PRINT(); };
    chain["repeated"] = [&]
    { repeated(par2vet(1)) | FMT() | PRINT(); };
    chain["unique"] = [&]
    { unique(par2vet(1)) | FMT() | PRINT(); };
    chain["reverse_inplace"] = [&]
    {
        auto vet = par2vet(1);
        reverse_inplace(vet);
        vet | FMT() | PRINT();
    };

    execute(chain, ui);
}