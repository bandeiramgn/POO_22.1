#include "aux.hpp"
#include <iostream>
#include <memory>
#include <sstream>

class Person
{
    std::string name; // atributo
    int age;

public:
    Person(std::string name = "", int age = 0) : name{name}, age{age} {}

    int getAge() { return this->age; }
    std::string getName() { return name; }
    std::string str()
    {
        std::ostringstream oss;
        oss << name << ":" << age;
        return oss.str();
    }
};

std::ostream &operator<<(std::ostream &os, Person &p) { return os << p.str(); }

class Motorcycle
{
    std::shared_ptr<Person> person{nullptr}; // agregação
    int time{0};
    int power{1};

public:
    Motorcycle(int power = 1) : power{power} {}

    bool insertPerson(std::shared_ptr<Person> p)
    {
        if (person == nullptr)
        {
            person = p;
            return true;
        }
        std::cout << "fail: busy motorcycle\n";
        return false;
    }

    std::string honk()
    {
        int pot{1};
        while (pot < power)
        {
            pot++;
        }
        return "P" + std::string(pot, 'e') + "m";
    }

    std::shared_ptr<Person> removePerson()
    {
        if (person != nullptr)
        {
            auto personRet = person;
            person = nullptr;
            return personRet;
        }
        std::cout << "fail: empty motorcycle\n";
        return nullptr;
    }

    void buyTime(int time) { this->time = time; }

    void drive(int time)
    {
        if (person->getAge() > 10)
        {
            std::cout << "fail: too old to drive\n";
        }
        else if (this->time == 0)
        {
            std::cout << "fail: buy time first\n";
        }
        else if (this->time >= time)
        {
            this->time -= time;
        } 
        else if (this->time < time)
        {
            std::cout << "fail: time finished after " << this->time << " minutes\n";
            this->time = 0;
        }
    }

    std::string str() const
    {
        std::ostringstream os;
        os << "power:" << power << ", time:" << time;
        os << ", person:(" << (person == nullptr ? "empty" : person->str()) << ")";
        return os.str();
    }
};

std::ostream &operator<<(std::ostream &os, const Motorcycle &m)
{
    return os << m.str();
}

int main()
{
    aux::Chain chain;
    aux::Param param;

    Motorcycle m(1);

    auto __int = [&](int index)
    { return aux::to<int>(param[index]); };

    chain["show"] = [&]()
    { aux::show << m; };
    chain["leave"] = [&]()
    {
        auto person = m.removePerson();
        if (person != nullptr)
        {
            aux::show << *person;
        }
    };
    chain["honk"] = [&]()
    { aux::show << m.honk(); };
    chain["init"] = [&]()
    { m = Motorcycle(__int(1)); };
    chain["enter"] = [&]()
    {
        m.insertPerson(std::make_shared<Person>(param[1], __int(2)));
    };
    chain["buy"] = [&]()
    { m.buyTime(__int(1)); };
    chain["drive"] = [&]()
    { m.drive(__int(1)); };

    aux::execute(chain, param);
}