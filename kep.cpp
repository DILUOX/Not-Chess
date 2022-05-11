#include "kep.hpp"
#include <iostream>

using namespace genv;
void kep::rajz(int rajz_helye_x, int rajz_helye_y)const{
    for(size_t i=0; i<keppontok.size(); i++)
        {
            gout<<move_to(rajz_helye_x+keppontok[i].x,rajz_helye_y+keppontok[i].y)
                <<color(keppontok[i].r,keppontok[i].g,keppontok[i].b)<<dot;
        }
}
