#include <vector>
#include <stdio.h>
#include <iostream>
#include "Animation_obj.h"
#include "Button.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_ttf.h>

///Animation
#define PG_MENU_ANI_SIZE 10
const char PG_MENU_ANI_filename[][20]={"battle_llama2","hand_left","hand_right","rest_map_right","walk_map_right","laser_map_right","rest_map_left","walk_map_left","laser_map_left","ha"};
const int PG_MENU_ANI_max_cur[]={10,6,6,5,5,9,5,5,9,19};
const float PG_MENU_ANI_width[]={180,120,120,80,80,144,80,80,144,70};
const float PG_MENU_ANI_height[]={180,120,120,80,80,90,80,80,90,101};
const float PG_MENU_ANI_position_x[]={275,130,480,160,160,220,470,470,340,315};
const float PG_MENU_ANI_position_y[]={50,70,70,100,100,100,100,100,100,150};

///Button
#define PG_MENU_BUTTON_NUMBER 4
#define PG_MENU_BUTTON_MAXCUR 6
#define PG_MENU_BUTTON_WIDTH 180
#define PG_MENU_BUTTON_HEIGHT 60
#define PG_MENU_BUTTON_X 275
#define PG_MENU_BUTTON_Y 240
#define PG_MENU_BUTTON_dX 95
#define PG_MENU_BUTTON_dY 25
#define PG_MENU_BUTTON_DISPLACEMENT 40
#define PG_MENU_BUTTON_FILENAME1 "./image/Page_menu/selector.png"
#define PG_MENU_BUTTON_FILENAME2 "./WORD.ttf"
const char PG_MENU_BTN_name[][20]={"START", "CONTROL", "ABOUT", "QUIT"};

///Font
const char PG_MENU_FONT_contain[][20]={"PLAYER1","PLAYER2","W","A S D","Q","I","J K L","O","MOVE","ATTACK"};
const float PG_MENU_FONT_position_x[]={200,520,200,200,200,520,520,520,360,360};
const float PG_MENU_FONT_position_y[]={250,250,300,330,380,300,330,380,315,380};

class Page_menu{
    public:
        Page_menu();
        ~Page_menu();
        void run();
        void draw();
        bool control(int command);
        bool get_quit(){return quit;}
        bool get_into(){return into;}
        ALLEGRO_SAMPLE_INSTANCE *get_sample_instance(int command);

    private:
        ALLEGRO_FONT *font;
        std::vector<Animation_obj *> ani_set;
        Button *button;
        int control_selector;
        bool into;
        bool quit;
        bool walk1, walk2, attack1, attack2;
};
