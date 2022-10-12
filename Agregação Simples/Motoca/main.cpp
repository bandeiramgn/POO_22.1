/*
    Atividade bem legal, resolvida a maior parte dela em sala, achei relativamente fácil e não tomou muito tempo para termina-la. Espero continuar tendo
    entendimento do conteúdo para conseguir avançar nas próximas atividades. Conteúdo de agregação foi bem digerido e com a prática vou conseguir ter mais
    domínio.´
*/

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
        if (this->time == 0)    // Faz o primeiro teste para saber se tem horas compradas
        {
            std::cout << "fail: buy time first\n";
            return;
        }
        if (person == nullptr)  // Veririficar se tem alguma pessoa na motoca
        {
            std::cout << "fail: empty motorcycle\n";
            return;
        }
        if (person->getAge() > 10)  // Verifica o teste da idade da criança
        {
            std::cout << "fail: too old to drive\n";
            return;
        }
        if (this->time >= time)     // Decrementa o tempo que a criança andou
        {
            this->time -= time;
            return;
        }
        if (this->time < time)  // Se a criança não tem tempo suficiente, ela retorna até quanto tempo a criança andou e depois parou.
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
    { aux::show << m; };
    chain["leave"] = [&]()
    {
        auto person = m.remove();
        if (person != nullptr)
        {
            aux::show << *person;
        }
    };
    chain["honk"] = [&]()
    { aux::show << m.honk(); };
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
