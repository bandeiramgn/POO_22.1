#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <aux.hpp>

class Pessoa
{
    std::string nome;

public:
    Pessoa(std::string nome) : nome(nome)
    {
    }
    std::string getNome() const
    {
        return nome; // todo
    }
    std::string str() const
    {
        return nome;
    }
};

std::ostream &operator<<(std::ostream &os, const Pessoa &p)
{
    return (os << p.str());
}

class Mercantil
{
    std::vector<std::shared_ptr<Pessoa>> boxs;    // caixas do supermercado
    std::list<std::shared_ptr<Pessoa>> esperando; // lista de clientes esperando

    bool validarIndice(int indice)
    {
        if (indice < 0 || indice >= (int)this->boxs.size())
        {
            return false;
        }
        return true;
    }

public:
    Mercantil(int qtd_caixas)
    {
        for (int i = 0; i < (int)qtd_caixas; i++)
        {
            boxs.push_back(nullptr);
        }
    }

    void chegar(const std::shared_ptr<Pessoa> &person)
    {
        esperando.push_back(person);
    }

    bool chamarNoCaixa(int indice)
    {
        if (!validarIndice(indice))
        {
            return false;
        }

        if (this->esperando.empty())
        {
            std::cout << "fail: sem clientes\n";
            return false;
        }

        if (this->boxs[indice] != nullptr)
        {
            std::cout << "fail: caixa ocupado\n";
            return false;
        }

        if (this->boxs[indice] == nullptr)
        {
            this->boxs[indice] = this->esperando.front();
            this->esperando.pop_front();
            return true;
        }
        return false;
    }

    std::shared_ptr<Pessoa> finalizar(int indice)
    {
        if (validarIndice(indice) && this->boxs[indice] != nullptr)
        {
            auto person = this->boxs[indice];
            this->boxs[indice] = nullptr;
            return person;
        }

        if (validarIndice(indice) && this->boxs[indice] == nullptr)
        {
            std::cout << "fail: caixa vazio\n";
            return {};
        }

        if (!validarIndice(indice))
        {
            std::cout << "fail: caixa inexistente\n";
            return {};
        }

        return {};
    }

    std::string str() const
    {
        int i = 0;
        auto fn = [&i](auto p)
        {
            std::stringstream ss;
            ss << " " << i++ << ":" << (p == nullptr ? "-----" : p->getNome()) << " ";
            return ss.str();
        };
        std::stringstream os;
        os << "Caixas: |" << (boxs | aux::MAP(fn) | aux::JOIN("|")) << "|\n"
           << "Espera: " << (esperando | aux::MAP(LAMBDA(x, *x)) | aux::FMT());
        return os.str();
    }
};

std::ostream &operator<<(std::ostream &os, const Mercantil &b)
{
    return (os << b.str());
}

int main()
{
    aux::Chain chain;
    aux::Param par;

    Mercantil bank(0);

    chain["init"] = [&]()
    { bank = Mercantil(aux::to<int>(par[1])); };
    chain["call"] = [&]()
    { bank.chamarNoCaixa(aux::to<int>(par[1])); };
    chain["finish"] = [&]()
    { bank.finalizar(aux::to<int>(par[1])); };
    chain["arrive"] = [&]()
    { bank.chegar(std::make_shared<Pessoa>(par[1])); };
    chain["show"] = [&]()
    { std::cout << bank << '\n'; };

    aux::execute(chain, par);
}
