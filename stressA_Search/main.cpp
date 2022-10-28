/*
        A atividade inicial do curso acabou sendo bem divertida de fazer e desafiadora ao mesmo tempo, sendo o meu primeiro contato com a linguagem C++. Mas de
    forma sincera, achei a sintaxe menos complexa do que a linguagem java (Usada na cadeira de POO feita antes).
        Falando da atividade, levei cerca de 2h 30m para fazer todas, algumas foi meio que "Automático" outras eu demorei bem mais tempo para idealizar a ideia
    de como fazer mas foi bem legal e conseguir ter uma boa imersão na linguagem e a trabalhar a lógica de programação tendo que quebrar bastante neurônios para
    fazer o código mais clean possível.

        Em uma escala de 0 a 5, a minha retenção de conteúdo dessa parte foi 3. Ainda fiquei com algumas dúvidas em relação a Stringstream que pretendo estudar de forma
    mais imensiva nas próximas aulas.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <tuple>
#include <functional>
#include <iomanip>
#include <cstddef>
#include <cstdlib>
#include <aux.hpp>

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

int index_of(std::vector<int> vet, int x)
{

    for (int i = 0; i < (int)vet.size(); i++)
    {
        if (vet[i] == x)
        {
            return i;
        }
    }
    return -1;
}

int find_if(const std::vector<int> &vet)
{
    int positionMan{vet[0]};

    for (int i = 0; i < (int)vet.size(); i++)
    {
        if (vet[i] > 0)
        {
            positionMan = i;
            return positionMan;
        }
    }
    return (int)-1;
}

int min_element(const std::vector<int> &vet)
{
    if (vet.empty())
    {
        return -1;
    }
    int posMenor{0};

    for (int i = 1; i < (int)vet.size(); i++)
    {
        if (vet[i] < vet[posMenor])
        {
            posMenor = i;
        }
    }
    return posMenor;
}

int find_min_if(const std::vector<int> &vet)
{
    int posMan = find_if(vet);

    for (int i = 0; i < (int)vet.size(); i++)
    {
        if (vet[i] > 0 && vet[i] < vet[posMan])
        {
            posMan = i;
        }
    }
    return posMan;
}

// loop principal
using namespace aux;

int main()
{
    Chain chain;
    Param ui;

    auto bool2str = LAMBDA(x, x ? "true" : "false");                       // converte de bool para string true or false
    auto INT = LAMBDA(x, x | aux::STR2<int>());                            // converte de string para int
    auto VET = LAMBDA(x, x | COPY(1, -1) | SPLIT(',') | MAP(STR2<int>())); // converte de string para vetor de int

    chain["in"] = [&]
    { in(VET(ui.at(1)), INT(ui.at(2))) | PIPE(bool2str) | PRINT(); };
    chain["index_of"] = [&]
    { index_of(VET(ui.at(1)), INT(ui.at(2))) | PRINT(); };
    chain["find_if"] = [&]
    { find_if(VET(ui.at(1))) | PRINT(); };
    chain["min_element"] = [&]
    { min_element(VET(ui.at(1))) | PRINT(); };
    chain["find_min_if"] = [&]
    { find_min_if(VET(ui.at(1))) | PRINT(); };

    execute(chain, ui);
}