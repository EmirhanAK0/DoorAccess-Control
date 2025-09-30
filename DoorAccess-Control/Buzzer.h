#ifndef BUZZER_H
#define BUZZER_H

#include <iostream>
#include "Timer.h"
#include "Pin.h"
#include "PasswordInput.h"

class Buzzer : public Timer::Listener
{
public:
    void init()
    {
        std::cout << "Initialize buzzer\n";
        _timer.init(*this);
    }

    void startNormalAlarm()
    {
        std::cout << "Buzzer alarm started\n";
        _remainingTime = 3000;
        _state = false; 
        _timer.start(500);
    }

    void stop()
    {
        std::cout << "Buzzer silenced\n";
        pinBuzzer.clear();
        _timer.stop();
        _remainingTime = 0;
    }

    void startShortAlarm()
    {
        std::cout << "Buzzer short alarm started\n";
        _remainingTime = 1000;
        _state = false;
        _timer.start(500);
    }
    void pressed()
    {
        
        pinBuzzer.set();
        pinBuzzer.clear();
    }

    void onTimer(Timer& sender) override
    {
        _remainingTime -= 200;
        _state = !_state;
        if (_state) {
            pinBuzzer.set();
            std::cout << "Buzzer ON\n";
        } else {
            pinBuzzer.clear();
            std::cout << "Buzzer OFF\n";
        }
        if (_remainingTime <= 0) {
            stop();
        }
    }

private:
    Timer _timer;
    int _remainingTime = 0; // ms
    bool _state = false;
};

#endif
