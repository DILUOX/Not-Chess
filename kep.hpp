#ifndef KEP_HPP
#define KEP_HPP
#include <fstream>
#include <vector>
#include <iostream>
#include "graphics.hpp"
struct pixel{
    int x,y,r,g,b;
    pixel(int _x,int _y,std::ifstream &f){
        x=_x;y=_y;
        f>>r>>g>>b;
    }
};

class kep{
public:
    kep(std::string kepnev){
        std::ifstream f(kepnev);
        f>>szel>>mag;
        for(int y=0;y<mag;y++){
            for(int x=0;x<szel;x++){
                pixel p(x,y,f);
                keppontok.push_back(p);
            }
        }
        f.close();
    }
    ~kep(){
        keppontok.erase(keppontok.begin(),keppontok.end());
    }
    void rajz(int rajz_helye_x, int rajz_helye_y)const;
protected:
    int szel,mag;
    std::vector<pixel> keppontok;
};

#endif // KEP_HPP
