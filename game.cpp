#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include "game.hpp"
using namespace genv;
using namespace std;

int switch_ =0;
///jatekter fuggvenyei

void Jatek::indit(){
    gameover=0;
    veresegvan=0;
}



int Jatek::futtatas(event eva){

    if(eva.type==ev_timer)
    {
        ido++;
    }
    return 1;


}

void Jatek::rajzolas()
{
   // ora->ofunction();

}

int Jatek::vereseg(){
    if(gameover){
        if(!switch_){
        gameoverscreen->rajz(0,0);
            switch_ =1;
            veresegvan=1;
        }

        return -1;
    }
    else return 0;
}

void Jatek::rekorddontes(){
    cout<<rekord<<endl;
    if(pontok>rekord){
        ofstream m;
        m.open("rekord.txt");
        m<<to_string(pontok);
        m.close();
        rekord=pontok;
    }
}







