#include<iostream>

class ITransport {
public:
    virtual void drive() = 0;
};

class Car : public ITransport {
public:
    void drive() override {
        std::cout << "Car is driving\n";
    }
};

class Horse {
public:
    void walk() {
        std::cout << "Horse is walking\n";
    }
};

class People { //Client
public:
    void ride(ITransport &transport) {
        transport.drive();
    }
};

class Saddle : public ITransport {
public:
    explicit Saddle(Horse horse) : _horse(horse) {}

    void drive() override {
        _horse.walk();
    }

private:
    Horse _horse;
};

int main() {
    People man;
    Car BMW;
    man.ride(BMW);
    Horse some_horse;
    Saddle saddle_for_horse(some_horse);
    man.ride(saddle_for_horse);
    return 0;
}
