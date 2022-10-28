#include <iostream>
#include <algorithm>
#include <list>
#include <sstream>

int main()
{
    std::list<std::string> lista {"Bandeira", "raquel", "Raimundo", "Bellda", "Kauê"};

    

    std::cout << lista.back() << std::endl;
    // for (auto it = std::prev(waiting.begin()); it != std::prev(waiting.end()); ++it)
    // {
    //     auto var = *it;
    //     saida += var->str();
    // }
}