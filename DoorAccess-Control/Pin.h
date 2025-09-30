#ifndef PIN_H
#define PIN_H

#include <cstdint>

class Pin {
    public:
        explicit Pin(int id) : _id(id) {}

        bool isSet() const
        {
            return _isSet;
        }

        void set()
        {
            _isSet = true;
        }

        void clear()
        {
            _isSet = false;
        }

    private:
        int _id = 0;
        bool _isSet = true;
};

inline Pin pin0{0};
inline Pin pin1{1};
inline Pin pin2{2};
inline Pin pin3{3};
inline Pin pin4{4};
inline Pin pin5{5};
inline Pin pin6{6};
inline Pin pin7{7};
inline Pin pin8{8};
inline Pin pin9{9};
inline Pin pinEnter{10};
inline Pin pinClear{11};
inline Pin pinDoor{12};
inline Pin pinBuzzer{13};

#endif
