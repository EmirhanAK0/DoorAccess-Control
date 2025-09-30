#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include "Timer.h"
#include "Pin.h"

class Button : public Timer::Listener
{
    public:
        struct Listener {
            virtual void onClick(Button& sender) = 0;
        };
        Button(Pin& pin) : _pin(pin)
        {

        }

        Pin& getPin() {
            return _pin;
        }

        void init(Listener& listener)
        {
            _listener = &listener;
            _timer.init(*this); // 20 ms tick
            _timer.start(20);
        }

        void onTimer(Timer& sender) override {
            const auto rawPressed = ! _pin.isSet();
            const auto timestamp = sender.getTimestamp();

            switch (_state) {
                case State::Idle:
                    if (rawPressed) {
                        _state = State::Pressing;
                        _lastChange = timestamp;
                    }
                    break;

                case State::Pressing:
                    if (!rawPressed) {
                        _state = State::Idle;
                    } else if (timestamp - _lastChange >= DebouceTimeMs) {
                        _state = State::Pressed;
                        emitClick();
                    }
                    break;

                case State::Pressed:
                    if (!rawPressed) {
                        _state = State::Releasing;
                        _lastChange = timestamp;
                    }
                    break;

                case State::Releasing:
                    if (rawPressed) {
                        _state = State::Pressed;
                    } else if (timestamp - _lastChange >= DebouceTimeMs) {
                        _state = State::Idle;
                    }
                    break;
            }
        }

    private:
        enum class State { Idle, Pressing, Pressed, Releasing };
        static constexpr auto DebouceTimeMs = 20;
        Pin& _pin; 
        Listener* _listener = nullptr;
        Timer _timer;
        State _state = State::Idle;
        uint64_t _lastChange = 0;

    private:
        void emitClick()
        {
            if (_listener)
                _listener->onClick(*this);
        }
};

#endif
