#include "Button.h"

Button::Button(){
    cur=0;
    control_selector=0;
    _move=true;
    img=nullptr;
    font=nullptr;
    sample = al_load_sample("./music/sound_shift.wav");
    sound_shift = al_create_sample_instance(sample);
    sample = al_load_sample("./music/sound_select.wav");
    sound_select = al_create_sample_instance(sample);
    //sample = al_load_sample("./music/sound_shift2.wav");
    //sound_shift2 = al_create_sample_instance(sample);
    //sample = al_load_sample("./music/sound_select2.wav");
    //sound_select2 = al_create_sample_instance(sample);
}

Button::~Button(){
    al_destroy_bitmap(img);
    al_destroy_font(font);
    al_destroy_sample(sample);
    al_destroy_sample_instance(sound_select);
    al_destroy_sample_instance(sound_shift);
}

void Button::setting(int mc, int bn, float w, float h, float x, float y, float dx, float dy, float dp, const char *buffer1, const char *buffer2, float font_scale){
    max_cur=mc;
    button_number=bn;
    width=w;
    height=h;
    position_x=x;
    position_y=y;
    d_x=dx;
    d_y=dy;
    displacement=dp;
    img=al_load_bitmap(buffer1);
    font=al_load_font(buffer2, font_scale, 0);
}

void Button::run(){
    if(_move){
        cur++;
        if(cur == max_cur) cur=0;
    }
}

void Button::draw(){
    /*You can change the style by rewriting here.*/
    al_draw_bitmap_region(img,cur*width,0,width,height,position_x,position_y+displacement*control_selector,0);
}

void Button::draw_text(const char *text, int index){
    /*You can change the style by rewriting here.*/
    al_draw_text(font,al_map_rgb(255,255,255),position_x+d_x,position_y+displacement*index+d_y,1,text);
}

int Button::control(int command){
    /*UP = 0; DOWN = 1;*/
    if(command == 0){
        control_selector--;
        if(control_selector == -1) control_selector=button_number-1;
    }
    else if(command == 1){
        control_selector++;
        if(control_selector == button_number) control_selector=0;
    }
    return control_selector;
}
ALLEGRO_SAMPLE_INSTANCE *Button::get_sample_instance(int command){
    if(command == 0) return sound_shift;
    else if(command == 1) return sound_select;
}
