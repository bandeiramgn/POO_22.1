#include <iostream>
#include <sstream>
#include <aux.hpp>

class Time {
private:
    int hour {0};
    int minute {0};
    int second {0};

public:
    Time (int hour, int minute, int second) { // todo
    }

    void setHour (int hour) { // todo
    }
    
    void setMinute (int minute) { // todo
    }

    void setSecond (int second) { // todo
    }

    int getHour () {
        return {}; // todo
    }
    
    int getMinute () {
        return {}; // todo
    }
    
    int getSecond () {
        return {}; // todo
    }
    
    void nextSecond() { // todo
    }

    std::string str() {
        std::stringstream ss;
        auto sw = std::setw(2);
        ss  << std::setfill('0') << sw << this->hour << ":" << sw << this->minute << ":" << sw << this->second;
        return ss.str();
    }
};

int main() {
    aux::Chain chain;
    aux::Param ui;
    Time time(0, 0, 0);

    chain["set"] = [&] () {
        time.setHour(aux::to<int>(ui[1]));
        time.setMinute(aux::to<int>(ui[2]));
        time.setSecond(aux::to<int>(ui[3]));
    };
    chain["show"] = [&] () { std::cout << time.str() << std::endl; };
    chain["next"] = [&] () { time.nextSecond(); };

    aux::execute(chain, ui);
};
