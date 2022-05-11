#ifndef menu_hpp
#define menu_hpp
#include "objects.hpp"
#include "kep.hpp"
#include <vector>
#include <iostream>

struct setting{
    int difficulty;
    ~setting(){
        delete this;
    }
};

class parent_app{
public:
    virtual ~parent_app(){
        objects.erase(objects.begin(),objects.end());
    };

    setting* get_settings();
    virtual void start_application()=0;
    virtual int run_();
        void give_object(object* b);
protected:
    int wsizex, wsizey;
    std::vector<object*> objects;
    setting* settings;

};


class menu : public parent_app{
public:
    menu(int wx, int wy,std::string title_){
        wsizex=wx; wsizey=wy;
        textbox* t = new textbox(10,10,title_,200,100,50);
        title=t;
    }
    ~menu(){
        objects.erase(objects.begin(),objects.end());
    }
    kep* main_menu_logo=new kep("logo.kep");
    void start_application();
    int run_(genv::event e);

private:
    genv::event io;
    textbox* title;

};
#endif // menu_hpp
