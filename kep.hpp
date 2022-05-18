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
     kep(std::string kepnev,int x_, int y_){
        std::ifstream f(kepnev);
        f>>szel>>mag;
        std::cout<<szel<<" x "<<mag<<std::endl;
        for(int y=0;y<mag;y++){
            for(int x=0;x<szel;x++){
                pixel p(x+x_,y+y_,f);
                keppontok.push_back(p);
            }
        }
        f.close();
    }
    ~kep(){
        keppontok.erase(keppontok.begin(),keppontok.end());
    }
    void rajz(int rajz_helye_x, int rajz_helye_y)const;
    int szel,mag;
    std::vector<pixel> keppontok;
protected:

};

#endif // KEP_HPP
