#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <aux.hpp>

class Cliente
{
    std::string id;
    std::string fone;

public:
    Cliente(std::string id = "", std::string fone = "") : id(id), fone(fone)
    {
    }

    void setId(std::string id)
    {
        this->id = id;
    }

    void setFone(std::string fone)
    {
        this->fone = fone;
    }

    std::string getId()
    {
        return this->id;
    }

    std::string getFone()
    {
        return this->fone;
    }

    std::string str()
    {
        std::stringstream ss;
        ss << id << ":" << fone;
        return ss.str();
    }
};

std::ostream &operator<<(std::ostream &os, Cliente c)
{
    return os << c.str();
}

class Sala
{
    std::vector<std::shared_ptr<Cliente>> cadeiras;

    int procurar(std::string nome)
    {
        for (int i = 0; i < (int)cadeiras.size(); i++)
        {
            if (cadeiras[i] != nullptr && cadeiras[i]->getId() == nome)
            {
                return i;
            }
        }
        return -1;
    }

    bool verificarIndice(int indice)
    {
        if (indice < 0 || indice > (int)(cadeiras.size() - 1))
        {
            return false;
        }

        return true;
    }

public:
    Sala(int qtd = 0) : cadeiras(qtd, nullptr)
    {
    }

    void reservar(std::string id, std::string fone, int ind)
    {
        if (!verificarIndice(ind))
        {
            std::cout << "fail: cadeira nao existe\n";
            return;
        }

        if (procurar(id) != -1)
        {
            std::cout << "fail: cliente ja esta no cinema\n";
            return;
        }

        if (cadeiras[ind] != nullptr)
        {
            std::cout << "fail: cadeira ja esta ocupada\n";
            return;
        }

        cadeiras[ind] = std::make_shared<Cliente>(id, fone);
    }

    void cancelar(std::string id)
    {
        int idRemoveClient = procurar(id);

        if (idRemoveClient != -1)
        {
            cadeiras[idRemoveClient] = nullptr;
        }
        else
        {
            std::cout << "fail: cliente nao esta no cinema\n";
        }
    }

    std::string str()
    {
        std::stringstream ss;
        std::string prefix = "[";
        std::string suffix = "]";

        ss << prefix;
        for (int i = 0; i < (int)cadeiras.size(); i++)
        {
            int j = cadeiras.size() - 1;

            if (cadeiras[i] == nullptr && i == j)
                ss << "-";
            else if (cadeiras[i] == nullptr)
                ss << "- ";
            else if (cadeiras[i] != nullptr && i == j)
                ss << cadeiras[i]->str();
            else
                ss << cadeiras[i]->str() << " ";
        }
        ss << suffix;

        return ss.str();
    }
};

int main()
{
    aux::Chain chain;
    aux::Param param;
    Sala sala;

    chain["init"] = [&]()
    { sala = Sala(aux::to<int>(param[1])); };
    chain["reservar"] = [&]()
    { sala.reservar(param[1], param[2], aux::to<int>(param[3])); };
    chain["cancelar"] = [&]()
    { sala.cancelar(param[1]); };
    chain["show"] = [&]()
    { std::cout << sala.str() << std::endl; };

    aux::execute(chain, param);
}
