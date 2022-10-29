#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <utility>
#include <iomanip> //setprecision
#include <aux.hpp>

class Grafite
{
    float calibre;
    std::string dureza;
    int tamanho;

public:
    Grafite(float calibre, std::string dureza, int tamanho) : calibre(calibre),
                                                              dureza(dureza), tamanho(tamanho)
    {
    }

    int desgastePorFolha() const
    {
        if (dureza == "HB")
            return 1;
        if (dureza == "2B")
            return 2;
        if (dureza == "4B")
            return 4;
        return 6;
    }
    float getCalibre() const
    {
        return calibre;
    }
    std::string getDureza() const
    {
        return dureza;
    }
    int getTamanho() const
    {
        return tamanho;
    }
    void setTamanho(int tamanho)
    {
        this->tamanho = tamanho;
    }
    std::string str() const
    {
        std::ostringstream os;
        os << std::fixed << std::setprecision(1) << calibre << ":" << dureza << ":" << tamanho;
        return os.str();
    }
};

std::ostream &operator<<(std::ostream &os, Grafite g)
{
    return os << g.str();
}

using PGrafite = std::shared_ptr<Grafite>;

std::ostream &operator<<(std::ostream &os, PGrafite g)
{
    return os << "[" << (g == nullptr ? "" : g->str()) << "]";
}

struct Lapiseira
{
    float calibre{0.f};
    PGrafite grafite{nullptr};
    std::list<PGrafite> tambor;

    Lapiseira(float calibre = 0.0) : calibre(calibre), grafite(nullptr), tambor()
    {
    }

    bool inserir(PGrafite grafite)
    {
        if (calibre == grafite->getCalibre())
        {
            tambor.push_back(grafite);
            return true;
        }
        else
        {
            std::cout << "fail: calibre incompatível\n";
            return false;
        }
        return false;
    }

    PGrafite remover()
    {
        if (grafite == nullptr)
        {
            std::cout << "fail: nao tem grafite no bico\n";
            return nullptr;
        }

        auto grafiteReturn = grafite;
        grafite = nullptr;

        return grafiteReturn;
    }

    void write()
    {
        if (grafite == nullptr)
        {
            std::cout << "fail: nao existe grafite no bico\n";
            return;
        }
        if (grafite->getTamanho() <= 10)
        {
            std::cout << "fail: tamanho insuficiente\n";
            return;
        }

        int useGrafite = grafite->desgastePorFolha();

        if ((grafite->getTamanho() - useGrafite) < 10)
        {
            grafite->setTamanho(10);
            std::cout << "fail: folha incompleta\n";
            return;
        }
        else
        {
            grafite->setTamanho(grafite->getTamanho() - useGrafite);
            return;
        }
    }

    void puxar()
    {
        if (tambor.empty())
        {
            std::cout << "fail: tambor esta sem grafite\n";
            return;
        }

        if (grafite != nullptr)
        {
            std::cout << "fail: ja existe grafite no bico\n";
            return;
        }

        grafite = tambor.front();
        tambor.pop_front();
    }

    std::string str() const
    {
        std::ostringstream os;
        os << "calibre: " << calibre
           << ", bico: " << grafite
           << ", tambor: {" << (tambor | aux::JOIN("")) << "}";
        return os.str();
    }
};

std::ostream &operator<<(std::ostream &os, const Lapiseira &l)
{
    return os << l.str();
}

int main()
{
    aux::Chain chain;
    aux::Param param;
    Lapiseira lapiseira;

    auto FLOAT = [&param](int index)
    { return aux::to<float>(param[index]); };
    auto __INT = [&param](int index)
    { return aux::to<int>(param[index]); };

    chain["init"] = [&]()
    { lapiseira = Lapiseira(FLOAT(1)); };
    chain["show"] = [&]()
    { std::cout << lapiseira << std::endl; };
    chain["insert"] = [&]()
    { lapiseira.inserir(std::make_shared<Grafite>(FLOAT(1), param[2], __INT(3))); };
    chain["remove"] = [&]()
    { lapiseira.remover(); };
    chain["pull"] = [&]()
    { lapiseira.puxar(); };
    chain["write"] = [&]()
    { lapiseira.write(); };

    aux::execute(chain, param);
}
