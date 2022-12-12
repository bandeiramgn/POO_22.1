#include <iostream>

// using namespace std;

// struct Animal
// {
//     string tipo;

//     virtual string str() const
//     {
//         return "Animal " + tipo;
//     }
// };

// struct Pet : Animal
// {
//     string nome;

//     string str() override const
//     {
//         return tipo + " " + nome;
//     }
// };

// void mostrar(Animal animal) //
// {
//     cout << animal.str() << '\n';
// }

// int main()
// {
//     Pet pet;
//     pet.nome = "tom";
//     pet.tipo = "gato";
//     cout << pet.str() << '\n';

//     Animal &bixo = pet;
//     cout << bixo.str() << '\n';

//     return 0;
// }

void incrementAndPrint()
{
    static int value{1}; // automatic duration by default
    ++value;
    std::cout << value << '\n';
} // value is destroyed here

int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();

    return 0;
}
