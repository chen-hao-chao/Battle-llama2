#ifndef PARTY_QUEEN_INCLUDE
#define PARTY_QUEEN_INCLUDE

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>

#define PQWIDTH 80
#define PQHEIGHT 80
#define PQATTACKING 1
#define PQWIDTH_LASER 144
#define PQHEIGHT_LASER 90
#define PQWIDTH_LASER_MAX 400
#define PQHEIGHT_LASER_MAX 100
#define PQWIDTH_MAXATTACK 170
#define PQHEIGHT_MAXATTACK 150
#define PQWIDTH_EXPLODE 60
#define PQHEIGHT_EXPLODE 60
#define PQSPEED 6
#define PQSTATE1 90
#define PQSTATE2 60

class Party_queen{
    public:
        Party_queen(int _x, int _y, bool p1);
        ~Party_queen();
        void run();
        void draw();
        void control(int command);
        void renew_blood(float& _x, float& _y, float& _blood);
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
        ALLEGRO_BITMAP *pq_rest_map_left, *pq_rest_map_right;
        ALLEGRO_BITMAP *pq_walk_map_left, *pq_walk_map_right;
        ALLEGRO_BITMAP *laser_map_left, *laser_map_right;
        ALLEGRO_BITMAP *pq_laser_map_left, *pq_laser_map_right;
        ALLEGRO_BITMAP *pq_maxattack_map, *pq_explode_map;
        ALLEGRO_SAMPLE *sample;
        ALLEGRO_SAMPLE_INSTANCE *sound_move, *sound_laser, *sound_maxlaser, *sound_explode;
};

#endif //PARTY_QUEEN_INCLUDE
