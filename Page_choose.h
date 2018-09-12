#include <vector>
#include <stdio.h>
#include <iostream>
#include "Animation_obj.h"
#include "Button.h"
#include <allegro5/allegro_audio.h>

///Animation
#define PG_CHOOSE_ANI_SIZE 9
const char PG_CHOOSE_ANI_filename[][20]={"circle","circle","hat","hamburger","weed","hat","hamburger","weed","disco"};
const int PG_CHOOSE_ANI_max_cur[]={6,6,4,4,4,4,4,4,6};
const float PG_CHOOSE_ANI_width[]={180,180,32,32,32,32,32,32,120};
const float PG_CHOOSE_ANI_height[]={180,180,32,32,32,32,32,32,120};
const float PG_CHOOSE_ANI_position_x[]={100,450,175,175,175,525,525,525,305};
const float PG_CHOOSE_ANI_position_y[]={50,50,125,125,125,125,125,125,0};

///Button
#define PG_CHOOSE_BUTTON_NUMBER 3
#define PG_CHOOSE_BUTTON_MAXCUR 5
#define PG_CHOOSE_BUTTON_WIDTH 155
#define PG_CHOOSE_BUTTON_HEIGHT 17
#define PG_CHOOSE_BUTTON_X 110
#define PG_CHOOSE_BUTTON_Y 305
#define PG_CHOOSE_BUTTON_dX 80
#define PG_CHOOSE_BUTTON_dY 5
#define PG_CHOOSE_BUTTON_DISPLACEMENT 30
#define PG_CHOOSE_BUTTON_FILENAME1 "./image/Page_choose/selector.png"
#define PG_CHOOSE_BUTTON_FILENAME2 "./WORD.ttf"
const char PG_CHOOSE_BTN_name[][20]={"PARTYQUEEN", "HAMBURBABY", "WEEDLLAMA"};

class Page_choose{
    public:
        Page_choose();
        ~Page_choose();
        void run();
        void draw();
        bool control(int command, bool first);
        int get_values(int sel);
        ALLEGRO_SAMPLE_INSTANCE *get_sample_instance(int command, bool first);

    private:
        std::vector<Animation_obj *> ani_set;
        Button *button1, *button2;
        ALLEGRO_BITMAP *crown, *go;
        int control_selector1, control_selector2;
        bool check1, check2;
};
