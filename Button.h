#ifndef BTN_INCLUDE
#define BTN_INCLUDE

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <vector>

class Button{
    public:
        Button();
        ~Button();
        void setting(int mc, int bn, float w, float h, float x, float y, float dx, float dy, float dp, const char *buffer1, const char *buffer2, float font_scale);
        void run();
        void draw();
        void flip_move(){_move=!_move;cur=0;}
        void draw_text(const char *text, int index);
        int control(int command);
        ALLEGRO_SAMPLE_INSTANCE *get_sample_instance(int command);

    private:
        int cur, max_cur;
        int button_number;
        int control_selector;
        float width, height, position_x, position_y, d_x, d_y;
        float displacement;
        bool _move;
        ALLEGRO_BITMAP *img;
        ALLEGRO_FONT *font;
        ALLEGRO_SAMPLE *sample;
        ALLEGRO_SAMPLE_INSTANCE *sound_shift, *sound_select, *sound_shift2, *sound_select2;
};

#endif
