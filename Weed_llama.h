#ifndef WEED_LLAMA_INCLUDE
#define WEED_LLAMA_INCLUDE

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>

#define WLWIDTH 80
#define WLHEIGHT 80
#define WLATTACKING 1
#define WLWIDTH_LASER 144
#define WLHEIGHT_LASER 90
#define WLWIDTH_LASER_MAX 400
#define WLHEIGHT_LASER_MAX 100
#define WLWIDTH_MAXATTACK 170
#define WLHEIGHT_MAXATTACK 150
#define WLWIDTH_EXPLODE 150
#define WLHEIGHT_EXPLODE 150
#define WLSPEED 8
#define WLSTATE1 70
#define WLSTATE2 40

class Weed_llama{
    public:
        Weed_llama(int _x, int _y, bool p1);
        ~Weed_llama();
        void run();
        void draw();
        void control(int command);
        void renew_blood(float& _x, float& _y, float& _blood);
        int renew_state(float& _blood);
        float x,y;
        bool get_movement(bool sel);
        ALLEGRO_SAMPLE_INSTANCE *get_sample_instance(int command);

    private:
        float attacking;
        int cur, cur_att, cur_maxattack, cur_explode;
        int state;
        bool rest;
        bool attack, max_attack;
        bool right;
        bool movement[4];//UP,DOWN,LEFT,RIGHT
        ALLEGRO_BITMAP *rest_map_left, *rest_map_right;
        ALLEGRO_BITMAP *walk_map_left, *walk_map_right;
        ALLEGRO_BITMAP *wl_rest_map_left, *wl_rest_map_right;
        ALLEGRO_BITMAP *wl_walk_map_left, *wl_walk_map_right;
        ALLEGRO_BITMAP *laser_map_left, *laser_map_right;
        ALLEGRO_BITMAP *wl_laser_map_left, *wl_laser_map_right;
        ALLEGRO_BITMAP *wl_maxattack_map, *wl_explode_map;
        ALLEGRO_SAMPLE *sample;
        ALLEGRO_SAMPLE_INSTANCE *sound_move, *sound_laser, *sound_maxlaser, *sound_explode;
};

#endif //WEED_LLAMA_INCLUDE
