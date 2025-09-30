#ifndef APPLICATION_H
#define APPLICATION_H

#include "PasswordInput.h"
#include "Config.h"
#include "Door.h"
#include "Buzzer.h"
#include "Timer.h"
#include <string>
#include <iostream>



class Application:
    PasswordInput::Listener
{
    public:
        Application()
        {
        }
        
        void init()
        {
            _passwordInput.init(*this);
            _buzzer.init();
            _door.init();
            
        }

    void test(const std::string& passwd)
    {
        _passwordInput.emitPassword(passwd);
    }
    private:
        static constexpr auto MaxAttemptNumber = 3;


    private:
        Config _config;
        PasswordInput _passwordInput;
        Door _door;
        Buzzer _buzzer;
        int _incorrectPasswordNumber = 0;
        std::string _newPasswordCandidate;
        enum class State { Normal, AwaitingAdminPassword, AwaitingNewPassword };
        State _state = State::Normal;

    void onAdminRequest(PasswordInput& sender) override
    {
        _state = State::AwaitingAdminPassword;
    }

    void onPassword(PasswordInput& sender, const std::string& password) override
    {


        switch (_state)
        {
            case State::Normal:
                if (checkPassword(password)) {
                    _door.open();
                    _buzzer.stop();
                    _incorrectPasswordNumber = 0; 

                } else {
                    countIncorrectPassword();
                    _buzzer.startShortAlarm();

                }
                break;
        
            case State::AwaitingAdminPassword:
                if (password == _config.getAdminPassword()) {

                    _state = State::AwaitingNewPassword;
                    std::cout << "Admin access granted. Please enter new password.\n";

                } else {

                    _buzzer.startShortAlarm();
                    _state = State::Normal; 
                }
                break;
        
            case State::AwaitingNewPassword:
                _config.setPassword(password);
                std::cout << "New password set.\n";
                _state = State::Normal;
                break;
        
            default:
                std::cout << "[ERROR] Unknown state!\n";
                _state = State::Normal;
                break;
        }
    }


    private:
        void countIncorrectPassword()
        {
            if (++_incorrectPasswordNumber >= MaxAttemptNumber)
            {
                _incorrectPasswordNumber = 0;
                _buzzer.startNormalAlarm();
                
            }

            std::cout << "Password attempt: " << _incorrectPasswordNumber << "\n";

        }

        bool checkPassword(const std::string& password)
        {
    std::cout << "Checking password: input=" << password 
              << " vs stored=" << _config.getPassword()
              << " (Config@" << &_config << ")\n";
            return password == _config.getPassword();
        }
    

};


#endif
