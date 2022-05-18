#include "objects.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include "menu.hpp"
using namespace genv;
using namespace std;

const int wx=1400;
const int wy=720;

///Objektum foosztaly

void object::ofunction()
{
    draw();
}
void object::draw()const {};

int object::return_value()
{
    return 0;
};

void object::getinput(genv::event ev)
{
    e=ev;

}

void object::centering(std::string text,int pozx,int pozy)const
{
    genv::gout<<genv::move_to(x+sx/2-genv::gout.twidth(text)/2,pozy);        //kozepre igazitja a rajzpontot szovegirashoz
}

void  torol(const int x, const int y,int r,const int g,const int b)
{
    genv::gout<<genv::move_to(0,0)<<genv::color(r,g,b)<<genv::box(x,y);    //kepernyotorles; mozgatashoz ajanlott
}

bool object::init()
{
    return e.pos_x>x && e.pos_x<x+sx && e.pos_y>y && e.pos_y<y+sy;
}


void object::setvalue(string v,int prev_x, int prev_y)
{
    title=v;
}


string object::return_title()
{
    return title;
}


///sima gomb

void button::draw()const
{
    genv::gout<<genv::move_to(x,y)<<genv::color(r,g,b)<<genv::box(sx,sy);    //gombrajzolas
    centering(title,x,y+sy/2);
    genv::gout<<genv::color(0,0,0)<<genv::text(title);       //szoveg
}


void button::ofunction()
{
    if(init() && value==0)
    {
        value=1;
        r=160;
        g=204;
        b=100;

    }
    else if(value==1 && !init())
    {
        r=244;
        g=200;
        b=200;
        value=0;
    }

    draw();
}

int button::return_value()
{

    return init() && e.button==genv::btn_left;

}

/// haromszog jelzesu allito gomb(lefele/folfele)

void triangle(bool upsidedown,int x, int y, int a)
{
    if(upsidedown)
    {
        gout<<move_to(x,y)<<color(255,0,0)<<line_to(x+a,y)<<line_to(x+a/2,y+a)<<line_to(x,y);
    }
    else
    {
        gout<<move_to(x,y)<<color(255,0,0)<<line_to(x+a/2,y-a)<<line_to(x+a,y)<<line_to(x,y);
    }
}

void trianglebutton::draw()const
{
    gout<<move_to(x,y)<<color(0,0,0)<<box(sx,sy)<<move_to(x+2,y+2)<<color(r,g,b)<<box(sx-4,sy-4);
    if(upsided)
    {
        triangle(upsided,x+12,y+8,26);
    }
    else
    {
        triangle(upsided,x+12,y+32,26);
    }
}

void trianglebutton::ofunction()
{
    if(init())
    {
        r=255;
        g=204;
        b=0;
        if(e.button==btn_left)
        {
            value=1;
        }
    }
    else
    {
        r=g=b=255;
    }
    if(value && e.button==-btn_left)
    {
        value=0;
    }

};

int trianglebutton::return_value()
{

    return value;
}


///szambeallito widget


void numeric_setter::draw()const
{

    //Maga a adoboz
    gout<<move_to(x,y)<<color(255,0,0)<<box(sx,sy)<<move_to(x+framesize,y+framesize)<<color(r,g,b)<<box(sx-framesize*2,sy-framesize*2) // ablak, kerettel

        <<move_to(x+30,y+50)<<color(0,0,0)<<box(190,80)<<color(255,255,255)<<move_to(x+32,y+52)<<box(186,76)<<color(0,0,0);     //szovegdoboz

    centering(title,x,y+20);                    //doboz cime
    gout<<text(title);


    //Beallito gombok kirajz, ertek kiiratas
    for(size_t i = 0; i<btns.size(); i++)
    {
        btns[i]->draw();
    }
    gout<<move_to(x+33,y+75)<<text(std::to_string(value));



}


void numeric_setter::ofunction()
{
    draw();
    if(init() && e.button==+btn_left)
    {
        focus=true;
        r=51;
        g=153;
    }
    if(!init() && e.button== btn_left)
    {
        focus=false;
        r=g=b=255;
    }
    if(focus)
    {
        if(e.keycode==75 && value+10<=numhigh)
        {
            value+=10;
        }
        if(e.keycode==78&& value-10>=numlow)
        {
            value-=10;
        }
        if(e.keycode==82 && value<numhigh)
        {
            value++;
        }
        if(e.keycode==81 && value>numlow)
        {
            value--;
        }
    }

    for(size_t i=0; i<btns.size(); i++)
    {
        btns[i]->getinput(e);
        btns[i]->ofunction();
        if(btns[i]->return_value() && value<numhigh && i==0)
        {
            value++;
        }
        if(btns[i]->return_value() && value>numlow && i==1)
        {
            value--;
        }
    }





}

int numeric_setter::return_value()
{
    return value;
}


///legordulo lista


void stringlist::draw()const
{
    gout<<move_to(x,y)<<color(255,0,0)<<box(sx,sy)<<move_to(x+framesize,y+framesize)<<color(r,g,b)<<box(sx-framesize*2,sy-framesize*2);
    gout<<move_to(x+46,y+46)<<color(0,0,0)<<box(258,50);
    contents[0]->ofunction();
    triangle(1,x+275,y+60,20);
    gout<<move_to(x+sx/2-gout.twidth(title)/2,y+20)<<color(0,0,0)<<text(title);
}

void stringlist::ofunction()
{

    bool backlist=0;
    draw();
    if(listdown && e.button==btn_left && contents[0]->init())
    {
        listdown=0;
        backlist=1;
    }
    for(size_t i=0; i<maxdisplayedcontents; i++)
    {
        contents[i]->getinput(e);
        if((e.pos_x<=x+50 || e.pos_x>=x+sx-50) && (e.pos_y<y+50 || e.pos_y>y+maxdisplayedcontents*40) && e.button==btn_left && listdown==1)
        {
            listdown=0;
            backlist=1;
        }

        if(contents[i]->return_value() && listdown==1 && i!=0)
        {
            listdown=0;
            backlist=1;
            selectedelement=i;
            contents[0]->setvalue(contents[selectedelement]->return_title(),0,0);
        }

    }
    if(contents[0]->return_value() && e.button==+btn_left && !backlist)
    {
        listdown=1;
    }
    if(listdown)
    {
        if(e.button==+btn_wheeldown)
        {
            if(mid_btn_pos<contents.size()-1)
            {
                mid_btn_pos++;
            }

        }
        if(e.button==+btn_wheelup && mid_btn_pos>0)
        {
            mid_btn_pos--;

        }
        for(size_t i= 0; i<maxdisplayedcontents; i++)
        {
            contents[i]->ofunction();


            if(mid_btn_pos>=maxdisplayedcontents)
            {
                if(i!=0)
                {
                    contents[i]->setvalue(listelements[mid_btn_pos-maxdisplayedcontents+i],0,0);
                }


            }
            if(mid_btn_pos==0 && i<listelements.size())
            {
                contents[i+1]->setvalue(listelements[i],0,0);
            }

        }
    }

}

int stringlist::return_value()
{
    return 0;
}



/// szovegdoboz

void stringbox::draw()const
{
    gout<<move_to(x,y)<<color(255,0,0)<<box(sx,sy)<<move_to(x+4,y+4)<<color(r,g,b)<<box(sx-8,sy-8)<<
        move_to(x+50,y+50)<<color(0,0,0)<<box(sx-100,sy-120)<<move_to(x+52,y+52)<<color(r,g,b)<<box(sx-104,sy-124);
    if(selected)
    {
        gout<<move_to(x+55+cursorpozx,y+50+cursorpozy)<<color(0,0,0)<<line(0,gout.cascent()+10);
    }
    if(rows<1)
    {
        gout<<move_to(x+55,y+50+gout.cascent())<<text(title);
    }
    else
    {
        string vege = title.substr(rows*29,title.length()-rows*29);
        for(int i=0; i<rows; i++)
        {
            gout<<move_to(x+55,y+50+gout.cascent()*(i+1))<<text(title.substr(i*29,i+1*29-i));
        }
        gout<<move_to(x+55,y+50+gout.cascent()*(rows+1))<<text(title.substr(rows*29,vege.length()));
    }

}

void stringbox::ofunction()
{
    /*
    bool init=(e.pos_x>x+50 && e.pos_x<x+50+sx-100 && e.pos_y>y+50 && e.pos_y<y+50+sy-120 && e.button==btn_left);
    string vege = title.substr(rows*29,title.length()-rows*29);
    if(init)
    {
        selected=1;
        cout<<title<<endl;
    }
    if(!init && e.button==btn_left)
    {
        selected=0;
    }
    if(e.type==ev_key && selected && e.keycode>0 && e.keycode !=8 && e.keyname!="Left"
       && e.keyname!="Right" && e.keyname!="Delete")
    {
        if(title.length()!=0 && title.length()%29==0 && selected && rows<2)
        {
            rows+=1;
            cursorpozy+=gout.cascent();
        }
        if(rows<2)
        {
            title+=e.keycode;
            cursorcharacter++;
        }
        cursorpozx=vege.length()*10+10;

    }
    if(e.keycode==8 && title.length()>0)
    {
        if(rows>0 && vege.length()==0)
        {
            rows--;
            cursorpozx=29;
            cursorcharacter--;
        }
        else
        {                       ///12345
            cursorcharacter--;
            //title=title.substr(0,cursorcharacter-1)+title.substr(cursorcharacter,title.length()-cursorcharacter);
        }
    }

    cout<<e.keyname<<endl;
    cout<<e.keycode<<endl;
    if(e.keycode==+79)   //right
    {
        cursorpozx+=10;
        cursorcharacter++;
    }
    if(e.keycode==+80 && cursorpozx>0)          //left
    {
        cursorpozx-=10;
        cursorcharacter--;
    }
    if((e.keycode=+65541) && (cursorcharacter<vege.length()))
    {
      //  title=title.substr(0,cursorcharacter);
        cursorcharacter--;
    }
    if(cursorpozx==0 && rows>0 && cursorpozy>11 && e.keycode==+80)
    {
        cursorpozy-=gout.cascent();
        cursorpozx=29*10;
    }
    draw();
    */
}
void stringbox::titlecorrection()
{
}
int stringbox::return_value()
{
    return 0;
}


string stringlist::return_title()
{
    return contents[0]->return_title();
}






///sima szovegdoboz(csak tartalomkiiratasra)
void textbox::draw()
{
    genv::gout<<genv::move_to(x,y)<<genv::color(r,g,b)<<genv::box(sx,sy);
    if(centered)
    {
        centering(title,x,y+sy/2-gout.cascent()/2);
    }
    else
    {
        genv::gout<<genv::move_to(x+10,y+sy/2-gout.cascent()/2);
    }
    if(title!="notitle")
    {
        genv::gout<<genv::color(0,0,0)<<genv::text(title);
    }

}


void textbox::ofunction()
{
    if(init() && e.button==+btn_left)
    {
        focus=1;
    }
    if(id==-2 && e.keyname=="Return")
    {
        focus=1;
    }
    if(focus || (init() && id!=-2))
    {
        r=255;
        g=204;
        b=0;
    }
    else
    {
        r=g=b=204;
    }
    if(id!=0)
    {
        focus=0;
        draw();
    }


}

int textbox::return_value()
{
    if(init() && e.button==+btn_left)
    {
        return 1;
    }
    return 0;
}


