#include<iostream>

class WebSocketManager{
public:
    void put_request(const std::string &message){
        std::cout << "To server: " << message << '\n';
    }
    void get_request(const std::string &message){
        std::cout << "From server: " << message << '\n';
    }
};
class DrawingManager{
public:
        void create_rectangle(){
            std::cout << "Rectangle is creating\n";
        }
        void create_square(){
            std::cout << "Square is creating\n";
        }
};
class UI{
public:
    void draw(){
        std::cout << "Drawing current canvas\n";
    }
};
class LiveOnCanvas{ //Facade
public:
    LiveOnCanvas(const UI & ui, const DrawingManager & dm, const WebSocketManager & wsm): _ui(ui), 
    _dm(dm), _wsm(wsm){}
    void create_rectangle(){
        _wsm.put_request("Creating rectangle");
        _wsm.get_request("Success");
        _dm.create_rectangle();
        _ui.draw();
    }
private:
    UI _ui;
    DrawingManager _dm;
    WebSocketManager _wsm;
    
};
int main() {
    UI ui;
    DrawingManager dm;
    WebSocketManager wsm;
    LiveOnCanvas for_egor(ui, dm,wsm);
    for_egor.create_rectangle();
    return 0;
}
