#include <vector>
#include <stdio.h>
#include <iostream>
#include "Animation_obj.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_ttf.h>

///Animation
#define PG_WIN_ANI_SIZE 6
const char PG_WIN_ANI_filename[][20]={"win","hat","rest_map_right","walk_map_right","rest_map_left","walk_map_left"};
const int PG_WIN_ANI_max_cur[]={4,4,5,5,5,5};
const float PG_WIN_ANI_width[]={250,32,80,80,80,80};
const float PG_WIN_ANI_height[]={150,32,80,80,80,80};
const float PG_WIN_ANI_position_x[]={230,343,310,310,330,330};
const float PG_WIN_ANI_position_y[]={50,200,230,230,230,230};

class Page_win{
    public:
        Page_win(bool f_w);
        ~Page_win();
        void run();
        void draw();
        bool control(int command);
        ALLEGRO_SAMPLE_INSTANCE *get_sample_instance(){return sound_winner;}

    private:
        std::vector<Animation_obj *> ani_set;
        ALLEGRO_FONT *font;
        ALLEGRO_SAMPLE *sample;
        ALLEGRO_SAMPLE_INSTANCE *sound_winner;
        bool first_win;
        bool walk1, walk2;
};
