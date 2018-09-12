#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

#include "Page_menu.h"
#include "Page_choose.h"
#include "Page_play.h"
#include "Page_win.h"
#include "Page_esc.h"

///Display size
#define DISPLAY_WIDTH 720
#define DISPLAY_HEIGHT 480

///Game state
#define GAME_EXIT 0
#define GAME_CONTINUE 1

///Page
#define PAGE_MENU 0
#define PAGE_CHOOSE 1
#define PAGE_PLAY 2
#define PAGE_WIN 3
#define PAGE_ESC 4

///Command
#define UP 0
#define DOWN 1
#define ENTER 2
#define CHECK 3
#define LEFT 4
#define RIGHT 5
#define ATTACK 6

#define ATTACK_UNPRESS 7
#define UP_UNPRESS 8
#define DOWN_UNPRESS 9
#define LEFT_UNPRESS 10
#define RIGHT_UNPRESS 11
#define ATTACK_MAX 12

const float FPS = 24;

class Game_window{
    public:
        Game_window(){game_setting();}
        ~Game_window(){game_destroy();}
        void game_setting();
        void game_play();
        bool game_run();
        bool process_event();
        bool draw_running_map();
        void game_destroy();

    private:
        ALLEGRO_BITMAP *icon;
        ALLEGRO_DISPLAY* display;
        ALLEGRO_EVENT_QUEUE *event_queue;
        ALLEGRO_EVENT event;
        ALLEGRO_TIMER *timer;

        ALLEGRO_SAMPLE *sample;
        ALLEGRO_SAMPLE_INSTANCE *sound_background;

        Page_menu *PG_MENU;
        Page_choose *PG_CHOOSE;
        Page_play *PG_PLAY;
        Page_win *PG_WIN;
        Page_esc *PG_ESC;
        int page;
        bool next_page;
};
