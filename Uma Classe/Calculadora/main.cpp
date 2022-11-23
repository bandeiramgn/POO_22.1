#include <iostream>
#include <sstream>
#include <iomanip>
#include <aux.hpp>

struct Calculator
{
    int batteryMax;
    int battery;
    float display;

    Calculator(int batteryMax) : batteryMax(batteryMax)
    {
        battery = 0;
        display = 0.0;
    }

    void chargeBattery(int value) // 4 battery \ 5 bM \ charge 3
    {

        if (value > batteryMax)
        {
            battery = batteryMax;
            return;
        }

        battery += value;
        if (battery > batteryMax)
        {
            battery = batteryMax;
        }
    }

    bool useBattery()
    {
        if (battery == 0)
        {
            std::cout << "fail: bateria insuficiente\n";
            return false;
        }

        battery -= 1;
        return true;
    }

    void sum(int a, int b)
    {
        if (useBattery())
        {
            display = a + b;
        }
    }

    void division(int num, int den)
    {
        if (den == 0 || num == 0)
        {
            std::cout << "fail: divisao por zero\n";
            useBattery();
            return;
        }

        if (useBattery())
        {
            display = (float)num / den;
        }
    }

    std::string str()
    {
        std::stringstream ss;
        ss << "display = " << std::fixed << std::setprecision(2) << this->display;
        ss << ", battery = " << this->battery;
        return ss.str();
    }
};

std::ostream &operator<<(std::ostream &os, Calculator c)
{
    return (os << c.str());
}

int main()
{
    Calculator c(0);
    aux::Chain chain;
    aux::Param ui;

    // função para obter um parâmetro convertido para inteiro
    auto par2int = LAMBDAE(&ui, index, ui.at(index) | aux::STR2<int>()); // converte de string para int

    chain["show"] = [&]()
    { std::cout << c << std::endl; };
    chain["init"] = [&]()
    { c = Calculator(par2int(1)); };
    chain["charge"] = [&]()
    { c.chargeBattery(par2int(1)); };
    chain["sum"] = [&]()
    { c.sum(par2int(1), par2int(2)); };
    chain["div"] = [&]()
    { c.division(par2int(1), par2int(2)); };

    aux::execute(chain, ui);
}
