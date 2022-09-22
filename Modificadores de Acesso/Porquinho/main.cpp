#include <iostream>
#include <vector>
#include <utility>
#include <aux.hpp>

enum Coin
{
    M10,
    M25,
    M50,
    M100
};
struct CoinDef
{
    float value;
    int volume;
};

CoinDef getDef(Coin coin)
{
    switch (coin)
    {
    case M10:
        return {0.1, 1};
    case M25:
        return {0.25, 2};
    case M50:
        return {0.50, 3};
    case M100:
        return {1, 4};
    }
    return {0, 0};
}

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
        int volCoin = getDef(coin).volume;
        float valCoin = getDef(coin).value;

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
        double valueReceived {0.0};
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
            for (int i = 0; i < (int) itens.size();i++)
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
        ss << aux::fmt(this->itens) << " : "
            << aux::fmt(value) << "$ : "
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

    auto toint = aux::to<int>;

    chain["addCoin"] = [&]()
    {
        if (par[1] == "10")
            pig.addCoin(M10);
        else if (par[1] == "25")
            pig.addCoin(M25);
        else if (par[1] == "50")
            pig.addCoin(M50);
        else if (par[1] == "100")
            pig.addCoin(M100);
    };
    chain["init"] = [&]()
    { pig = Pig(toint(par[1])); };
    chain["addItem"] = [&]()
    { pig.addItem(Item(par[1], toint(par[2]))); };
    chain["break"] = [&]()
    { pig.breakPig(); };
    chain["getCoins"] = [&]()
    { aux::show << pig.getCoins(); };
    chain["getItens"] = [&]()
    { aux::show << pig.getItens(); };
    chain["show"] = [&]()
    { aux::show << pig.str(); };

    aux::execute(chain, par);
}