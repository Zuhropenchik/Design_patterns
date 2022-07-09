#include<iostream>
class IWebSite{
public:
    virtual void draw_content() = 0;
};
class Server{
public:
    Server(const std::string & some_content): _content(some_content){}
    std::string get_content(){
        return _content;
    }
private:
    std::string _content;
};
class WebSite : public IWebSite{
public:
    WebSite(Server * server): _server(server){}
    void draw_content() override{
        std::cout << "Content: " << _content << '\n';
    }
    std::string get_content(){
        return _content;
    }
    std::string set_content(){
        _content = _server->get_content();
    }
private:
    std::string _content;
    Server * _server;
};
class Proxy: public IWebSite{
public:
    Proxy(WebSite *wb): _web_site(wb){}
    void draw_content() override{
        if(_web_site->get_content() == "")
            _web_site->set_content();
        _web_site->draw_content();
    }
private:
    WebSite *_web_site;
};
int main() {
    Server *server = new Server("Some Content");
    WebSite *wb = new WebSite(server);
    Proxy website_proxy(wb);
    website_proxy.draw_content();
    delete server;
    delete wb;
    return 0;
}
