#include "Page_win.h"

Page_win::Page_win(bool f_w){
    ///Animation
    char buffer[70];
    for(int i=0;i<PG_WIN_ANI_SIZE;i++){
        Animation_obj *p=new Animation_obj;
        sprintf(buffer, "./image/Page_win/%s.png", PG_WIN_ANI_filename[i]);
        p->setting(PG_WIN_ANI_max_cur[i], PG_WIN_ANI_width[i], PG_WIN_ANI_height[i],
            PG_WIN_ANI_position_x[i], PG_WIN_ANI_position_y[i], buffer);
        ani_set.push_back(p);
    }
    font=al_load_font("./WORD.ttf",10,0);
    sample = al_load_sample("./music/sound_winner.wav");
    sound_winner = al_create_sample_instance(sample);
    first_win=f_w;
    walk1=false;
    walk2=false;
}
Page_win::~Page_win(){
    for(auto e:ani_set){delete e;}
    ani_set.clear();
}
void Page_win::run(){
    for(int i=0;i<PG_WIN_ANI_SIZE;i++) ani_set[i]->animate();
}
void Page_win::draw(){
    if(first_win) {
        al_draw_text(font,al_map_rgb(255,255,255),360,350,1,"PLAYER1 WIN!");
        if(!walk1) ani_set[2]->draw();
        else ani_set[3]->draw();
    }
    else {
        al_draw_text(font,al_map_rgb(255,255,255),360,350,1,"PLAYER2 WIN!");
        if(!walk2) ani_set[4]->draw();
        else ani_set[5]->draw();
    }
    for(int i=0;i<2;i++) ani_set[i]->draw();
    al_draw_text(font,al_map_rgb(255,255,255),360,380,1,"PRESS <ENTER> TO MENU");
}
bool Page_win::control(int command){
    if(command==4) return true;

    //llama1 walk
    else if(command==0){walk1=true;}
    else if(command==1){walk1=false;}
    //llama2 walk
    else if(command==2){walk2=true;}
    else if(command==3){walk2=false;}

    return false;
}
