#ifndef ANI_OBJ_INCLUDE
#define ANI_OBJ_INCLUDE

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Animation_obj{
    public:
        Animation_obj(){
            max_cur=0;
            cur=0;
            appear=true;
        }
        ~Animation_obj(){al_destroy_bitmap(img);}
        void animate();
        void draw();
        void setting(int mc, float w, float h, float x, float y, const char *buffer);
        void flip_appear(){appear=!appear;};

    private:
        int max_cur, cur;
        bool appear;
        float width, height;
        float position_x, position_y;
        ALLEGRO_BITMAP *img;
};

#endif //ANI_OBJ
