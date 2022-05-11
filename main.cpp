#include "graphics.hpp"
#include "menu.hpp"
#include "game.hpp"
#include <vector>
#include <cstdlib>
#include <string>

using namespace genv;
using namespace std;

const int wx=1400;
const int wy=720;


string cuttitles(string& title)   //Adott meretu szoveget darabol szet ";" jelek alapjan
{
    string btittle="";
    btittle=title.substr(0,title.find(';'));
    title=title.substr(title.find(';')+1,title.length());
    return btittle;
}


void generate_buttons(menu* m,int db,string& titles){           //tettszoleges mennyisegu gombot general; a gombok nevet egymas utan ';' jellel elvalasztva kell megadni.
                                                                //Ha nem adsz meg annyi nevet, ahany gombod van, akkor automatikusan a legutolso megadott nev fog a gombokon szerepelni
    for(int j=0;j<db;j++){
         button* jatek= new button(650,wy-600+j*55,cuttitles(titles));
         m->give_object(jatek);
    }
}


void run(menu* m,Jatek* not_chess)           //maga a teljes jatek
{

    string buttonnames="Új játék;Kilépés";
    generate_buttons(m,2,buttonnames);
    event ev;
    m->start_application();
    not_chess->indit();



    bool gamerun=0;
    while(ev.keycode!=key_escape)
    {
        gin>>ev;
        if(!gamerun)
        {
            if(m->run_(ev)==-1)              //-1 a "jatek"/folytatas gomb visszateresi erteke
            {
                gamerun=1;
                torol(wx,wy,0,0,0);                   //elindul a jatek
            }
            else if(not_chess->veresegvan==0){
                m->run_(ev);
            }
            if(not_chess->vereseg()==-1 && ev.keyname=="F1"){
                buttonnames="Új játék;Kilépés";
                generate_buttons(m,2,buttonnames);
                not_chess->indit();
            }

        }
        else
        {
            if(not_chess->futtatas(ev)==-1){
                gamerun=0;
            }
            torol(wx,wy,203 , 140, 111);
            not_chess->rajzolas();
            if(ev.keyname=="F1"){
                buttonnames="Folytatás;Kilépés"; //a futo jatekbol az esc billentyuvel lehet kilepni
                generate_buttons(m,2,buttonnames);
                gamerun=0;
                m->main_menu_logo->rajz(0,0);

            }
        }


        gout<<refresh;
    }

}



int main()
{
    menu* main_menu= new menu(wx,wy,"Kígyó károly");
    Jatek* not_chess=new Jatek(wx,wy);
    run(main_menu,not_chess);
    delete main_menu;
    delete not_chess;
    return 0;
}
