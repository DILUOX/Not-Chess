#ifndef     GAME_HPP
#define     GAME_HPP
#include "graphics.hpp"
#include "kep.hpp"
#include <vector>
#include <random>
#include <fstream>
#include "menu.hpp"
#include "objects.hpp"
//#include <iostream>


struct pozi{
    int _x, _y;
};
/*
class sakkfigura{
public:
    virtual void kirajz()const;
    virtual pozi getpozi();
    void getio(genv::event evnt);
    virtual void lep();
    virtual void ut();
    virtual void halal();
    virtual ~sakkfigura()=default;

protected:                   // current_x current_y
    int x, y,xkord,ykord;
    bool szin,eletben;
    std::vector<kep*> kinezetek;
};

class bastya : public sakkfigura{
public:
    bastya(bool szin_,int x_k,int y_k,std::string filename_){
        eletben=1;
        szin=szin_;
        xkord=x_k;
        ykord=y_k;
        x=xkord*65;
        y=ykord*65;
        std::vector<std::string> szinek = {"1","2","3","4"};
        for(size_t i=0;i<szinek.size();i++){
            kep * babu = new kep(filename_+szinek[i]);
            kinezetek.push_back(babu);
        }

    }
    virtual void lep()override;
    virtual void ut()override;
    virtual void halal()override;

};

*/




class Jatek{
public:
    Jatek(const int wx, const int wy){
        screen_x=wx;
        screen_y=wy;
        ido=0;
        pontok=0;
        gameover=false;

        textbox * ora_ = new textbox(5,5,"Idő: ",255,255,255,0);
        ora_=ora_;

        kep * deathlog = new kep("gameover.kep");
        gameoverscreen = deathlog;
    }
    ~Jatek(){

    }
    void indit();
    int futtatas(genv::event eva);
    int vereseg();
    void rekorddontes();
    bool veresegvan=0;


private:
    genv::event e;
    int screen_x,screen_y,ido,pontok;

    kep * gameoverscreen;

    bool gameover;

    textbox * ora;

};



class Graphics_engine : public parent_app{
public:
    Graphics_engine(int wx, int wy){
        wsizex=wx;
        wsizey=wy;
        std::vector<std::string> figuranevek = {"bastya","futo","kiraly","kiralyn","lo","paraszt"};

        for(size_t i=0;i<figuranevek.size();i++){
            if(figuranevek[i]=="bastya"){
        //        bastya * b=new bastya(0,1,1,figuranevek[i]);
        //        figurak.push_back(b);
            }
        }
//        std::cout<<figurak.size();
    }
    virtual void start_application()override;
    virtual int run_() override;
    void draw()const;
private:
    kep * hatter = new kep("game_bckgrnd.kep");
    std::fstream f;
 //   std::vector<sakkfigura*> figurak;

};


#endif // game_hpp
