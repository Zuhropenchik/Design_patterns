#include<iostream>
#include<map>
#include<vector>

struct Point {
    Point() : x(0), y(0) {}

    Point(int _x, int _y) : x(_x), y(_y) {}

    int x;
    int y;
};

class IDecoration {
public:
    virtual void draw(int x, int y) = 0;

    virtual void draw(Point point) = 0;
};

class Decoration : public IDecoration {
public:
    explicit Decoration(const std::string &type) : _type(type), _texture("Textures/Decoration/" + type) {}

    void draw(int x, int y) override {
        std::cout << _type << " in (" << x << ';' << y << ")\n";
    }

    void draw(Point point) override {
        std::cout << _type << " in (" << point.x << ';' << point.y << ")\n";
    }

    char get_symbol() const {
        return _type[0];
    }

private:
    std::string _type;
    std::string _texture;
};

class DecorationManager { //FlyweightFactory
public:
    void create_decoration(const std::string &type, int x, int y) {
        auto it = _flyweights.find(type);
        if (it == _flyweights.end())
            _flyweights.insert(std::make_pair(type, Decoration(type)));
        _pool.insert(std::make_pair(type, Point(x, y)));
    }

    void print_all() {
        for (auto &i: _pool) {
            _flyweights.find(i.first)->second.draw(i.second);
        }
    }

    void draw_all() {
        std::vector<std::vector<char>> game_map(10);
        for (auto &i: game_map) {
            i = std::vector<char>(10, ' ');
        }
        for (auto &i: _pool) {
            char curr_symbol = _flyweights.find(i.first)->second.get_symbol();
            auto point = i.second;
            game_map[point.y][point.x] = curr_symbol;
        }
        for (auto &i: game_map) {
            for (auto &j: i)
                std::cout << j << ' ';
            std::cout << '\n';
        }
    }

private:
    std::multimap<std::string, Point> _pool;
    std::map<std::string, Decoration> _flyweights;
};

int main() {
    DecorationManager DM;
    DM.create_decoration("Tree", 0, 1);
    DM.create_decoration("Tree", 9, 1);
    DM.create_decoration("Stone", 5, 5);
    DM.create_decoration("Tree", 4, 7);
    DM.create_decoration("Stone", 8, 4);
    DM.create_decoration("Tree", 4, 4);
    DM.create_decoration("Stone", 8, 6);
    DM.create_decoration("Tree", 0, 3);
    DM.create_decoration("Tree", 9, 8);
    DM.print_all();
    DM.draw_all();
    return 0;
}
