#include "Page_play.h"

Page_play::Page_play(int s1, int s2){
    ///Animation
    char buffer[70];
    for(int i=0;i<PG_PLAY_ANI_SIZE;i++){
        Animation_obj *p=new Animation_obj;
        sprintf(buffer, "./image/Page_play/%s.png", PG_PLAY_ANI_filename[i]);
        p->setting(PG_PLAY_ANI_max_cur[i], PG_PLAY_ANI_width[i], PG_PLAY_ANI_height[i],
            PG_PLAY_ANI_position_x[i], PG_PLAY_ANI_position_y[i], buffer);
        ani_set.push_back(p);
    }
    ///Llamas
    if(s1==0){PQllama1=new Party_queen(LLAMA1_POSITION_X,LLAMA1_POSITION_Y,1);blood1=PQBLOOD;}
    else if(s1==1){HMllama1=new Hamburbaby(LLAMA1_POSITION_X,LLAMA1_POSITION_Y,1);blood1=HMBLOOD;}
    else if(s1==2){WLllama1=new Weed_llama(LLAMA1_POSITION_X,LLAMA1_POSITION_Y,1);blood1=WLBLOOD;}
    if(s2==0){PQllama2=new Party_queen(LLAMA2_POSITION_X,LLAMA2_POSITION_Y,0);blood2=PQBLOOD;}
    else if(s2==1){HMllama2=new Hamburbaby(LLAMA2_POSITION_X,LLAMA2_POSITION_Y,0);blood2=HMBLOOD;}
    else if(s2==2){WLllama2=new Weed_llama(LLAMA2_POSITION_X,LLAMA2_POSITION_Y,0);blood2=WLBLOOD;}

    sel1=s1;
    sel2=s2;
    state1=0;
    state2=0;
    add_check1=false;
    add_check2=false;
    counter=0;
    background=al_load_bitmap("./image/Page_play/background.png");
    add=al_load_bitmap("./image/Page_play/add.png");
    level_one=al_load_bitmap("./image/Page_play/level_one.png");
    level_two=al_load_bitmap("./image/Page_play/level_two.png");
    add_b=al_load_bitmap("./image/Page_play/add_b.png");
    level_one_b=al_load_bitmap("./image/Page_play/level_one_b.png");
    level_two_b=al_load_bitmap("./image/Page_play/level_two_b.png");
    font=al_load_font("./WORD.ttf",20,0);
}
Page_play::~Page_play(){
    for(auto e:ani_set){delete e;}
    ani_set.clear();
    delete PQllama1;
    delete PQllama2;
    delete HMllama1;
    delete HMllama2;
    delete WLllama1;
    delete WLllama2;
    al_destroy_font(font);
    al_destroy_bitmap(background);
    al_destroy_bitmap(add);
}
bool Page_play::run(){
    if(counter<90){
        counter++;
    }
    else{
        float *new_x1, *new_y1;
        float *new_x2, *new_y2;

        if(sel1==0){new_x1=&(PQllama1->x);new_y1=&(PQllama1->y);}
        else if(sel1==1){new_x1=&(HMllama1->x);new_y1=&(HMllama1->y);}
        else if(sel1==2){new_x1=&(WLllama1->x);new_y1=&(WLllama1->y);}
        if(sel2==0){new_x2=&(PQllama2->x);new_y2=&(PQllama2->y);}
        else if(sel2==1){new_x2=&(HMllama2->x);new_y2=&(HMllama2->y);}
        else if(sel2==2){new_x2=&(WLllama2->x);new_y2=&(WLllama2->y);}

        if(sel1==0){
            PQllama1->run();
            PQllama1->renew_blood(*new_x2,*new_y2,blood2);
            state1=PQllama1->renew_state(blood1);
        }
        else if(sel1==1){
            HMllama1->run();
            HMllama1->renew_blood(*new_x2,*new_y2,blood2,blood1);
            state1=HMllama1->renew_state(blood1);
        }
        else if(sel1==2){
            WLllama1->run();
            WLllama1->renew_blood(*new_x2,*new_y2,blood2);
            state1=WLllama1->renew_state(blood1);
        }
        if(sel2==0){
            PQllama2->run();
            PQllama2->renew_blood(*new_x1,*new_y1,blood1);
            state2=PQllama2->renew_state(blood2);
        }
        else if(sel2==1){
            HMllama2->run();
            HMllama2->renew_blood(*new_x1,*new_y1,blood1,blood2);
            state2=HMllama2->renew_state(blood2);
        }
        else if(sel2==2){
            WLllama2->run();
            WLllama2->renew_blood(*new_x1,*new_y1,blood1);
            state2=WLllama2->renew_state(blood2);
        }

        map_scope(new_x1,new_y1,new_x2,new_y2);
        for(int i=0;i<PG_PLAY_ANI_SIZE;i++) ani_set[i]->animate();
    }
    if(blood1<=0||blood2<=0) return true;
    else return false;
}
void Page_play::draw(){
    al_draw_bitmap(background,0,0,0);
    if(add_check1) {al_draw_bitmap(add,100,40,0);}
    else {al_draw_bitmap(add_b,100,40,0);}
    if(add_check2) {al_draw_bitmap(add,613,40,0);}
    else {al_draw_bitmap(add_b,613,40,0);}

    if(state1==1||state1==2) {al_draw_bitmap(level_one,78,40,0);}
    else {al_draw_bitmap(level_one_b,78,40,0);}
    if(state1==2) {al_draw_bitmap(level_two,50,40,0);}
    else {al_draw_bitmap(level_two_b,50,40,0);}
    if(state2==1||state2==2) {al_draw_bitmap(level_one,640,40,0);}
    else {al_draw_bitmap(level_one_b,640,40,0);}
    if(state2==2) {al_draw_bitmap(level_two,660,40,0);}
    else {al_draw_bitmap(level_two_b,660,40,0);}

    if(sel1==0){PQllama1->draw();}
    else if(sel1==1){HMllama1->draw();}
    else if(sel1==2){WLllama1->draw();}
    if(sel2==0){PQllama2->draw();}
    else if(sel2==1){HMllama2->draw();}
    else if(sel2==2){WLllama2->draw();}
    al_draw_filled_rounded_rectangle(50,20,50+blood1,28,4,4,al_map_rgb(180,100,255));
    al_draw_filled_rounded_rectangle(450,20,450+blood2,28,4,4,al_map_rgb(255,100,180));
    for(int i=0;i<PG_PLAY_ANI_SIZE;i++) ani_set[i]->draw();

    //counter
    if(counter<30){
        al_draw_text(font,al_map_rgb(255,255,255),360,220,1,"3");
    }
    else if(counter>=30&&counter<60){
        al_draw_text(font,al_map_rgb(255,255,255),360,220,1,"2");
    }
    else if(counter<90){
        al_draw_text(font,al_map_rgb(255,255,255),360,220,1,"1");
    }
}
void Page_play::control(int command, bool first){
    /*
    Command
    #define UP 0
    #define DOWN 1
    #define ENTER 2
    #define CHECK 3
    #define LEFT 4
    #define RIGHT 5
    #define ATTACK 6
    #define ATTACK_UNPRESS 7
    #define UP_UNPRESS 8
    #define DOWN_UNPRESS 9
    #define LEFT_UNPRESS 10
    #define RIGHT_UNPRESS 11
    #define ATTACK_MAX 12
    */
    if(first){
        if(sel1==0) PQllama1->control(command);
        else if(sel1==1) HMllama1->control(command);
        else if(sel1==2) WLllama1->control(command);
    }
    else{
        if(sel2==0) PQllama2->control(command);
        else if(sel2==1) HMllama2->control(command);
        else if(sel2==2) WLllama2->control(command);
    }
}
void Page_play::map_scope(float* x1, float* y1, float* x2, float* y2){
    if(*x1>MAP_DOWNLIMIT_X) *x1=MAP_DOWNLIMIT_X;
    else if(*x1<MAP_UPLIMIT_X) *x1=MAP_UPLIMIT_X;
    if(*y1>MAP_DOWNLIMIT_Y) *y1=MAP_DOWNLIMIT_Y;
    else if(*y1<MAP_UPLIMIT_Y) *y1=MAP_UPLIMIT_Y;
    if(*x1<MAP_AB_DOWNLIMIT_X&&*x1>MAP_AB_UPLIMIT_X&&*y1<MAP_AB_DOWNLIMIT_Y&&*y1>MAP_AB_UPLIMIT_Y){
        if(blood1<BLOOD_LIMIT)blood1+=MAP_ADD_BLOOD;
        add_check1=true;
    }
    else add_check1=false;

    if(*x2>MAP_DOWNLIMIT_X) *x2=MAP_DOWNLIMIT_X;
    else if(*x2<MAP_UPLIMIT_X) *x2=MAP_UPLIMIT_X;
    if(*y2>MAP_DOWNLIMIT_Y) *y2=MAP_DOWNLIMIT_Y;
    else if(*y2<MAP_UPLIMIT_Y) *y2=MAP_UPLIMIT_Y;
    if(*x2<MAP_AB_DOWNLIMIT_X&&*x2>MAP_AB_UPLIMIT_X&&*y2<MAP_AB_DOWNLIMIT_Y&&*y2>MAP_AB_UPLIMIT_Y){
        if(blood2<BLOOD_LIMIT)blood2+=MAP_ADD_BLOOD;
        add_check2=true;
    }
    else add_check2=false;
}
ALLEGRO_SAMPLE_INSTANCE *Page_play::get_sample_instance(int command, bool first){
    //0->move
    //1->laser
    //2->maxlaser
    //3->explode
    //if(counter==90){
    if(first){
        if(sel1==0){
            if(command==0) return PQllama1->get_sample_instance(0);
            else if(command==1) return PQllama1->get_sample_instance(1);
            else if(command==2) return PQllama1->get_sample_instance(2);
            else if(command==3) return PQllama1->get_sample_instance(3);
        }
        else if(sel1==1){
            if(command==0) return HMllama1->get_sample_instance(0);
            else if(command==1) return HMllama1->get_sample_instance(1);
            else if(command==2) return HMllama1->get_sample_instance(2);
            else if(command==3) return HMllama1->get_sample_instance(3);
        }
        else if(sel1==2){
            if(command==0) return WLllama1->get_sample_instance(0);
            else if(command==1) return WLllama1->get_sample_instance(1);
            else if(command==2) return WLllama1->get_sample_instance(2);
            else if(command==3) return WLllama1->get_sample_instance(3);
        }
    }
    else{
        if(sel2==0){
            if(command==0) return PQllama2->get_sample_instance(0);
            else if(command==1) return PQllama2->get_sample_instance(1);
            else if(command==2) return PQllama2->get_sample_instance(2);
            else if(command==3) return PQllama2->get_sample_instance(3);
        }
        else if(sel2==1){
            if(command==0) return HMllama2->get_sample_instance(0);
            else if(command==1) return HMllama2->get_sample_instance(1);
            else if(command==2) return HMllama2->get_sample_instance(2);
            else if(command==3) return HMllama2->get_sample_instance(3);
        }
        else if(sel2==2){
            if(command==0) return WLllama2->get_sample_instance(0);
            else if(command==1) return WLllama2->get_sample_instance(1);
            else if(command==2) return WLllama2->get_sample_instance(2);
            else if(command==3) return WLllama2->get_sample_instance(3);
        }
    }
}
bool Page_play::get_movement(bool sel, bool first){
    if(first){
        if(sel1==0){return PQllama1->get_movement(sel);}
        else if(sel1==1){return HMllama1->get_movement(sel);}
        else if(sel1==2){return WLllama1->get_movement(sel);}
    }
    else{
        if(sel2==0){return PQllama2->get_movement(sel);}
        else if(sel2==1){return HMllama2->get_movement(sel);}
        else if(sel2==2){return WLllama2->get_movement(sel);}
    }
}
