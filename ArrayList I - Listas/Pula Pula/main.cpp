#include <iostream>
#include <list>
#include <sstream>
#include <memory>
#include <aux.hpp>

using namespace aux;

class Kid
{
private:
    int age;
    std::string name;

public:
    Kid(std::string name, int age) : age(age), name(name)
    {
    }

    int getAge()
    {
        return age;
    }

    std::string getName()
    {
        return name;
    }

    std::string str()
    {
        return name + ":" + std::to_string(age);
    }
};

using PtrKid = std::shared_ptr<Kid>;

std::ostream &operator<<(std::ostream &os, PtrKid kid)
{
    return (os << kid->str());
}

class Trampoline
{
    std::list<PtrKid> waiting;
    std::list<PtrKid> playing;

    PtrKid removeFromList(std::string name, std::list<PtrKid> &lista)
    {
        for (auto it = lista.begin(); it != lista.end(); it++)
        {
            auto kid = *it;
            if (kid->getName() == name)
            {
                lista.erase(it);
                return kid;
            }
        }
        return {};
        // for (auto kidSearch : lista) {
        //     if (kidSearch == name->getName()) {
        //         auto kid = kidSearch;
        //         lista.remove(lista.begin(), lista.end(), kidSearch);
        //         return kid;
        //     }
        //     else {
        //         return{};
        //     }
        // }

        // auto it = std::find(lista.begin(), lista.end(), name);

        // if (kid == lista.end()) {
        //     std::cout << "fail: crianca não está na lista\n";
        //     return;
        // } else {
        //     auto kid = *it;
        //     lista.erase(*it);
        //     return kid;
        // }
        // return {};
    }

public:
    Trampoline()
    {
    }

    void arrive(PtrKid kid)
    {
        waiting.push_front(kid);
    }

    void enter()
    {
        if (waiting.empty())
        {
            // std::cout << "fail: lista de espera está vazia!\n";
            return;
        }

        auto it = waiting.back();
        waiting.pop_back();

        playing.push_front(it);
    }

    void leave()
    {
        if (playing.empty())
        {
            // std::cout << "fail: lista de\n";
            return;
        }
        auto kid = playing.back();
        removeFromList(kid->getName(), playing);
        waiting.push_front(kid);
        return;
    }

    PtrKid removeKid(std::string name)
    {
        return (removeFromList(name, waiting), removeFromList(name, playing));
    }

    std::string str()
    {
        std::stringstream ss;
        std::string exitOne, exitTwo;

        for (auto kid : waiting)
        {
            if (kid == waiting.back())
            {
                exitOne += kid->str();
            }
            else
            {
                exitOne += kid->str() + ", ";
            }
        }
        for (auto kid : playing)
        {
            if (kid == playing.back())
            {
                exitTwo += kid->str();
            }
            else
            {
                exitTwo += kid->str() + ", ";
            }
        }

        ss << "[" << exitOne << "] => ["
           << exitTwo << "]";

        return ss.str();
    }
};

int main()
{
    aux::Chain chain;
    aux::Param param;
    Trampoline tr;
    chain["arrive"] = [&]()
    { tr.arrive(std::make_shared<Kid>(param[1], aux::to<int>(param[2]))); };
    chain["enter"] = [&]()
    { tr.enter(); };
    chain["leave"] = [&]()
    { tr.leave(); };
    chain["remove"] = [&]()
    { tr.removeKid(param[1]); };
    chain["show"] = [&]()
    { std::cout << tr.str() << std::endl; };

    aux::execute(chain, param);
}