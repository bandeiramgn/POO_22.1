#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <aux.hpp>
#include <list>

enum Label { DEPOSIT, FEE, OPENING, REVERSE, WITHDRAW };

class LabelData {
    std::string name = "error detected!";

public:
    LabelData(Label operation) {
        switch (operation) 
        {
            case DEPOSIT:
                name = "deposit";
                break;
            case FEE:
                name = "fee";
                break;  
            case OPENING:
                name = "opening";
                break;
            case REVERSE:
                name = "reverse";
                break;
            case WITHDRAW:
                name = "withdraw";
                break;
            default:
                break;
        }
    }

    std::string getName() const {
        return this->name;
    }
};

class Operation {
    Label label;
    int index;
    int value;
    int balance;

public: 
    Operation(Label label, int index, int value, int balance): label(label), index(index), value(value), balance(balance) {}

    Label getLabel() const { 
        return label;
    }

    int getIndex() const { 
        return index;
    }

    int getValue() const {
        return value;
    }

    int getBalance() const { 
        return balance;
    }

    std::string str() const {   // Retorna o nome da operação a ser realizada
        return LabelData(label).getName();
    }
};

class BalanceManager {
    int balance;
    std::list<std::shared_ptr<Label>> extract;
    int nextId;

public: 
    BalanceManager(){}

    void addOperation(Label label, int value) {}

    int getBalance() const {
        return balance;
    }

    std::list<std::shared_ptr<Label>> getExtract(int indice) const {
        return {};
    }

    std::string str() const {
        return {};
    }
};

class Account {
    int id;
    BalanceManager balanceManager;

public: 

    Account(int id): id(id) {
    }

    void deposit(int valeu) {
    }

    void fee(int value) {
    }

    void reverse(int index) {
    }

    void withdraw(int value) {
    }

    BalanceManager getBalanceManager() const {
        return {};
    }

    std::string str() const {
        std::stringstream ss;
        ss << "account: " << id 
            << " balance:" << balanceManager.getBalance() 
            << std::endl; 
        return ss.str();
    }
};

using namespace aux;

int main() {
    Chain chain;
    Param ui;
    Account acc(0);

    auto INT = STR2<int>();

    chain["show"]     = [&]() { std::cout << acc.str() << std::endl; };
    chain["init"]     = [&]() { acc = Account(INT(ui[1])); };
    chain["deposit"]  = [&]() {   acc.deposit(INT(ui[1])); };
    chain["withdraw"] = [&]() {  acc.withdraw(INT(ui[1])); };
    chain["fee"]      = [&]() {       acc.fee(INT(ui[1])); };
    chain["reverse"]  = [&]() { ui | DROP(1) | MAP(INT) | FOREACH([&](int index) { acc.reverse(index); }); };
    chain["extract"]  = [&]() { acc.getBalanceManager().getExtract(INT(ui[1])) | JOIN("\n") | PRINT(); };

    execute(chain, ui);
}