#include "menu.hpp"
#include <iostream>
#include <string>


void parent_app::give_object(object * b)
{
    objects.push_back(b);
}

setting* parent_app::get_settings(){
    return settings;
}


void parent_app::start_application(){}

int parent_app::run_(){return true;}




void menu::start_application()
{
    genv::gout.open(wsizex,wsizey,0);
    if(objects.size()==0)
    {
        textbox* error= new textbox(130,50,"Hiba az alkalmazás inditásakor",244,0,0);
        give_object(error);

        button* kilepes= new button(wsizex/2-40,120,0,0,"Kilépés");
        give_object(kilepes);

    }
     main_menu_logo->rajz(0,0);


}



int menu::run_(genv::event e){
    int btn_val=0;

    for(size_t i=0; i<objects.size();i++)
    {
        objects[i]->getinput(e);
        objects[i]->ofunction();

        btn_val=objects[i]->return_value();

        if(btn_val){

            if(i==0)
            {
            i=objects.size();
            objects.erase(objects.begin(),objects.end());
            return -1;
            }
            if(i==objects.size()-1){
                exit(0);
            }
            if(i==1 && objects.size()>2){

            }
        }

    }

    return true;
}
