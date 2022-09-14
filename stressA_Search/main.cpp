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


bool in(std::vector<int> vet, int x) { 
    for (int i = 0; i < (int) vet.size(); i++) {
        if (vet[i] == x) {
            return true;
        }    
    }
    return false;
}

int index_of(std::vector<int> vet, int x) {

    for (int i = 0; i < (int) vet.size(); i++) {
        if (vet[i] == x) {
            return i;
        }    
    }
    return -1;
}

int find_if(const std::vector<int>& vet) { 
    int positionMan {vet[0]};

    for (int i = 0; i < (int) vet.size(); i++) {
        if (vet[i] > 0) {
            positionMan = i;
            return positionMan;
        }   
    }
    return (int) -1;
}

int min_element(const std::vector<int>& vet) { 
    if (vet.empty()){
        return -1;    
    }
    int posMenor {0};

    for (int i = 1; i < (int) vet.size(); i++) {
        if (vet[i] < vet[posMenor]) {
            posMenor = i;
        }
    }
    return posMenor;
}

int find_min_if(const std::vector<int>& vet) { 
    int posMan = find_if(vet);

    for (int i = 0; i < (int) vet.size(); i++) {
        if (vet[i] > 0 && vet[i] < vet[posMan]) {
            posMan = i;
        }
    }
    return posMan;
}




// Funções auxiliares
template <class T>
T to(std::string data); //int value = to<int>("43");
std::vector<int> to_vet(std::string data); //vector<int> vet = to_vet("[1,2,3]");
std::vector<std::string> split(std::string content, char sep = ' '); //quebra uma linha em um vetor de palavras
std::string fmt(std::vector<int> data); //formata vetor como [2,3,4,5]
std::string fmt(bool value); //retorna bool como "true" ou "false"
std::string fmt(double value); //retorna com duas casas decimais;

template <class T>
void print(T data) {
    std::cout << data << std::endl;
}

//loop principal
int main(){
    while(true) {
        std::string line{};
        std::getline(std::cin, line);
        print("$" + line);
        auto ui = split(line);
        auto cmd = ui[0];
        if (cmd == "end") {
            break;
        } else if (cmd == "in") {
            auto res = in(to_vet(ui[1]), to<int>(ui[2]));
            std::cout << fmt(res) << '\n';
        }   else if (cmd == "index_of") {
            auto res = index_of(to_vet(ui[1]), to<int>(ui[2]));
            std::cout << res << '\n';
        } else if (cmd == "find_if") {
            auto res = find_if(to_vet(ui[1]));
            std::cout << res << '\n';
         }  else if (cmd == "min_element") {
             std::cout << min_element(to_vet(ui[1])) << '\n';
        } else if (cmd == "find_min_if") {
            std::cout << find_min_if(to_vet(ui[1])) << '\n';
        } else if (cmd == "count") {
            std::cout << count(to_vet(ui[1]), to<int>(ui[2])) << '\n';
        } else if (cmd == "average") {
            std::cout << fmt(average(to_vet(ui[1]))) << '\n';
        } else if (cmd == "more_men") {
             std::cout << more_men(to_vet(ui[1])) << '\n';
        } else if (cmd == "half_compare") {
           std::cout << half_compare(to_vet(ui[1])) << '\n';
        } else if (cmd == "sex_battle") {
            std::cout << sex_battle(to_vet(ui[1])) << '\n';
         } else {
             std::cout << "unknown command: " << cmd << '\n';
        }
    }
    return 0;
}

std::vector<std::string> split(std::string content, char sep) {
    std::stringstream ss(content);
    std::string token;
    std::vector<std::string> vet;
    while(std::getline(ss, token, sep))
        vet.push_back(token);
    return vet;
}

template <class T>
T to(std::string data) {
    T value;
    std::istringstream(data) >> value;
    return value;
}

std::vector<int> to_vet(std::string data) {
    auto vet_str = split(data.substr(1, data.size() - 2), ',');
    // int value {};
    std::vector<int> vet;
    for (auto token : vet_str)
        vet.push_back(to<int>(token));
    return vet;
}

std::string fmt(std::vector<int> data) {
    std::ostringstream ss;
    ss << "[";
    for (auto it = data.begin(); it != data.end(); ++it)
        ss << (it != data.begin() ? "," : "") << *it;
    ss << "]";
    return ss.str();
}

std::string fmt(bool value) {
    return value ? "true" : "false";
}

std::string fmt(double value) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << value;
    return ss.str();
}