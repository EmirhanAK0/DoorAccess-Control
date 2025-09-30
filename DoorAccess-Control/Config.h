#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <iostream>

class Config
{
    public:
        Config()
        {
            std::cout << "Config constructed\n";
        }

        std::string getPassword() const
        {
            return _password;
        }

        void setPassword(const std::string& newPassword)
        {
            _password = newPassword;
                std::cout << "Password updated to: " << _password 
              << " (Config@" << this << ")\n";
            std::cout << "Password updated to: " << _password << "\n";
        }
        std::string getAdminPassword() const {
            return _adminPassword;
}

    private:
        std::string _password = "123";   // normal kullanıcı şifresi
        std::string _adminPassword = "234"; // varsayılan şifre
        Config(const Config& other);
};

#endif
