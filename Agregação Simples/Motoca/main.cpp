
#include <iostream>
#include <sstream>
#include <memory>
#include <aux.hpp>

class Person
{
    std::string name; // atributo
    int age;

public:
    Person(std::string name = "", int age = 0) : name(name), age(age)
    {
    }

    Person(int age) : age(age)
    {
    }

    int getAge()
    {
        return this->age;
    }
    std::string getName()
    {
        return this->name;
    }
    std::string str()
    {
        std::ostringstream oss;
        oss << name << ":" << age;
        return oss.str();
    }
};
std::ostream &operator<<(std::ostream &os, Person &p)
{
    return os << p.str();
}

class Motorcycle
{
    std::shared_ptr<Person> person{nullptr}; // agregação
    int time{0};
    int power{1};

public:
    Motorcycle(int power = 1) : power(power)
    {
    }

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

    std::shared_ptr<Person> remove()
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

    void buyTime(int time)
    {
        this->time += time;
    }

    void drive(int time)
    {
        if (this->time == 0)
        {
            std::cout << "fail: buy time first\n";
            return;
        }
        if (person == nullptr)
        {
            std::cout << "fail: empty motorcycle\n";
            return;
        }
        if (person->getAge() > 10)
        {
            std::cout << "fail: too old to drive\n";
            return;
        }
        if (this->time >= time)
        {
            this->time -= time;
            return;
        }
        if (this->time < time)
        {
            std::cout << "fail: time finished after " << this->time << " minutes\n";
            this->time = 0;
            return;
        }
    }

    std::string str()
    {
        std::ostringstream os;
        os << "power:" << power << ", time:" << time;
        os << ", person:(" << (person == nullptr ? "empty" : person->str()) << ")";
        return os.str();
    }
};

std::ostream &operator<<(std::ostream &os, Motorcycle m)
{
    return os << m.str();
}

int main()
{
    aux::Chain chain;
    aux::Param param;

    Motorcycle m(1);

    auto INT = aux::to<int>;

    chain["show"] = [&]()
    { m | aux::PRINT(); };
    chain["leave"] = [&]()
    {
        auto person = m.remove();
        if (person != nullptr)
        {
            *person | aux::PRINT();
        }
    };
    chain["honk"] = [&]()
    { m.honk() | aux::PRINT(); };
    chain["init"] = [&]()
    { m = Motorcycle(INT(param.at(1))); };
    chain["enter"] = [&]()
    { m.insertPerson(std::make_shared<Person>(param.at(1), INT(param.at(2)))); };
    chain["buy"] = [&]()
    { m.buyTime(INT(param.at(1))); };
    chain["drive"] = [&]()
    { m.drive(INT(param.at(1))); };

    aux::execute(chain, param);
}