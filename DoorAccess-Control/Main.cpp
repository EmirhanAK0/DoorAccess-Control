#include "Application.h"
#include "Timer.h"
#include "Pin.h"
#include <chrono>
#include <thread>
#include <iostream>
#include "ButtonPresser.h"

namespace Test
{

    struct ButtonPresserTest: ButtonPresser::Listener
    {
        static constexpr const char* sequences[] = {
            "444E, CCC", "234E", "444E, 444E"
        };

        ButtonPresser _buttonPresser;
        int _sequenceIndex = 0;

        void onPress(::ButtonPresser& sender, const std::string& sequence) override
        {
            sendNextSequence();
        }

        void init()
        {
            _buttonPresser.init(*this);
            _sequenceIndex = 0;
            sendNextSequence();
        }

        void sendNextSequence()
        {
            if (_sequenceIndex < sizeof(sequences) / sizeof(sequences[0]))
            {
                const auto seq = sequences[_sequenceIndex++];
                _buttonPresser.press(seq);
            }
        }

    };
}


int main()
{
    static Application app;
    app.init();

    {
        static Test::ButtonPresserTest test;
        test.init();
    }

    while (true)
    {
        Timer::poll();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}
