#include <iostream>
#include <sstream>
#include <iomanip>
#include <aux.hpp>

class Time
{
    int hour{0};
    int minute{0};
    int second{0};

public:
    Time(int hour = 0, int minute = 0, int second = 0)
    {
        setHour(hour);
        setMinute(minute);
        setSecond(second);
    }
    void setHour(int hour)
    {
        if (hour >= 0 && hour <= 23)
            this->hour = hour;
        else
            std::cout << "fail: hora invalida\n";
    }

    void setMinute(int minute)
    {
        if (minute >= 0 && minute <= 59)
            this->minute = minute;
        else
            std::cout << "fail: minuto invalido\n";
    }

    void setSecond(int second)
    {
        if (second >= 0 && second <= 59)
            this->second = second;
        else
            std::cout << "fail: segundo invalido\n";
    }

    int getHour()
    {
        return hour;
    }

    int getMinute()
    {
        return minute;
    }

    int getSecond()
    {
        return second;
    }

    void nextSecond()
    {
        if (hour == 23 && minute == 59 && second == 59)
        {
            hour = 0;
            minute = 0;
            second = 0;
        }
        else if (minute == 59 && second == 59)
        {
            hour++;
            minute = 0;
            second = 0;
        }
        else if (second == 59)
        {
            minute++;
        }
        else if (minute == 59)
        {
            second++;
        }
        else
        {
            second++;
        }
    }

    std::string str()
    {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << hour << ":"
           << std::setfill('0') << std::setw(2) << minute << ":"
           << std::setfill('0') << std::setw(2) << second;
        return ss.str();
    }
};

int main()
{
    aux::Chain chain;
    aux::Param param;
    Time time;

    auto INT = aux::STR2<int>();

    chain["set"] = [&]()
    {
        time.setHour(INT(param[1]));
        time.setMinute(INT(param[2]));
        time.setSecond(INT(param[3]));
    };
    chain["init"] = [&]()
    {
        time = Time(INT(param[1]), INT(param[2]), INT(param[3]));
    };
    chain["show"] = [&]()
    {
        std::cout << time.str() << '\n';
    };
    chain["next"] = [&]()
    {
        time.nextSecond();
    };

    aux::execute(chain, param);
}
