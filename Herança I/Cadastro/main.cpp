#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <memory>
#include <iomanip>
#include <iterator>
#include <exception>

class Account
{
    int accId;
    std::string clientId;
    std::string typeId;
protected:
    double balance = 0.00;
public:
    Account(int accId, std::string clientId, std::string typeId, double balance = 0.00) : accId(accId), clientId(clientId), typeId(typeId)
    {
    }

    Account(){};

    virtual void updateMonthly() = 0;

    virtual void withdraw(double value)
    {
        if (balance < 0 || value > balance)
        {
            std::cout << "fail: saldo insuficiente\n";
            return;
        }

        balance -= value;
    }

    virtual void deposit(double value)
    {
        if (value < 0)
        {
            std::cout << "fail: valor invalido\n";
            return;
        }

        balance += value;
    }

    virtual void transfer(std::shared_ptr<Account> other, double value)
    {
        if (this->balance < 0 || value > this->balance)
        {
            std::cout << "fail: saldo insuficiente\n";
            return;
        }

        other->deposit(value);
        this->balance -= value;
    }

    double getBalance() const
    {
        return balance;
    }

    virtual int getId() const
    {
        return accId;
    }

    virtual std::string getClientId() const
    {
        return clientId;
    }

    std::string getTypeId() const
    {
        return typeId;
    }

    std::string str() 
    {
        std::stringstream ss;
        ss << this->getId() << ":" << this->getClientId() << ":" 
        << std::fixed << std::setprecision(2) 
        << this->getBalance() << ":" << this->getTypeId();
        return ss.str();
    }
};

std::ostream &operator<<(std::ostream& os, Account& account)
{
    return os << account.str();
}

class CheckingAccount : public Account
{
public:
    double monthlyFee{20.0};

    CheckingAccount(int accId, std::string clientId) : Account(accId, clientId, "CC")
    {
    }

    void updateMonthly()
    {
        balance -= monthlyFee;
    }
};

class SavingsAccount : public Account
{
public:
    double monthlyInterest{0.01};

    SavingsAccount(int accId, std::string clientId) : Account(accId, clientId, "CP") {}

    void updateMonthly()
    {
        balance += balance * monthlyInterest;
    }
};

class Client 
{
    std::string clientId;
    std::map<int, std::shared_ptr<Account>> accounts;

public:
    Client(std::string clientId) : clientId(clientId)
    {
    }

    void addAccount(std::shared_ptr<Account> account)
    {
        accounts[account->getId()] = account;
    }

    std::vector<std::shared_ptr<Account>> getAccounts() const
    {
        std::vector<std::shared_ptr<Account>> toAccounts;

        for (auto& [id, account] : accounts)
            toAccounts.push_back(account);

        return toAccounts;
    }

    std::string getClientId() const 
    {
        return clientId;
    };

    std::string str() const
    {
        std::stringstream ss;
        ss << getClientId() << " [";
        for (auto it = accounts.begin(); it != accounts.end(); ++it)
            ss << (it == this->accounts.begin() ? "" : ", ") << (*it).second->getId();
        ss << "]";
        return ss.str();
    }
};

std::ostream &operator<<(std::ostream& os, const Client& client)
{
    return os << client.str();
}

class Agency 
{
    std::map<int, std::shared_ptr<Account>> accounts;
    std::map<std::string, std::shared_ptr<Client>> clients;
    int nextAccountId {0};

    std::shared_ptr<Account> getAccount(int accountId) const 
    {   
        auto account = accounts.find(accountId);
        if (account == accounts.end())
            return nullptr; 
            
        return account->second;
    }
public:
    double teste = 0.00;
    Agency(){};

    void addClient(std::string clientId)
    {
        auto it = clients.find(clientId);

        if (it != clients.end())
        {
            throw "fail: cliente already exists";
            return;
        }

        auto client = std::make_shared<Client>(clientId);
        clients[clientId] = client;
        
        auto accountChecking = std::make_shared<CheckingAccount>(nextAccountId, clientId);
        accounts[nextAccountId] = accountChecking;
        client->addAccount(accountChecking);
        nextAccountId++;

        auto accountSavings = std::make_shared<SavingsAccount>(nextAccountId, clientId);    
        accounts[nextAccountId] = accountSavings;
        client->addAccount(accountSavings);
        nextAccountId++;
    }

    void deposit(int accId, double value)
    {
        try 
        {
            auto accountToDeposit = getAccount(accId);
            if (accountToDeposit != nullptr)
                accountToDeposit->deposit(value);
            else
                std::cout << "fail: conta nao encontrada\n";
        } catch (std::exception &error) {
            std::cout << "exception: " << error.what() << '\n';
        }
    }

    void withdraw(int accId, double value)
    {
        try 
        {
            auto accountToWithdraw = getAccount(accId);
            if (accountToWithdraw != nullptr)
                accountToWithdraw->withdraw(value);
            else
                std::cout << "fail: conta nao encontrada\n";
        } catch (std::exception &error) 
        {
            std::cout << "exception: " << error.what() << '\n';
        }
    }

    void transfer(int fromAccId, int toAccId, double value)
    {
        try 
        {
            auto fromAcc = getAccount(fromAccId);
            auto toAcc = getAccount(toAccId);
            if (fromAcc!= nullptr && toAcc != nullptr)
                fromAcc->transfer(toAcc, value);
            else
                std::cout << "fail: conta nao encontrada\n";
        } catch (std::exception &error) 
        {
            std::cout << "exception: " << error.what() << '\n';
        }
    }

    void updateMonthly()
    {
        for (auto& [id, account] : accounts)
            account->updateMonthly();
    }

    std::string str() 
    {
        std::stringstream ss;
        ss << "- Clients \n";
            for (auto [key, value] : clients)
                ss << *value << '\n';
        ss << "- Accounts \n";
            for (auto [key, value] : accounts)
                ss << *value << '\n';
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Agency& bank)
{
    return os << bank.str();
}

int main()
{
    Agency agency;
    std::string line, cmd;
    
    while(true)
    {
        try 
        {
            std::getline(std::cin, line);
            std::cout << "$" << line << std::endl;
            std::stringstream ss(line);
            std::vector<std::string> ui(std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>());
            std::string cmd = ui[0];

            if(cmd == "end"){
                break;
            }else if(cmd == "addCli"){
                for(std::size_t i = 1; i < ui.size(); i++)
                    agency.addClient(ui[i]);
            }else if(cmd == "saque"){
                for(std::size_t i = 2; i < ui.size(); i++)
                    agency.withdraw( stoi(ui[1]), stod(ui[i]));
            }else if(cmd == "show"){
                std::cout << agency;
            }else if(cmd == "deposito"){
                for(std::size_t i = 2; i < ui.size(); i++)
                    agency.deposit(stoi(ui[1]), stod(ui[i]));
            }else if(cmd == "transf"){
                for(size_t i = 3; i < ui.size(); i++)
                    agency.transfer(stoi(ui[1]), stoi(ui[2]), stod(ui[i]));
            }else if(cmd == "update"){
                agency.updateMonthly();
            }else{
                std::cout << "comando invalido " << "[" << cmd << "]\n";
            }
        } 
        catch(std::string e) 
        {
            std::cout << e << std::endl;
        }
    }
    return 0;
}