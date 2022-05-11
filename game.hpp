#ifndef     GAME_HPP
#define     GAME_HPP
#include "graphics.hpp"
#include "kep.hpp"
#include <vector>
#include <random>
#include <fstream>
#include "objects.hpp"
//#include <iostream>


struct pozi{
    int _x, _y;
};

class sakkfigura{
public:
    virtual void kirajz()const;
    virtual pozi getpozi();
    virtual void setparameter(int parameter);
    void getio(genv::event evnt);
    virtual ~sakkfigura()=default;

protected:                   // current_x current_y
    int x, y;
    char r,g,b;
};

class Jatek{
public:
    Jatek(const int wx, const int wy){
        screen_x=wx;
        screen_y=wy;
        ido=0;
        pontok=0;
        gameover=false;
        std::fstream f("rekord.txt");
        f>>rekord;
        f.close();

        textbox * ora_ = new textbox(5,5,"Idő: ",255,255,255,0);
        ora_=ora_;

        kep * deathlog = new kep("gameover.kep");
        gameoverscreen = deathlog;
    }
    ~Jatek(){

    }
    void indit();
    int futtatas(genv::event eva);
    void rajzolas();
    int vereseg();
    void rekorddontes();
    bool veresegvan=0;


private:
    genv::event e;
    int screen_x,screen_y, rekord,ido,pontok;

    kep * gameoverscreen;

    bool gameover;

    textbox * ora;

};


#endif // game_hpp
