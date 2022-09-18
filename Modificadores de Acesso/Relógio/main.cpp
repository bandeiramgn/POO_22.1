#include <iostream>
#include <sstream>
#include <aux.hpp>

class Time {
    int hour {0};
    int minute {0};
    int second {0};

public:
    Time (int hour, int minute, int second) { 
        this->setHour(hour);
        this->setMinute(minute);
        this->setSecond(second);
    }
    void setHour (int hour) { 
        if (hour >= 0 && hour <= 23)
            this->hour = hour;
        else 
            std::cout << "fail: hora invalida\n";
    }
    
    void setMinute (int minute) { 
        if (minute >= 0 && minute <= 59)
            this->minute = minute;
        else    
            std::cout << "fail: minuto invalido\n";
    }

    void setSecond (int second) {
        if (second >= 0 && second <= 59)
            this->second = second;
        else 
            std::cout << "fail: segundo invalido\n";
    }

    int getHour () {
        return hour;
    }
    
    int getMinute () {
        return minute; 
    }
    
    int getSecond () {
        return second;
    }
    
    void nextSecond() { 
        if (minute == 59 && second == 59) {
            hour++;
            minute = 0;
            second = 0;
        }
        else if (second == 59) {
            minute++;
            second = 0;
        }
        else if (minute == 59) {
            second++;
        }
        else {
            second++;
        }
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
