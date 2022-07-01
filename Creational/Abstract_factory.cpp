#include<iostream>
#include<vector>
class Legs {
public:
    virtual ~Legs() = default;
};

class SpiderLegs : public Legs {
public:
    SpiderLegs() {
        std::cout << "Spiders have 8 legs\n";
    }
};
class DogLegs : public Legs {
public:
    DogLegs() {
        std::cout << "Dogs have 4 legs\n";
    }
};

class Eyes {
public:
    virtual ~Eyes() = default;
};

class SpiderEyes : public Eyes {
public:
    SpiderEyes() {
        std::cout << "Spiders have 8 eyes\n";
    }
};
class DogEyes : public Eyes {
public:
    DogEyes() {
        std::cout << "Dogs have 2 eyes\n";
    }
};
class AnimalFactory {
public:
    virtual std::pair<Legs *, Eyes *> creating() const = 0;

    virtual ~AnimalFactory() = default;

private:
};

class SpiderFactory : public AnimalFactory {
    std::pair<Legs *, Eyes *> creating() const override {
        auto new_legs = new SpiderLegs();
        auto new_eyes = new SpiderEyes();
        return std::make_pair(new_legs, new_eyes);
    }
};

class DogFactory : public AnimalFactory {
    std::pair<Legs *, Eyes *> creating() const override {
        auto new_legs = new DogLegs();
        auto new_eyes = new DogEyes();
        return std::make_pair(new_legs, new_eyes);
    }
};

int main() {
    std::cout << "Input positive to create Dog, input negative to create Spider, input 0 to exit\n";
    int n;
    std::cin >> n;
    std::vector<AnimalFactory*> factories;
    factories.emplace_back(new DogFactory);
    factories.emplace_back(new SpiderFactory);
    while(n!=0){
        if(n>0)
            factories[0]->creating();
        else
            factories[1]->creating();
        std::cin >> n;
    }
    return 0;
}
