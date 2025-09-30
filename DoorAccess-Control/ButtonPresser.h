#ifndef BUTTON_PRESSER_H
#define BUTTON_PRESSER_H

#include <string>
#include <iostream>
#include "Timer.h"
#include "Pin.h"

struct ButtonPresser: Timer::Listener
{
    struct Listener
    {
        virtual void onPress(ButtonPresser& sender, const std::string& sequence) = 0;
    };

    void init(Listener& listener)
    {
        _listener = &listener;
        _timer.init(*this);
    }

    void emitPress()
    {
        if (_listener)
            _listener->onPress(*this, _sequence);
    }

    void press(const std::string& sequence)
    {
        _sequence = sequence;
        _index = 0;
        _buttonState = ButtonState::Released;
        pressNextButton();
    }

    void pressNextButton()
    {
        if (_index <_sequence.size())
        {
            const auto ch = _sequence[_index];
            pressButton(ch);
            _buttonState = ButtonState::Pressed;
            _timer.start(100);
        }
        else
        {
            emitPress();
        }
    }

    void onTimer(Timer&) override
    {
        _timer.stop();
        if (_buttonState == ButtonState::Pressed)
        {
            const auto ch = _sequence[_index++];
            releaseButton(ch);
            _timer.start(100);
            _buttonState = ButtonState::Released;
        }
        else 
        {
            pressNextButton();
        }
    }

    void pressButton(char ch)
    {
        setButton(ch, true);
    }

    void releaseButton(char ch)
    {
        setButton(ch, false);
    }

    void setButton(char ch, bool isSet)
    {
        struct CharPinPair
        {
            char ch;
            Pin* pin;
        };

        static constexpr CharPinPair pins[] =
        {
            { '0', &pin0 },
            { '1', &pin1 },
            { '2', &pin2 },
            { '3', &pin3 },
            { '4', &pin4 },
            { '5', &pin5 },
            { '6', &pin6 },
            { '7', &pin7 },
            { '8', &pin8 },
            { '9', &pin9 },
            { 'C', &pinClear },
            { 'E', &pinEnter },
        };

        Pin* pin = nullptr;
        for (auto& item: pins)
        {
            if (item.ch == ch)
            {
                if (isSet)
                    item.pin->set();
                else
                    item.pin->clear();
                break;
            }
        }
    }

    enum class ButtonState
    {
        Released,
        Pressed
    };

    Listener* _listener = nullptr;
    std::string _sequence;
    int _index = 0;
    Timer _timer;
    ButtonState _buttonState = ButtonState::Released;

};


#endif 

