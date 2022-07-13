#include<iostream>
#include<vector>

class JSONComponent {
public:
    explicit JSONComponent(const std::string &content) : _content(content) {}

    virtual ~JSONComponent() = default;

    virtual void print() = 0;

    std::string get_content() {
        return _content;
    }

protected:
    std::string _content;
};

class Variable : public JSONComponent {
public:
    explicit Variable(const std::string &content) : JSONComponent(content) {}

    explicit Variable(const std::string &content, const std::string &value) :
            JSONComponent(content), _value(value) {}

    void print() override {
        std::cout << "\"" << _content << "\": " << _value << '\n';
    }

private:
    std::string _value;
};

class Complex : public JSONComponent {
public:
    explicit Complex(const std::string &content) : JSONComponent(content) {}

    ~Complex() override {
        for (auto &comp: components)
            delete comp;
    }

    void add_comp(JSONComponent *new_comp) {
        components.emplace_back(new_comp);
    }

    void delete_comp(const std::string &content_to_del) {
        for (int i = 0; i < components.size(); ++i) {
            if (components[i]->get_content() == content_to_del) {
                components.erase(components.begin() + i);
                return;
            }
        }
    }

protected:
    std::vector<JSONComponent *> components;
};

class List : public Complex {
public:
    explicit List(const std::string &content) : Complex(content) {}

    void print() override {
        std::cout << "\"" << _content << "\":\n";
        std::cout << "[\n";
        for (auto &comp: components)
            comp->print();
        std::cout << "]\n";
    }
};

class Class : public Complex {
public:
    explicit Class(const std::string &content) : Complex(content) {}

    void print() override {
        std::cout << "\"" << _content << "\":\n";
        std::cout << "{\n";
        for (auto &comp: components)
            comp->print();
        std::cout << "}\n";
    }
};

int main() {
    Class student("Student");
    student.add_comp(new Variable("Name", "Zakhar"));
    student.add_comp(new Variable("Age", "19"));
    List *marks = new List("marks");
    marks->add_comp(new Variable("Math", "4"));
    marks->add_comp(new Variable("ITC", "5"));
    marks->add_comp(new Variable("English", "4"));
//    marks->delete_comp("English");
    student.add_comp(marks);
    student.print();
    return 0;
}
