#include <vector>
#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include "Button.h"

///Button
#define PG_ESC_BUTTON_NUMBER 3
#define PG_ESC_BUTTON_MAXCUR 5
#define PG_ESC_BUTTON_WIDTH 155
#define PG_ESC_BUTTON_HEIGHT 17
#define PG_ESC_BUTTON_X 290
#define PG_ESC_BUTTON_Y 180
#define PG_ESC_BUTTON_dX 80
#define PG_ESC_BUTTON_dY 5
#define PG_ESC_BUTTON_DISPLACEMENT 30
#define PG_ESC_BUTTON_FILENAME1 "./image/Page_esc/selector.png"
#define PG_ESC_BUTTON_FILENAME2 "./WORD.ttf"
const char PG_ESC_BTN_name[][20]={"BACK", "MENU", "QUIT"};

class Page_esc{
    public:
        Page_esc(int Page=0);
        ~Page_esc();
        void run();
        void draw();
        bool control(int command);
        int get_control_selector(){return control_selector;}
        int get_back_page(){return back_page;}
        ALLEGRO_SAMPLE_INSTANCE *get_sample_instance(int command);

    private:
        Button *button;
        ALLEGRO_FONT *font;
        int control_selector;
        int back_page;
};

