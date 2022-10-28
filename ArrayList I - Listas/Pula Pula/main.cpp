#include <iostream>
#include <list>
#include <sstream>
#include <memory>
#include <aux.hpp>

using namespace aux;

class Kid {
private:
    int age;
    std::string name;

public:
    Kid(std::string name, int age): age(age), name(name)
    {}

    int getAge() {
        return age;
    }
    
    std::string getName() {
        return name;
    }

    std::string str() {
        return name + ":" + std::to_string(age);
    }
};

using PtrKid = std::shared_ptr<Kid>;

std::ostream& operator<<(std::ostream& os,  PtrKid kid) {
    return (os << kid->str());
}

class Trampoline {
    std::list<PtrKid> waiting;
    std::list<PtrKid> playing;
    
    PtrKid removeFromList(std::string name, std::list<PtrKid>& lista) {
        return {};
    }

public:
    Trampoline() {
    }
    
    void arrive(PtrKid kid) {
        waiting.push_back(kid);
    }

    void enter() {
    }

    void leave() {
    }

    PtrKid removeKid(std::string name) {
        return {};
    }

    std::string str() {
        std::stringstream ss;
        std::string exitOne, exitTwo;

        for (auto kid : waiting) {
            if (kid == waiting.back()) {
                exitOne += kid->str();
            } else {
                exitOne += kid->str() + ", ";
            }
        }
        for (auto kid : playing) {
            if (kid == playing.back()) {
                exitTwo += kid->str();
            } else {
                exitTwo += kid->str() + ", ";
            }
        }
        
        ss << "[" << exitOne << "] => [" 
            << exitTwo << "]";
        
        return ss.str();
    }
};

int main() {
    aux::Chain chain;
    aux::Param param;
    Trampoline tr;
    chain["arrive"] = [&]() { tr.arrive(std::make_shared<Kid>(param[1], aux::to<int>(param[2]))); };
    chain["enter"]  = [&]() { tr.enter(); };
    chain["leave"]  = [&]() { tr.leave(); };
    chain["remove"] = [&]() { tr.removeKid(param[1]); };
    chain["show"]   = [&]() { std::cout << tr.str() << std::endl; };

    aux::execute(chain, param);
}