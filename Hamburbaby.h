#ifndef HAMBURBABY_INCLUDE
#define HAMBURBABY_INCLUDE

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>

#define HMWIDTH 80
#define HMHEIGHT 80
#define HMATTACKING 1
#define HMWIDTH_LASER 144
#define HMHEIGHT_LASER 90
#define HMWIDTH_LASER_MAX 400
#define HMHEIGHT_LASER_MAX 100
#define HMWIDTH_MAXATTACK 170
#define HMHEIGHT_MAXATTACK 150
#define HMWIDTH_EXPLODE 60
#define HMHEIGHT_EXPLODE 60
#define HMSPEED 5
#define HMSTATE1 100
#define HMSTATE2 40

class Hamburbaby{
    public:
        Hamburbaby(int _x, int _y, bool p1);
        ~Hamburbaby();
        void run();
        void draw();
        void control(int command);
        void renew_blood(float& _x, float& _y, float& _blood, float& self_blood);
        int renew_state(float& _blood);
        bool get_movement(bool sel);
        float x,y;
        ALLEGRO_SAMPLE_INSTANCE *get_sample_instance(int command);

    private:
        float attacking;
        int cur, cur_att, cur_maxattack;
        int state;
        bool rest;
        bool attack, max_attack;
        bool right;
        bool movement[4];//UP,DOWN,LEFT,RIGHT
        ALLEGRO_BITMAP *rest_map_left, *rest_map_right;
        ALLEGRO_BITMAP *walk_map_left, *walk_map_right;
        ALLEGRO_BITMAP *hm_rest_map_left, *hm_rest_map_right;
        ALLEGRO_BITMAP *hm_walk_map_left, *hm_walk_map_right;
        ALLEGRO_BITMAP *laser_map_left, *laser_map_right;
        ALLEGRO_BITMAP *hm_laser_map_left, *hm_laser_map_right;
        ALLEGRO_BITMAP *hm_maxattack_map, *hm_explode_map;
        ALLEGRO_SAMPLE *sample;
        ALLEGRO_SAMPLE_INSTANCE *sound_move, *sound_laser, *sound_maxlaser, *sound_explode;
};

#endif //AMBURBABY_INCLUDE_INCLUDE

