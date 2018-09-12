#include "Animation_obj.h"
void Animation_obj::animate(){
    cur++;
    if(cur==max_cur) cur=0;
}
void Animation_obj::draw(){
    if(appear)al_draw_bitmap_region(img,cur*width,0,width,height,position_x,position_y,0);
}
void Animation_obj::setting(int mc, float w, float h, float x, float y, const char *buffer){
    max_cur=mc;
    img=al_load_bitmap(buffer);
    width=w;
    height=h;
    position_x=x;
    position_y=y;
}
