#include<iostream>
#include<vector>

using std::string;
using std::vector;

class Leg {
public:
    Leg() {}

    explicit Leg(const string &type) : _type(type) {}

    string get_type() {
        return _type;
    }
    void set_type(const string &new_type){
        _type = new_type;
    }

private:
    string _type;
};

class Arm {
public:
    Arm() {}

    explicit Arm(const string &type) : _type(type) {}

    string get_type() {
        return _type;
    }
    void set_type(const string &new_type){
        _type = new_type;
    }

private:
    string _type;
};

class Eye {
public:
    Eye() {}

    explicit Eye(const string &type) : _type(type) {}

    string get_type() {
        return _type;
    }
    void set_type(const string &new_type){
        _type = new_type;
    }

private:
    string _type;
};

class Creature {
public:
    void set_legs(const vector<Leg> &legs) {
        _legs = legs;
    }

    void set_arms(const vector<Arm> &arms) {
        _arms = arms;
    }

    void set_eyes(const vector<Eye> &eyes) {
        _eyes = eyes;
    }

    void set_cover(const string &cover) {
        _cover = cover;
    }

    void set_color(const string &color) {
        _color = color;
    }

    void description() {
        std::cout << "Creature is " << _color << " and his skin is " << _cover << '\n';
        std::cout << _legs.size() << " legs:\n";
        for (auto& i: _legs)
            std::cout << i.get_type() << ' ';
        std::cout << '\n';
        std::cout << _arms.size() << " arms:\n";
        for (auto& i: _arms)
            std::cout << i.get_type() << ' ';
        std::cout << '\n';
        std::cout << _eyes.size() << " eyes:\n";
        for (auto& i: _eyes)
            std::cout << i.get_type() << ' ';
        std::cout << '\n';
    }

private:
    vector<Leg> _legs;
    vector<Arm> _arms;
    vector<Eye> _eyes;
    string _cover;
    string _color;
};

class CreatureBuilder {
public:
    virtual ~CreatureBuilder() = default;

    void create_new() {
        _creature = Creature();
    }

    Creature get() {
        Creature temp = _creature;
        create_new();
        return temp;
    }

    virtual void build_legs() = 0;

    virtual void build_arms() = 0;

    virtual void build_eyes() = 0;

    virtual void build_cover() = 0;

    virtual void build_color() = 0;

protected:
    Creature _creature;
};

class SpiderBuilder : public CreatureBuilder {
    void build_legs() override {
        _creature.set_legs(vector<Leg>(8, Leg("Arthropod")));
    }

    void build_arms() override {
        _creature.set_arms(vector<Arm>(0));
    }

    void build_eyes() override {
        _creature.set_eyes(vector<Eye>(8, Eye("Black")));
    }

    void build_cover() override {
        _creature.set_cover("Fluffy");
    }

    void build_color() override {
        _creature.set_color("Black");
    }
};

class OctopusBuilder : public CreatureBuilder {
    void build_legs() override {
        _creature.set_legs(vector<Leg>(8, Leg("Tentacles")));
    }

    void build_arms() override {
        _creature.set_arms(vector<Arm>(0));
    }

    void build_eyes() override {
        _creature.set_eyes(vector<Eye>(2, Eye("Human-like yellow")));
    }

    void build_cover() override {
        _creature.set_cover("Slimy");
    }

    void build_color() override {
        _creature.set_color("Purple");
    }
};

class CreatureEditor { //Director + Editing features
public:
    void construct_creature(CreatureBuilder* builder) {
        builder->build_legs();
        builder->build_arms();
        builder->build_eyes();
        builder->build_cover();
        builder->build_color();
        _current_creature = builder->get();
    }
    void description(){
        _current_creature.description();
    }
    void editing(){
        std::cout << "input 0 to exit, description to get information about your creature or type of editing part\n";
        string temp;
        std::cin >> temp;
        while(temp!= "0"){
            if(temp=="legs")
                legs_edit();
            else if(temp=="arms")
                arms_edit();
            else if(temp=="eyes")
                eyes_edit();
            else if(temp=="cover")
                cover_edit();
            else if(temp=="color")
                color_edit();
            else if(temp=="description")
                description();
            std::cin >> temp;
        }
    }
    void legs_edit(){
        int count;
        std::cout << "Input number of legs: ";
        std::cin >> count;
        vector<Leg> new_legs(count);
        std::string curr_type;
        std::cout << "Input types of legs:\n";
        for(int i=0; i<count; ++i) {
            std::cin >> curr_type;
            new_legs[i].set_type(curr_type);
        }
        _current_creature.set_legs(new_legs);
    }
    void arms_edit(){
        int count;
        std::cout << "Input number of arms: ";
        std::cin >> count;
        vector<Arm> new_arms(count);
        std::string curr_type;
        std::cout << "Input types of arms:\n";
        for(int i=0; i<count; ++i) {
            std::cin >> curr_type;
            new_arms[i].set_type(curr_type);
        }
        _current_creature.set_arms(new_arms);
    }
    void eyes_edit(){
        int count;
        std::cout << "Input number of eyes: ";
        std::cin >> count;
        vector<Eye> new_eyes(count);
        std::string curr_type;
        std::cout << "Input types of eyes:\n";
        for(int i=0; i<count; ++i) {
            std::cin >> curr_type;
            new_eyes[i].set_type(curr_type);
        }
        _current_creature.set_eyes(new_eyes);
    }
    void cover_edit(){
        string new_cover;
        std::cout << "Input new cover: ";
        std::cin >> new_cover;
        _current_creature.set_cover(new_cover);
    }
    void color_edit(){
        string new_color;
        std::cout << "Input new color: ";
        std::cin >> new_color;
        _current_creature.set_cover(new_color);
    }
private:
    Creature _current_creature;
};

int main() {
    CreatureEditor editor;
    auto spider = new SpiderBuilder();
    auto octopus = new OctopusBuilder();
    editor.construct_creature(spider);
    editor.editing();
    return 0;
}
