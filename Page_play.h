#ifndef PAGE_PLAY_INCLUDE
#define PAGE_PLAY_INCLUDE

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "Animation_obj.h"
#include "Party_queen.h"
#include "Hamburbaby.h"
#include "Weed_llama.h"

///Animation
#define PG_PLAY_ANI_SIZE 1
const char PG_PLAY_ANI_filename[][20]={"disco"};
const int PG_PLAY_ANI_max_cur[]={6};
const float PG_PLAY_ANI_width[]={120};
const float PG_PLAY_ANI_height[]={120};
const float PG_PLAY_ANI_position_x[]={300};
const float PG_PLAY_ANI_position_y[]={0};

///Llama
#define LLAMA1_POSITION_X 169
#define LLAMA1_POSITION_Y 169
#define LLAMA2_POSITION_X 469
#define LLAMA2_POSITION_Y 250

///Blood
#define PQBLOOD 180.0
#define HMBLOOD 140.0
#define WLBLOOD 150.0
#define BLOOD_LIMIT 180.0

///Map
//Scope
#define MAP_UPLIMIT_X 0
#define MAP_DOWNLIMIT_X 640
#define MAP_UPLIMIT_Y 60
#define MAP_DOWNLIMIT_Y 400
//add_blood
#define MAP_AB_UPLIMIT_X 270
#define MAP_AB_DOWNLIMIT_X 370
#define MAP_AB_UPLIMIT_Y 50
#define MAP_AB_DOWNLIMIT_Y 90
#define MAP_ADD_BLOOD 0.5

class Page_play{
    public:
        Page_play(int s1, int s2);
        ~Page_play();
        bool run();
        void draw();
        void control(int command, bool first);
        bool get_values(){if(blood1<=0) return false; else return true;}
        int get_state1(){return state1;}
        int get_state2(){return state2;}
        bool get_movement(bool sel, bool first);
        bool get_count_down(){return (counter==90);}
        ALLEGRO_SAMPLE_INSTANCE *get_sample_instance(int command, bool first);

    private:
        void map_scope(float *x1, float *y1, float *x2, float *y2);
        std::vector<Animation_obj *> ani_set;
        int sel1, sel2;
        int counter;
        int state1, state2;
        float blood1, blood2;
        bool add_check1, add_check2;
        ALLEGRO_BITMAP *background;
        ALLEGRO_BITMAP *add_b, *level_one_b, *level_two_b, *add, *level_one, *level_two;
        ALLEGRO_FONT *font;
        Party_queen *PQllama1=nullptr, *PQllama2=nullptr;
        Hamburbaby *HMllama1=nullptr, *HMllama2=nullptr;
        Weed_llama *WLllama1=nullptr, *WLllama2=nullptr;

};

#endif //PAGE_PLAY_INCLUDE
