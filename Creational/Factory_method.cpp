#include<iostream>
#include<vector>
#include<ctime>
#include<cmath>

using std::vector;

class Enemy {
public:
    virtual ~Enemy() = default;
};

class Goblin : public Enemy {
public:
    Goblin() {
        std::cout << "Goblin\n";
    }
};

class Orc : public Enemy {
public:
    Orc() {
        std::cout << "Orc\n";
    }
};

class Ogre : public Enemy {
public:
    Ogre() {
        std::cout << "Ogre\n";
    }

};
class Dragon : public Enemy {
public:
    Dragon() {
        std::cout << "Dragon\n";
    }

};

class Creator {
public:
    Creator(){}
    Creator(int _optimal_diff){
        optimal_diff = _optimal_diff;
        priority = 10.;

    }
    virtual void update_diff(int new_diff){
        priority = 10. - (1./5)*pow((new_diff-optimal_diff),2);
        if(priority<0)
            priority = 0;
    }
    virtual ~Creator(){};

    virtual double get_priority() { return priority; }

    virtual Enemy *creating() const = 0;

protected:
    double priority;
    int optimal_diff = 0;
};

class GoblinCreator : public Creator {
public:
    GoblinCreator(int _optimal_diff): Creator(_optimal_diff){}

    Enemy *creating() const override {
        return new Goblin();
    }
};

class OrcCreator : public Creator {
public:
    OrcCreator(int _optimal_diff): Creator(_optimal_diff){}

    Enemy *creating() const override {
        return new Orc();
    }
};

class OgreCreator : public Creator {
public:
    OgreCreator(int _optimal_diff): Creator(_optimal_diff){}

    Enemy *creating() const override {
        return new Ogre();
    }
};
class DragonCreator : public Creator {
public:
    DragonCreator(int _optimal_diff): Creator(_optimal_diff){}

    Enemy *creating() const override {
        return new Dragon();
    }
};

int main() {
    srand(time(nullptr));
    vector<Creator *> creators;
    creators.emplace_back(new GoblinCreator(0));
    creators.emplace_back(new OrcCreator(4));
    creators.emplace_back(new OgreCreator(6));
    creators.emplace_back(new DragonCreator(10));
    for(auto &i: creators)
        i->update_diff(3);
    vector<double> last_positions(creators.size(), creators[0]->get_priority());
    std::cout << last_positions[0] << ' ';
    for (int i = 1; i < creators.size(); ++i) {
        last_positions[i] = last_positions[i - 1] + creators[i]->get_priority();
        std::cout << last_positions[i] << ' ';
    }
    std::cout << '\n';
    for (int i = 0; i < 10; ++i) {
        double temp = (double)(rand() % (int)(10*last_positions[last_positions.size() - 1] + 1))/10;
        std::cout << temp << ' ';
        for(int j=0; j<last_positions.size(); ++j){
            if(temp<last_positions[j]) {
                creators[j]->creating();
                break;
            }
        }
    }
    return 0;
}

