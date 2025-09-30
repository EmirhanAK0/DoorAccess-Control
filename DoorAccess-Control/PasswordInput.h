#ifndef PASSWORD_INPUT_H
#define PASSWORD_INPUT_H

#include "Button.h"
#include "Timer.h"
#include "Door.h"
#include "Buzzer.h"
#include <string>
#include <iostream>

Timer TMR;

class PasswordInput : public Button::Listener, public Timer::Listener
{
    public:
        struct Listener
        {
            virtual void onPassword(PasswordInput&, const std::string& password) = 0;
            virtual void onAdminRequest(PasswordInput&) { }
        };

    public:
        void init(Listener& listener)
        {
            _listener = &listener;
            _clearTimer.init(*this);
            for (auto& button: _buttons)
                button.init(*this);
        }



    private:
        Listener* _listener = nullptr;

        // Buton nesneleri
        Button _buttons[12] = {
            Button(pin0),
            pin1,
            pin2,
            pin3,
            pin4,
            pin5,
            pin6,
            pin7,
            pin8,
            pin9,
            pinEnter,
            pinClear
        };

    private:
        std::string _buffer;
        Timer _clearTimer;  
        int _remainingTime = 0;
        Buzzer _buzzer;
        int _clearPressCount = 0;

    private:
        void onClick(Button& sender) override
        {
            for (auto i = 0; i < (sizeof(_buttons)/sizeof(_buttons[0])); ++i)
            {
                auto& button = _buttons[i];
                if (&button == &sender)
                {
                    if (i >= 0 && i <= 9){
                        _buffer += static_cast<char>('0' + i);
                        _remainingTime = 5;  
                        _clearTimer.start(1000); 
                        _buzzer.pressed();
                        std::cout << "Button " << i << " pressed, buffer=\"" << _buffer << "\"\n";
                        _clearPressCount = 0;
                    }
                    else if (i == 11) { // CLEAR
                        _buffer.clear();
                        ++_clearPressCount;       
                        if (_clearPressCount >= 3) {
                            _clearPressCount = 0;
                            emitAdminRequest();
                    }
                    _remainingTime = 3; 
                    _clearTimer.start(1000); 
                    }
                    else if (i == 10) { // ENTER

                        if (!_buffer.empty()) {
                            emitPassword(_buffer);

                            std::cout << "[DEBUG] Password emitted: " << _buffer << "\n";
                        } else {
                        }
                        _buffer.clear();
                    }
                }

            }
        }

        void onTimer(Timer& sender) override
        {

            if (_remainingTime > 0 && --_remainingTime == 0) {
                _buffer.clear();
                _clearPressCount = 0;
                _clearTimer.stop();
            }
        }

    public:
        void emitPassword(const std::string& passwd)
        {
            if (_listener)
                _listener->onPassword(*this, passwd);
        }

        void emitAdminRequest()
        {
            if (_listener)
                _listener->onAdminRequest(*this);
        }
};

#endif
