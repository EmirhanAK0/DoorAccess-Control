#ifndef DOOR_H
#define DOOR_H

#include <iostream>
#include "Timer.h"

class Door: public Timer::Listener
{
    public:
        void init()
        {
            _timer.init(*this);  // 1 sn tick
        }

        void open()
        {
            std::cout << "Door opened\n";
            pinDoor.set();
            _remaining = 5; 
            _timer.start(1000);
        }
        void close()
        {
            std::cout << "Door closed\n";
            pinDoor.clear();
            _timer.stop();
        }
        
        void onTimer(Timer& sender) override
        {
            if (--_remaining <= 0) {
                close();
            }
        }

        private:
            Timer _timer;
            int _remaining = 0;
};

#endif
