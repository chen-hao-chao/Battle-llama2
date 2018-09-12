#include "Page_menu.h"

Page_menu::Page_menu(){
    ani_set.clear();
    ///Animation
    char buffer[70];
    for(int i=0;i<PG_MENU_ANI_SIZE;i++){
        Animation_obj *p=new Animation_obj;
        sprintf(buffer, "./image/Page_menu/%s.png", PG_MENU_ANI_filename[i]);
        p->setting(PG_MENU_ANI_max_cur[i], PG_MENU_ANI_width[i], PG_MENU_ANI_height[i],
            PG_MENU_ANI_position_x[i], PG_MENU_ANI_position_y[i], buffer);
        ani_set.push_back(p);
    }
    ///Button
    button = new Button;
    button->setting(PG_MENU_BUTTON_MAXCUR,PG_MENU_BUTTON_NUMBER,PG_MENU_BUTTON_WIDTH,PG_MENU_BUTTON_HEIGHT,
        PG_MENU_BUTTON_X,PG_MENU_BUTTON_Y, PG_MENU_BUTTON_dX, PG_MENU_BUTTON_dY,PG_MENU_BUTTON_DISPLACEMENT,PG_MENU_BUTTON_FILENAME1,PG_MENU_BUTTON_FILENAME2,10.0);

    into=false;
    walk1=false;
    attack1=false;
    walk2=false;
    attack2=false;
    quit=false;

    control_selector=0;
    font=al_load_font(PG_MENU_BUTTON_FILENAME2,9,0);
}
Page_menu::~Page_menu(){
    for(auto e:ani_set){delete e;}
    ani_set.clear();
    delete button;
    al_destroy_font(font);
}
bool Page_menu::control(int command){
    if(command==0){if(!into)control_selector=button->control(command);}//UP
    else if(command==1){if(!into)control_selector=button->control(command);}//DOWN
    else if(command==2){//ENTER
        into=!into;
        if(control_selector==0){return true;}
        if(control_selector==3){quit=true;return true;}
    }

    //control of left llama
    else if(command==4){if(control_selector==1&&into){walk1=true;}}
    else if(command==5){if(control_selector==1&&into){attack1=true;}}
    else if(command==6){if(control_selector==1&&into){walk1=false;}}
    else if(command==7){if(control_selector==1&&into){attack1=false;}}
    //control of right llama
    else if(command==8){if(control_selector==1&&into){walk2=true;}}
    else if(command==9){if(control_selector==1&&into){attack2=true;}}
    else if(command==10){if(control_selector==1&&into){walk2=false;}}
    else if(command==11){if(control_selector==1&&into){attack2=false;}}

    return false;
}
void Page_menu::run(){
    if(control_selector==1&&into){
        for(int i=3;i<9;i++) ani_set[i]->animate();
    }
    else if(control_selector==2&&into){
        ani_set[9]->animate();
    }
    else{
        for(int i=0;i<3;i++) ani_set[i]->animate();
        button->run();
    }
}
void Page_menu::draw(){
    if(control_selector==1&&into){
        for(int i=0;i<12;i++) al_draw_text(font,al_map_rgb(255,255,255),PG_MENU_FONT_position_x[i],PG_MENU_FONT_position_y[i],ALLEGRO_ALIGN_CENTRE,PG_MENU_FONT_contain[i]);
        if(!walk1) ani_set[3]->draw();
        else ani_set[4]->draw();
        if(attack1) ani_set[5]->draw();

        if(!walk2) ani_set[6]->draw();
        else ani_set[7]->draw();
        if(attack2) ani_set[8]->draw();

        al_draw_rounded_rectangle(330,310,390,330,7,7,al_map_rgb(100,255,255),1.5);
        al_draw_rounded_rectangle(330,375,390,395,7,7,al_map_rgb(100,255,255),1.5);
    }
    else if(control_selector==2&&into){
        ani_set[9]->draw();
        al_draw_text(font,al_map_rgb(255,255,255),360,300,1,"/LANCE HAOHAO HAS THE RIGHT TO REVISE/");
    }
    else{
        for(int i=0;i<3;i++) ani_set[i]->draw();
        for(int i=0;i<PG_MENU_BUTTON_NUMBER;i++) button->draw_text(PG_MENU_BTN_name[i],i);
        button->draw();
    }
}
ALLEGRO_SAMPLE_INSTANCE *Page_menu::get_sample_instance(int command){
    //shift->0
    //enter->1
    return button->get_sample_instance(command);
}
