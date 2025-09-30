# Door Access Control System

This project is a simple **door access control system** simulation.  
A user can enter a password to unlock the door.  
Incorrect attempts trigger the buzzer alarm.  
Additionally, an **admin password** allows setting a new user password.

---

## 🚀 Features
- **PasswordInput**: Handles numeric keypad input  
- **Door**: Opens on correct password, closes automatically after timeout  
- **Buzzer**: Provides audible alarms on incorrect input or alerts  
- **Config**: Stores user and admin passwords  
- **Button / ButtonPresser**: Keypad simulation  
- **Timer**: Software-based timer with polling mechanism  

---

## 📂 Project Structure
```
.
├── src/
│   ├── Application.h
│   ├── Button.h
│   ├── ButtonPresser.h
│   ├── Buzzer.h
│   ├── Config.h
│   ├── Door.h
│   ├── Main.cpp
│   ├── PasswordInput.h
│   ├── Pin.h
│   └── Timer.h
└── README.md
```

---

## 🛠️ Build & Run
```bash
g++ src/Main.cpp -o doorlock
./doorlock
```

---

## 🔑 Default Passwords
- User password: **123**  
- Admin password: **234**  

> ⚠️ In real-world usage, never store passwords directly in the code.  
> Use a `.env` or external configuration file instead.

---

## 🧪 Testing
The code includes a `ButtonPresserTest` to simulate keypad sequences.  
When running `Main.cpp`, predefined sequences are automatically tested:
```cpp
static constexpr const char* sequences[] = {
    "444E, CCC", "234E", "444E, 444E"
};
```

---

## 🏗️ Design Notes

- The project is written with **abstraction** in mind and follows principles similar to **SOLID**:
  - **Application layer**: Business logic (password validation, door control, admin flow)  
  - **Hardware abstraction layer**: `Pin` and `Timer` provide an interface to hardware without binding to a specific platform  
  - **Device drivers**: `Door`, `Buzzer`, and `Button` use the abstraction layer instead of direct hardware calls  

- This separation means the system was **not written specifically for Arduino** or any microcontroller.  
  Instead:
  1. The **system and algorithms** (state machine, password handling, alarms) were designed first.  
  2. The **hardware layer** (`Pin`, `Timer`) was abstracted.  
  3. This allows the project to run as a **learning/simulation project on PC**, or be **ported to embedded boards (Arduino, STM32, etc.)** with minimal changes.  

- The design makes it easier to **extend, test, and reuse** the code across different environments.  

