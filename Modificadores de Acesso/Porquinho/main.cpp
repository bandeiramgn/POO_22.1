/*
    Atividade mais desafiadora que as demais, porém, bem legal de se fazer. Demorei cerca de 3 horas para fazer ela usando alguns conceitos ensinados até agora como pro exemplo
    usando o stringstream.

    Tentei deixar a atividade o melhor indentada possível para facilitar o entendimento dos códigos.
*/

#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>
#include <aux.hpp>

enum Cents
{
    C10,
    C25,
    C50,
    C100
};

class Coin
{
    float value;
    int volume;
    std::string label;

public:
    Coin(Cents v)
    {
        switch (v)
        {
        case C10:
            value = 0.10;
            volume = 1;
            label = "C10";
            break;
        case C25:
            value = 0.25;
            volume = 2;
            label = "C25";
            break;
        case C50:
            value = 0.50;
            volume = 3;
            label = "C50";
            break;
        case C100:
            value = 1.0;
            volume = 4;
            label = "C100";
            break;
        }
    }
    float getValue() const
    {
        return value;
    }
    int getVolume() const
    {
        return volume;
    }
    std::string getLabel() const
    {
        return label;
    }
};

class Item
{
    std::string label;
    int volume;

public:
    Item(std::string label, int volume) : label(label), volume(volume)
    {
    }

    int getVolume() const
    {
        return volume;
    }

    std::string getLabel() const
    {
        return label;
    }

    void setVolume(int volume)
    {
        this->volume = volume;
    }

    void setLabel(std::string label)
    {
        this->label = label;
    }

    std::string str() const
    {
        return {}; // todo
    }
};

std::ostream &operator<<(std::ostream &os, const Item &item)
{
    return os << item.str();
}

class Pig
{
    std::vector<std::string> itens;
    double value;
    int volume;
    int volumeMax;
    bool broken;

public:
    Pig(int volumeMax = 0) : volumeMax(volumeMax)
    {
        this->value = 0;
        this->volume = 0;
        this->broken = false;
    }

    bool addCoin(Coin coin)
    {
        int volCoin = coin.getVolume();
        float valCoin = coin.getValue();

        if (!broken && this->volume < volumeMax)
        {
            if (volCoin + volume <= volumeMax)
            {
                this->value += valCoin;
                this->volume += volCoin;
                return true;
            }
            else
            {
                std::cout << "fail: the pig is full\n";
                return false;
            }
        }
        if (broken)
        {
            std::cout << "fail: the pig is broken\n";
            return false;
        }

        return false;
    }

    bool addItem(Item item)
    {
        std::string nameItem = item.getLabel();
        int volItem = item.getVolume();
        {
            if (!broken && this->volume < volumeMax)
            {
                if (volItem + volume <= volumeMax)
                {
                    this->itens.push_back(nameItem);
                    this->volume += volItem;
                    return true;
                }
                else
                {
                    std::cout << "fail: the pig is full\n";
                    return false;
                }
            }
            if (broken)
            {
                std::cout << "fail: the pig is broken\n";
                return false;
            }
        }
        return false;
    }

    bool breakPig()
    {
        volume = 0;
        return this->broken = true;
    }

    double getCoins()
    {
        double valueReceived{0.0};
        if (broken)
        {
            valueReceived = value;
            value = 0;
            return valueReceived;
        }
        else
        {
            std::cout << "fail: you must break the pig first\n";
            return {valueReceived};
        }
        return {valueReceived};
    }

    std::string getItens()
    {
        if (broken)
        {
            std::stringstream ss;

            ss << "[";
            for (int i = 0; i < (int)itens.size(); i++)
            {
                ss << (i == 0 ? "" : ", ") << itens[i];
            }
            ss << "]";

            itens.erase(itens.begin(), itens.end());

            return ss.str();
        }
        else
        {
            std::cout << "fail: you must break the pig first\n";
            return "[]";
        }
        return "[]";
    }

    std::string str() const
    {
        std::stringstream ss;
        ss << (this->itens | aux::FMT()) << " : "
           << std::fixed << std::setprecision(2) << value << "$ : "
           << volume << "/" << volumeMax << " : "
           << (broken ? "broken" : "unbroken");
        return ss.str();
    }
};

std::ostream &operator<<(std::ostream &os, const Pig &pig)
{
    return os << pig.str();
}

int main()
{
    aux::Chain chain;
    aux::Param par;

    Pig pig;

    auto toint = aux::STR2<int>();
    auto fmtdouble = aux::PIPE(LAMBDA(x, x | aux::STR("%.2f")));

    chain["addCoin"] = [&]()
    {
        if (par[1] == "10")
            pig.addCoin(Coin(C10));
        else if (par[1] == "25")
            pig.addCoin(Coin(C25));
        else if (par[1] == "50")
            pig.addCoin(Coin(C50));
        else if (par[1] == "100")
            pig.addCoin(Coin(C100));
    };
    chain["init"] = [&]()
    { pig = Pig(toint(par[1])); };
    chain["addItem"] = [&]()
    { pig.addItem(Item(par[1], toint(par[2]))); };
    chain["break"] = [&]()
    { pig.breakPig(); };
    chain["getCoins"] = [&]()
    { pig.getCoins() | fmtdouble | aux::PRINT(); };
    chain["getItems"] = [&]()
    { pig.getItems() | aux::PRINT(); };
    chain["show"] = [&]()
    { pig.str() | aux::PRINT(); };

    aux::execute(chain, par);
}