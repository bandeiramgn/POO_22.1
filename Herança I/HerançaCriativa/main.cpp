#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>

class Vehicle {
    std::string color;
    std::string model;
    std::string plate;
    int year;
public:
    Vehicle(std::string plate, std::string model, std::string color, int year) : 
    color(color), model(model), plate(plate), year(year) {};
    
    std::string getColor() const { return color; }
    std::string getModel() const { return model; }
    std::string getPlate() const { return plate; }
    int getYear() const { return year; }

    friend std::ostream& operator<<(std::ostream& os, Vehicle& vehicle); 
};

class Car : public Vehicle {
    int numDoors;
public:
    Car(std::string plate, std::string model, std::string color, int year, int numDoors) :
    Vehicle(plate, model, color, year), numDoors(numDoors) {};

    int getNumDoors() const { return numDoors; }

    friend std::ostream& operator<<(std::ostream& os, Car& car);
};

class Truck : public Vehicle {
    double payloadCapacity;
public:
    Truck(std::string plate, std::string color, std::string model, int year, double payloadCapacity) :
    Vehicle(plate, model, color, year), payloadCapacity(payloadCapacity) {};

    double getPayloadCapacity() const { return payloadCapacity; }

    friend std::ostream& operator<<(std::ostream& os, Truck& truck);
};

class Parking {
    std::map<std::string, std::shared_ptr<Car>> parkingCar;
    std::map<std::string, std::shared_ptr<Truck>> parkingTruck;
public:
    Parking() {};

    void addCar(std::string plate, std::string color, std::string model, int year, int numDoors) {
        if (parkingCar.count(plate) > 0 || parkingTruck.count(plate) > 0)
            throw std::runtime_error("A placa " + plate + " está atrelada a outro veículo!");
        
        if (plate.length() < 7)
            throw std::runtime_error("Placa inválida, favor, digitar uma placa válida! (Minímo 7 caracteres)");

        auto car = std::make_shared<Car>(plate, model, color, year, numDoors);
        parkingCar[plate] = car;
    }

    void addTruck(std::string plate, std::string model, std::string color, int year, double payloadCapacity) {
        if (parkingCar.count(plate) > 0 || parkingTruck.count(plate) > 0)
            throw std::runtime_error("A placa " + plate + " está atrelada a outro veículo!");
        
        if (plate.length() < 7)
            throw std::runtime_error("Placa inválida, favor, digitar uma placa válida! (Minímo 7 caracteres)");

        auto truck = std::make_shared<Truck>(plate, model, color, year, payloadCapacity);
        parkingTruck[plate] = truck;
    }

    void removeVehicle(std::string plate) {
        auto itCar = parkingCar.find(plate);
        if (itCar == parkingCar.end())
            throw std::runtime_error("Veículo inexistente!");
        parkingCar.erase(itCar);

        auto itTruck = parkingTruck.find(plate);
        if (itTruck == parkingTruck.end())
            throw std::runtime_error("Veículo inexistente!");
        parkingTruck.erase(itTruck);
    }

    friend std::ostream& operator<<(std::ostream& os, Parking& parking);
};

std::ostream& operator<<(std::ostream& os, Car& car)
{
    os << car.getModel() << " => (Placa: " << car.getPlate() 
        << " | Cor: " << car.getColor() << " | Ano de Fabricação: " << car.getYear() 
        << " | Quantidade de Portas: " << car.getNumDoors() << ")";
    
    return os;
}

std::ostream& operator<<(std::ostream& os, Truck& truck)
{
    os << truck.getModel() << " => (Placa: " << truck.getPlate() 
        << " | Cor: " << truck.getColor() << " | Ano de Fabricação: " << truck.getYear() 
        << " | Capacidade de Carga: " << truck.getPayloadCapacity() <<  ")"; 

    return os;
}

std::ostream& operator<<(std::ostream& os, Parking& parking)
{
    os << "Carros estacionados: \n";
    for (auto [key, value] : parking.parkingCar)
      os << "    " << *value << '\n';
    os << "Caminhões estacionados: \n";
    for (auto [key, value] : parking.parkingTruck)
        os << "    " << *value << '\n';
    return os;
}

int main() {
    std::string line, cmd;
    Parking parking;
    std::cout << "================================================================\n";
    std::cout << "=                       ESTACIONAMENTO                         =\n";
    std::cout << "================================================================\n";
    std::cout << "Comandos para usar o sistema: \n" << "-------------------------\n" 
                    << "estacionarCarro Placa Cor Modelo Ano QuantidadeDePortas\n"
                    << "--------------------------------\n"
                    << "estacionarCaminhao Placa Cor Modelo Ano PesoSuportado\n" 
                    << "--------------------------------\n" 
                    << "sairEstacionamento PlacaDoVeículo\n"
                    << "--------------------------------\n"
                    << "show\n";
    std::cout << "================================================================\n";
    while(true) {
        try {
            std::getline(std::cin, line);
            std::cout << "$" << line << std::endl;
            std::stringstream ss(line);

            std::vector<std::string> ui(std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>());
            std::string cmd = ui[0];
            if(cmd == "end"){
                break;
            }else if(cmd == "estacionarCarro"){
                parking.addCar(ui[1], ui[2], ui[3], std::stoi(ui[4]), std::stoi(ui[5]));
            } else if(cmd == "estacionarCaminhao") {
                parking.addTruck(ui[1], ui[2], ui[3], std::stoi(ui[4]), std::stod(ui[5]));
            } else if(cmd == "show") {
                std::cout << parking;
            } else if(cmd == "sairEstacionamento") {
                parking.removeVehicle(ui[1]);
            } else { 
                std::cout << "comando invalido " << "[" << cmd << "]\n";
            }
        } catch(const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }    
    }
    return 0;
}

/*
    TESTES

    estacionarCaminhao abc1234 Vermelho Volvo 2020 8000
    estacionarCaminhao abc1235 preto f400 1990 5000
    estacionarCaminhao abc1236 amarelo d10 2013 6000
    estacionarCaminhao abc1237 azul d40 2000 3000
    estacionarCaminhao abc1238 branco M1113 1998 7000
    estacionarCaminhao abc1239 Vermelho f1000 1992 4000

    estacionarCarro def9876 branco corolla 2012 4
    estacionarCarro def9888 branco civic 2017 4
    estacionarCarro def9846 preto fiatMile 2002 2

    show

    estacionarCaminhao abc1235 preto f400 1990 5000
    estacionarCarro def9888 branco civic 2017 4

    show

    sairEstacionamento abc1236
    sairEstacionamento def9846
    sairEstacionamento abc1236
*/