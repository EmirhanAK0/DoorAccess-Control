#ifndef TIMER_H
#define TIMER_H
#include <iostream>
#include <array>
#include <cstdint>
#include <cassert>

class Timer
{
    public:
        struct Listener
        {
            virtual void onTimer(Timer& sender) = 0;
        };

        void init(Listener& listener)
        {
            assert(_listener == nullptr);
            _listener = &listener;
            registerTimer(*this);
        }

        void start(int periodMs)
        {
            _prevTimestamp = _timestamp;
            _periodMs = periodMs;
            _isStarted = true;
        }

        void stop()
        {
            _isStarted = false;
        }

        static uint64_t getTimestamp()
        {
            return _timestamp;
        }

    private:
        Listener* _listener = nullptr;
        uint64_t _prevTimestamp = 0;
        unsigned int _periodMs = 0;
        bool _isStarted = false;;

    private:
        void checkAndFire()
        {
            if (! _isStarted)
                return;

            auto delta = _timestamp - _prevTimestamp;
            if (delta >= _periodMs)
            {
                _prevTimestamp += _periodMs;
                _listener->onTimer(*this);
            }
        }

    private:
        static constexpr auto MAX_TIMERS_NUMBER = 32;
        static inline std::array<Timer*, MAX_TIMERS_NUMBER> _timersArray;
        static inline int _timersNumber = 0;
        static inline uint64_t _timestamp = 0;

    private:
        static void registerTimer(Timer& timer)
        {
            assert(_timersNumber <MAX_TIMERS_NUMBER);
            _timersArray[_timersNumber++] = &timer;
        }

    public:
        static void poll()
        {
            ++_timestamp;
            auto iterator = &_timersArray[0];
            for (auto i = 0; i <_timersNumber; ++i, ++iterator)
            {
                auto timerPointer = *iterator;
                timerPointer->checkAndFire();
            }
        }
};



#endif
