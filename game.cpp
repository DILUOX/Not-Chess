#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include "game.hpp"
#include "kep.hpp"
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

}

void Graphics_engine::start_application(){
     hatter->rajz(0,0);
}

int Graphics_engine::run_(){
    draw();
    return 0;
}

void Graphics_engine::draw()const{

    const int bsx=65,xs=440,ys=60,st=65;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){

            if(j%2==0 && i%2==0){
                gout<<move_to(xs+j*st,ys+i*st)<<color(192,192,192)<<box(bsx,bsx);
            }
            else{
                gout<<move_to(xs+j*st,ys+i*st)<<color(255,255,255)<<box(bsx,bsx);
            }
            if(j%2!=0 && i%2!=0){
                gout<<move_to(xs+j*st,ys+i*st)<<color(192,192,192)<<box(bsx,bsx);
            }

        }
    }

/*    for(size_t i=0; i<figurak.size();i++){
        figurak[i]->kirajz();
    }
*/
}



