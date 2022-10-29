#include <iostream>
#include <algorithm>
#include <list>
#include <memory>
#include <sstream>

int main()
{
    std::list<std::string> lista {"Bandeira", "raquel", "Raimundo", "Bellda", "Kauê"};

    auto it = find(lista.begin(), lista.end(), "Bandeira");

    std::cout << *it << std::endl;
    // for (auto it = std::prev(waiting.begin()); it != std::prev(waiting.end()); ++it)
    // {
    //     auto var = *it;
    //     saida += var->str();
    // }
}