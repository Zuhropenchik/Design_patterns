#include<iostream>

class IForm {
public:
    virtual void draw(size_t size) = 0;
};

class Pyramid : public IForm {
public:
    void draw(size_t size) override {
        for (size_t i = 0; i < size; i++) {
            size_t count = 1 + i * 2;
            size_t space = (1 + (size - 1) * 2 - count) / 2;
            for (size_t j = 0; j < space; ++j)
                std::cout << ' ';
            for (size_t j = 0; j < count; ++j)
                std::cout << '0';
            for (size_t j = 0; j < space; ++j)
                std::cout << ' ';
            std::cout << '\n';
        }
    }
};

class DecoratorForm : public IForm {
public:
    explicit DecoratorForm(IForm * form): _form(form) {}

protected:
    IForm *_form;
};

class FormWithTopLine : public DecoratorForm {
public:
    explicit FormWithTopLine(IForm * form): DecoratorForm(form) {}
    void draw(size_t size) override{
        for(size_t j=0; j<2*size-1; ++j)
            std::cout << '_';
        std::cout << '\n';
        _form->draw(size);
    }
};

class FormWithBottomLine : public DecoratorForm {
public:
    explicit FormWithBottomLine(IForm * form): DecoratorForm(form) {}
    void draw(size_t size) override{
        _form->draw(size);
        for(size_t j=0; j<2*size-1; ++j)
            std::cout << '_';
        std::cout << '\n';
    }
};

int main() {
    Pyramid * form = new Pyramid();
    FormWithBottomLine * form_with_frames = new FormWithBottomLine(new FormWithTopLine(form));
    form->draw(4);
    form_with_frames->draw(2);
    delete form;
    delete form_with_frames;
    return 0;
}
