#ifndef button_hpp
#define button_hpp
#include "graphics.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class object
{

public:
    int id;
    void centering(std::string text,int pozx,int pozy)const;
    void getinput(genv::event e);
    bool init();
    virtual ~object()
    {
        delete this;
    }

    virtual void draw()const;
    virtual void ofunction();
    virtual int return_value();
    virtual void setvalue(std::string val,int prev_x,int prev_y);
    virtual std::string return_title();

protected:
    int x,y,sx,sy,framesize;
    genv::event e;
    std::string title;
    int r,g,b;
    bool focus;

};

struct textbox : public object
{
protected:
    bool centered;
    int og_x,og_y;
public:
    textbox(int _x, int _y,std::string _title,int _r,int _g,int _b)
    {
        x=og_x=_x;
        sx=250;
        title=_title;
        y=_y;
        sy=40;
        r=_r;
        g=_g;
        b=_b;
        id=-2;
        centered=true;
    }
    textbox(int _x, int _y,std::string _title, int _r, int _g, int _b, bool centering)
    {

        x=og_x=_x;
        sx=250;
        id=1;
        title=_title;
        y=_y;
        sy=genv::gout.cascent()+30;
        r=_r;
        g=_g;
        b=_b;
        centered=centering;
    }
    textbox(int _r, int _g, int _b, int _x, int _y,int sx_, int sy_)
    {
        x=_x;
        y=_y;
        sx=sx_;
        sy=sy_;
        r=_r;
        g=_g;
        b=_b;
        title="notitle";
    }
    virtual void draw();
    void ofunction();
    int return_value();
    std::string return_title()
    {
        return title;
    }

};

class button : public object
{
public:
    button(int _x, int _y, int _sx,int _sy,std::string _title)
    {
        x=_x;
        sx=_sx;
        title=_title;
        y=_y;
        sy=_sy;
        r=244;
        g=200;
        b=200;
        value=0;
    }

    button(int _x, int _y,std::string _title)
    {
        x=_x;
        y=_y;
        title=_title;
        sx=100;
        sy=35;
        r=244;
        g=200;
        b=200;
        value=0;
    }

    ~button() {}

    bool isklicked();
    void draw()const;
    void ofunction();
    int return_value();

protected:
    bool value;
    int r,g,b;
};

class trianglebutton : public object
{
public:
    trianglebutton(int _x, int _y, int _sx, int _sy, bool upside)
    {
        x=_x;
        y=_y;
        sx=_sx;
        sy=_sy;
        upsided=upside;
        value=0;
    }
    void draw()const;
    void ofunction();
    int return_value();

protected:
    bool value,upsided;

};


class numeric_setter : public object
{
public:
    numeric_setter(int poz_x,int poz_y, int numlimit_low, int numlimit_high, int def_value,std::string title_)
    {
        x=poz_x;
        y=poz_y;
        sx=250;
        sy=200;
        framesize=4;
        r=g=b=255;

        numlow=numlimit_low;
        numhigh=numlimit_high;
        value=def_value;
        title=title_;
        focus=0;

        object * u = new trianglebutton(x+150+30,y+50,50,40,0);
        object * d = new trianglebutton(x+150+30,y+90,50,40,1);

        btns.push_back(u);
        btns.push_back(d);
    }
    void draw()const;
    void ofunction()override;
    int return_value();

private:
    bool focus;
    std::vector<object*> btns;
    int value,
        numlow,numhigh;

};

class stringlist : public object
{
public:
    stringlist(int _x, int _y, std::vector<std::string> _contents,int dpedelements,std::string _title)
    {
        x=_x;
        y=_y;
        sx=350;
        sy=170;
        r=g=b=255;
        framesize=4;
        object * display = new textbox(x+50,y+50,_contents[0],244,244,244,0);
        display->id=-1;
        contents.push_back(display);
        for(std::size_t i = 0; i< _contents.size(); i++)
        {
            object * t = new textbox(x+50,y+i*40 + 96,_contents[i],204,204,204,0);
            t->id=i+1;
            contents.push_back(t);
            listelements.push_back(_contents[i]);
            id=0;
            title=_title;
        }
        selectedelement=0;
        maxdisplayedcontents=dpedelements;
        listdown=0;
        mid_btn_pos=0;
        focus=0;
    }

    void draw()const;
    void ofunction()override;
    int return_value()override;
    std::string return_title()override;
private:
    int numberofcontents, selectedelement;
    size_t maxdisplayedcontents,mid_btn_pos;
    std::vector<object*> contents;
    std::vector<std::string> listelements;
    bool listdown;

};



class stringbox : public object
{
public:
    stringbox(int _x, int _y)
    {
        x=_x;
        y=_y;
        sx=400;
        sy=200;
        title="";
        r=g=b=255;
        selected=0;
        rows=cursorpozx=0;
        cursorpozy=genv::gout.cascent();
        cursorcharacter=0;
    }
    void draw()const override;
    void ofunction();
    void titlecorrection();
    int return_value();
private:
    bool selected;
    int rows;
    int cursorpozx,cursorpozy,cursorcharacter;

};




void torol(const int x, const int y,const int r, const int g, const int b);
void triangle(bool upsidedown,int x, int y, int a);

#endif // button_hpp
