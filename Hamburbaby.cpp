#include "Hamburbaby.h"

Hamburbaby::Hamburbaby(int _x, int _y, bool p1){
    rest_map_left=al_load_bitmap("./image/Page_play/rest_map_left.png");
    rest_map_right=al_load_bitmap("./image/Page_play/rest_map_right.png");
    walk_map_left=al_load_bitmap("./image/Page_play/walk_map_left.png");
    walk_map_right=al_load_bitmap("./image/Page_play/walk_map_right.png");
    laser_map_left=al_load_bitmap("./image/Page_play/laser_map_left.png");
    laser_map_right=al_load_bitmap("./image/Page_play/laser_map_right.png");

    hm_rest_map_left=al_load_bitmap("./image/Page_play/hm_rest_map_left.png");
    hm_rest_map_right=al_load_bitmap("./image/Page_play/hm_rest_map_right.png");
    hm_walk_map_left=al_load_bitmap("./image/Page_play/hm_walk_map_left.png");
    hm_walk_map_right=al_load_bitmap("./image/Page_play/hm_walk_map_right.png");
    hm_laser_map_left=al_load_bitmap("./image/Page_play/hm_laser_map_left.png");
    hm_laser_map_right=al_load_bitmap("./image/Page_play/hm_laser_map_right.png");
    hm_maxattack_map=al_load_bitmap("./image/Page_play/hm_maxattack_map.png");
    hm_explode_map=al_load_bitmap("./image/Page_play/hm_explode_map.png");

    sample = al_load_sample("./music/sound_move.wav");
    sound_move = al_create_sample_instance(sample);
    sample = al_load_sample("./music/sound_laser.wav");
    sound_laser = al_create_sample_instance(sample);
    sample = al_load_sample("./music/sound_maxlaser.wav");
    sound_maxlaser = al_create_sample_instance(sample);
    sample = al_load_sample("./music/sound_explode.wav");
    sound_explode = al_create_sample_instance(sample);

    x=_x;
    y=_y;
    cur=0;
    cur_att=0;
    cur_maxattack=0;
    state=0;
    rest=true;
    attack=false;
    max_attack=false;
    attacking=HMATTACKING;
    right=p1;
    for(int i=0;i<4;i++) movement[i]=false;
}
Hamburbaby::~Hamburbaby(){
    al_destroy_bitmap(rest_map_left);
    al_destroy_bitmap(rest_map_right);
    al_destroy_bitmap(walk_map_left);
    al_destroy_bitmap(walk_map_right);
    al_destroy_bitmap(laser_map_left);
    al_destroy_bitmap(laser_map_right);
    al_destroy_bitmap(hm_rest_map_left);
    al_destroy_bitmap(hm_rest_map_right);
    al_destroy_bitmap(hm_walk_map_left);
    al_destroy_bitmap(hm_walk_map_right);
    al_destroy_bitmap(hm_laser_map_left);
    al_destroy_bitmap(hm_laser_map_right);
    al_destroy_bitmap(hm_maxattack_map);
    al_destroy_bitmap(hm_explode_map);
}
void Hamburbaby::run(){
    ///Animation
    cur++;
    if(cur==5) cur=0;

    if(max_attack){
        ///Max_attack
        cur_maxattack++;
        if(cur_maxattack==8){max_attack=false;cur_maxattack=0;}
    }
    else{
        ///Movement
        if(!movement[0]&&!movement[1]&&!movement[2]&&!movement[3]) rest=true;
        else rest=false;

        if(movement[0]) y-=HMSPEED;
        else if(movement[1]) y+=HMSPEED;
        if(movement[2]) x-=HMSPEED;
        else if(movement[3]) x+=HMSPEED;

        ///Attack
        if(attack){
            if(state==0){
                cur_att++;
                if(cur_att==9) cur_att=0;
            }
            else{
                cur_att++;
                if(cur_att==4) cur_att=0;
            }
        }
        else{
            cur_att=0;
        }
    }
}
void Hamburbaby::draw(){
    if(right){
        if(rest){
            if(state==0) al_draw_bitmap_region(rest_map_right,cur*HMWIDTH,0,HMWIDTH,HMHEIGHT,x,y,0);
            else al_draw_bitmap_region(hm_rest_map_right,cur*HMWIDTH,0,HMWIDTH,HMHEIGHT,x,y,0);
        }
        else{
            if(state==0) al_draw_bitmap_region(walk_map_right,cur*HMWIDTH,0,HMWIDTH,HMHEIGHT,x,y,0);
            else al_draw_bitmap_region(hm_walk_map_right,cur*HMWIDTH,0,HMWIDTH,HMHEIGHT,x,y,0);
        }
        if(attack&&!max_attack){
            if(state==0) al_draw_bitmap_region(laser_map_right,cur_att*HMWIDTH_LASER,0,HMWIDTH_LASER,HMHEIGHT_LASER,x+63,y-2,0);
            else al_draw_bitmap_region(hm_laser_map_right,cur_att*HMWIDTH_LASER_MAX,0,HMWIDTH_LASER_MAX,HMHEIGHT_LASER_MAX,x+73,y-15,0);
        }
    }
    else{
        if(rest){
            if(state==0) al_draw_bitmap_region(rest_map_left,cur*HMWIDTH,0,HMWIDTH,HMHEIGHT,x,y,0);
            else al_draw_bitmap_region(hm_rest_map_left,cur*HMWIDTH,0,HMWIDTH,HMHEIGHT,x,y,0);
        }
        else{
            if(state==0) al_draw_bitmap_region(walk_map_left,cur*HMWIDTH,0,HMWIDTH,HMHEIGHT,x,y,0);
            else al_draw_bitmap_region(hm_walk_map_left,cur*HMWIDTH,0,HMWIDTH,HMHEIGHT,x,y,0);
        }
        if(attack&&!max_attack){
            if(state==0)al_draw_bitmap_region(laser_map_left,cur_att*HMWIDTH_LASER,0,HMWIDTH_LASER,HMHEIGHT_LASER,x-130,y-2,0);
            else al_draw_bitmap_region(hm_laser_map_left,cur_att*HMWIDTH_LASER_MAX,0,HMWIDTH_LASER_MAX,HMHEIGHT_LASER_MAX,x-400,y-15,0);
        }
    }
    if(max_attack){
        for(int i=0;i<280;i+=70){
            al_draw_bitmap_region(hm_explode_map,cur_maxattack*HMWIDTH_EXPLODE,0,HMWIDTH_EXPLODE,HMHEIGHT_EXPLODE,x-100+i,y-70,0);
            al_draw_bitmap_region(hm_explode_map,cur_maxattack*HMWIDTH_EXPLODE,0,HMWIDTH_EXPLODE,HMHEIGHT_EXPLODE,x-100+i,y+70,0);
        }
        al_draw_bitmap_region(hm_explode_map,cur_maxattack*HMWIDTH_EXPLODE,0,HMWIDTH_EXPLODE,HMHEIGHT_EXPLODE,x-100,y,0);
        al_draw_bitmap_region(hm_explode_map,cur_maxattack*HMWIDTH_EXPLODE,0,HMWIDTH_EXPLODE,HMHEIGHT_EXPLODE,x+110,y,0);
        al_draw_bitmap_region(hm_maxattack_map,cur_maxattack*HMWIDTH_MAXATTACK,0,HMWIDTH_MAXATTACK,HMHEIGHT_MAXATTACK,x-50,y-50,0);
    }
}
void Hamburbaby::control(int command){
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
    switch(command){
        case 0:
        movement[0]=true;
        break;
        case 1:
        movement[1]=true;
        break;
        case 4:
        movement[2]=true;right=false;
        break;
        case 5:
        movement[3]=true;right=true;
        break;
        case 6:
        attack=true;
        break;
        case 7:
        attack=false;
        break;
        case 8:
        movement[0]=false;
        break;
        case 9:
        movement[1]=false;
        break;
        case 10:
        movement[2]=false;
        break;
        case 11:
        movement[3]=false;
        break;
        case 12:
        if(state==2&&!max_attack){max_attack=true;}
        break;
    }
}
void Hamburbaby::renew_blood(float& _x, float& _y, float& _blood, float& self_blood){
    if(attack&&!max_attack){
        if(state==0){
            if(right){if(_x<x+160&&_x>x&&_y>y-30&&_y<y+40){_blood-=attacking;}}
            else{if(_x>x-160&&_x<x&&_y>y-30&&_y<y+40){_blood-=attacking;}}
        }
        else{
            if(right){if(_x<x+450&&_x>x&&_y>y-40&&_y<y+40){_blood-=attacking*1.5;}}
            else{if(_x>x-450&&_x<x&&_y>y-40&&_y<y+40){_blood-=attacking*1.5;}}
        }
    }
    else if(max_attack){
        if(_x<x+150&&_x>x-150&&_y>y-120&&_y<y+120){_blood-=attacking;self_blood+=attacking;}
    }

}
int Hamburbaby::renew_state(float& _blood){
    if(_blood<=HMSTATE1&&state==0) state++;
    else if(_blood<=HMSTATE2&&state==1) state++;
    return state;
}
ALLEGRO_SAMPLE_INSTANCE *Hamburbaby::get_sample_instance(int command){
    //0->move
    //1->laser
    //2->maxlaser
    //3->explode
    if(command==0){return sound_move;}
    else if(command==1){return sound_laser;}
    else if(command==2){return sound_maxlaser;}
    else if(command==3){return sound_explode;}
}
bool Hamburbaby::get_movement(bool sel){
    //true->rest, false->attack.
    if(sel) return rest;
    else return attack;
}
