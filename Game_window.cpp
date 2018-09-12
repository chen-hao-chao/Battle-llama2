#include "Game_window.h"

void Game_window::game_setting(){
    if (!al_init()) std::cout<<"Fail to initialize...";

    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);

    ///addons
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_acodec_addon();

    al_install_keyboard();
    al_install_mouse();
    al_install_audio();
    al_reserve_samples(1);

    ///registor
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    ///load things.
    icon = al_load_bitmap("./icon.png");
    al_set_display_icon(display, icon);

    ///Page setting
    PG_MENU = new Page_menu;
    page=PAGE_MENU;
    next_page=false;
    for(int i=0;i<2;i++) al_attach_sample_instance_to_mixer(PG_MENU->get_sample_instance(i),al_get_default_mixer());

    ///Sound
    sample = al_load_sample("./music/background.wav");
    sound_background = al_create_sample_instance(sample);
    al_attach_sample_instance_to_mixer(sound_background,al_get_default_mixer());
    al_play_sample_instance(sound_background);

    ///Timer
    al_start_timer(timer);
}
void Game_window::game_play(){
    bool msg=true;
    while(msg != GAME_EXIT){
        msg = game_run();
    }
}
bool Game_window::game_run(){
    bool error=GAME_CONTINUE;
    if (!al_is_event_queue_empty(event_queue)) error=process_event();
    return error;
}
bool Game_window::process_event(){
    bool instruction = GAME_CONTINUE;
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_TIMER){
        if(page == PAGE_MENU){PG_MENU->run();}
        else if(page == PAGE_CHOOSE){PG_CHOOSE->run();}
        else if(page == PAGE_PLAY){
            next_page=PG_PLAY->run();
            if(!PG_PLAY->get_movement(1,1)){al_play_sample_instance(PG_PLAY->get_sample_instance(0,1));}
            if(PG_PLAY->get_movement(0,1)){
                if(PG_PLAY->get_state1()==0)al_play_sample_instance(PG_PLAY->get_sample_instance(1,1));
                else al_play_sample_instance(PG_PLAY->get_sample_instance(2,1));
            }
            if(!PG_PLAY->get_movement(1,0)){al_play_sample_instance(PG_PLAY->get_sample_instance(0,0));}
            if(PG_PLAY->get_movement(0,0)){
                if(PG_PLAY->get_state2()==0)al_play_sample_instance(PG_PLAY->get_sample_instance(1,0));
                else al_play_sample_instance(PG_PLAY->get_sample_instance(2,0));
            }
        }
        else if(page == PAGE_WIN){PG_WIN->run();}
        else if(page == PAGE_ESC){PG_ESC->run();}
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
        if(page == PAGE_MENU){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    next_page=PG_MENU->control(UP);
                    if(!PG_MENU->get_into())al_play_sample_instance(PG_MENU->get_sample_instance(0));
                    break;
                case ALLEGRO_KEY_DOWN:
                    next_page=PG_MENU->control(DOWN);
                    if(!PG_MENU->get_into())al_play_sample_instance(PG_MENU->get_sample_instance(0));
                    break;
                case ALLEGRO_KEY_ENTER:
                    next_page=PG_MENU->control(ENTER);
                    al_play_sample_instance(PG_MENU->get_sample_instance(1));
                    break;
                case ALLEGRO_KEY_W:
                case ALLEGRO_KEY_S:
                case ALLEGRO_KEY_A:
                case ALLEGRO_KEY_D:
                    next_page=PG_MENU->control(4);
                    break;
                case ALLEGRO_KEY_Q:
                    next_page=PG_MENU->control(5);
                    break;
                case ALLEGRO_KEY_I:
                case ALLEGRO_KEY_K:
                case ALLEGRO_KEY_L:
                case ALLEGRO_KEY_J:
                    next_page=PG_MENU->control(8);
                    break;
                case ALLEGRO_KEY_O:
                    next_page=PG_MENU->control(9);
                    break;
            }
        }
        else if(page == PAGE_CHOOSE){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_W:
                    next_page=PG_CHOOSE->control(UP,1);
                    if(!PG_CHOOSE->get_values(2))al_play_sample_instance(PG_CHOOSE->get_sample_instance(0,1));
                    break;
                case ALLEGRO_KEY_S:
                    next_page=PG_CHOOSE->control(DOWN,1);
                    if(!PG_CHOOSE->get_values(2))al_play_sample_instance(PG_CHOOSE->get_sample_instance(0,1));
                    break;
                case ALLEGRO_KEY_Q:
                    next_page=PG_CHOOSE->control(CHECK,1);
                    al_play_sample_instance(PG_CHOOSE->get_sample_instance(1,1));
                    break;
                case ALLEGRO_KEY_I:
                    next_page=PG_CHOOSE->control(UP,0);
                    if(!PG_CHOOSE->get_values(3))al_play_sample_instance(PG_CHOOSE->get_sample_instance(0,0));
                    break;
                case ALLEGRO_KEY_K:
                    next_page=PG_CHOOSE->control(DOWN,0);
                    if(!PG_CHOOSE->get_values(3))al_play_sample_instance(PG_CHOOSE->get_sample_instance(0,0));
                    break;
                case ALLEGRO_KEY_U:
                    next_page=PG_CHOOSE->control(CHECK,0);
                    al_play_sample_instance(PG_CHOOSE->get_sample_instance(1,0));
                    break;
                case ALLEGRO_KEY_ENTER:
                    next_page=PG_CHOOSE->control(ENTER,1);
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    PG_ESC = new Page_esc(page);
                    page=PAGE_ESC;
                    for(int i=0;i<2;i++) al_attach_sample_instance_to_mixer(PG_ESC->get_sample_instance(i),al_get_default_mixer());
                    break;
            }
        }
        else if(page == PAGE_PLAY){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_W:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(UP,1);
                    }
                    break;
                case ALLEGRO_KEY_S:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(DOWN,1);
                    }
                    break;
                case ALLEGRO_KEY_A:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(LEFT,1);
                    }
                    break;
                case ALLEGRO_KEY_D:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(RIGHT,1);
                    }
                    break;
                case ALLEGRO_KEY_Q:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(ATTACK,1);
                    }
                    break;
                case ALLEGRO_KEY_E:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(ATTACK_MAX,1);
                        if(PG_PLAY->get_state1()==2)al_play_sample_instance(PG_PLAY->get_sample_instance(3,1));
                    }
                    break;
                case ALLEGRO_KEY_I:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(UP,0);
                    }
                    break;
                case ALLEGRO_KEY_K:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(DOWN,0);
                    }
                    break;
                case ALLEGRO_KEY_J:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(LEFT,0);
                    }
                    break;
                case ALLEGRO_KEY_L:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(RIGHT,0);
                    }
                    break;
                case ALLEGRO_KEY_O:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(ATTACK,0);
                    }
                    break;
                case ALLEGRO_KEY_U:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(ATTACK_MAX,0);
                        if(PG_PLAY->get_state2()==2)al_play_sample_instance(PG_PLAY->get_sample_instance(3,0));
                    }
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    PG_ESC = new Page_esc(page);
                    page=PAGE_ESC;
                    for(int i=0;i<2;i++) al_attach_sample_instance_to_mixer(PG_ESC->get_sample_instance(i),al_get_default_mixer());
                    break;
            }
        }
        else if(page == PAGE_WIN){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_ENTER:
                    next_page=PG_WIN->control(4);
                    break;
                case ALLEGRO_KEY_W:
                case ALLEGRO_KEY_S:
                case ALLEGRO_KEY_A:
                case ALLEGRO_KEY_D:
                    next_page=PG_WIN->control(0);
                    break;
                case ALLEGRO_KEY_I:
                case ALLEGRO_KEY_K:
                case ALLEGRO_KEY_L:
                case ALLEGRO_KEY_J:
                    next_page=PG_WIN->control(2);
                    break;
            }
        }
        else if(page == PAGE_ESC){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    next_page=PG_ESC->control(0);
                    al_play_sample_instance(PG_ESC->get_sample_instance(0));
                    break;
                case ALLEGRO_KEY_DOWN:
                    next_page=PG_ESC->control(1);
                    al_play_sample_instance(PG_ESC->get_sample_instance(0));
                    break;
                case ALLEGRO_KEY_ENTER:
                    next_page=PG_ESC->control(2);
                    al_play_sample_instance(PG_ESC->get_sample_instance(1));
                    break;
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP){
        if(page == PAGE_MENU){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                case ALLEGRO_KEY_DOWN:
                    if(!PG_MENU->get_into())al_stop_sample_instance(PG_MENU->get_sample_instance(0));
                    break;
                case ALLEGRO_KEY_ENTER:
                    al_stop_sample_instance(PG_MENU->get_sample_instance(1));
                    break;
                case ALLEGRO_KEY_W:
                case ALLEGRO_KEY_S:
                case ALLEGRO_KEY_A:
                case ALLEGRO_KEY_D:
                    next_page=PG_MENU->control(6);
                    break;
                case ALLEGRO_KEY_Q:
                    next_page=PG_MENU->control(7);
                    break;
                case ALLEGRO_KEY_I:
                case ALLEGRO_KEY_K:
                case ALLEGRO_KEY_L:
                case ALLEGRO_KEY_J:
                    next_page=PG_MENU->control(10);
                    break;
                case ALLEGRO_KEY_O:
                    next_page=PG_MENU->control(11);
                    break;
            }
        }
        if(page == PAGE_CHOOSE){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_W:
                case ALLEGRO_KEY_S:
                    if(!PG_CHOOSE->get_values(2))al_stop_sample_instance(PG_CHOOSE->get_sample_instance(0,1));
                    break;
                case ALLEGRO_KEY_I:
                case ALLEGRO_KEY_K:
                    if(!PG_CHOOSE->get_values(3))al_stop_sample_instance(PG_CHOOSE->get_sample_instance(0,0));
                    break;
                case ALLEGRO_KEY_Q:
                    al_stop_sample_instance(PG_CHOOSE->get_sample_instance(1,1));
                    break;
                case ALLEGRO_KEY_U:
                    al_stop_sample_instance(PG_CHOOSE->get_sample_instance(1,0));
                    break;
            }
        }
        else if(page == PAGE_PLAY){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_W:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(UP_UNPRESS,1);
                    }
                    break;
                case ALLEGRO_KEY_S:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(DOWN_UNPRESS,1);
                    }
                    break;
                case ALLEGRO_KEY_A:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(LEFT_UNPRESS,1);
                    }
                    break;
                case ALLEGRO_KEY_D:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(RIGHT_UNPRESS,1);
                    }
                    break;
                case ALLEGRO_KEY_Q:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(ATTACK_UNPRESS,1);
                    }
                    break;
                case ALLEGRO_KEY_I:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(UP_UNPRESS,0);
                    }
                    break;
                case ALLEGRO_KEY_K:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(DOWN_UNPRESS,0);
                    }
                    break;
                case ALLEGRO_KEY_J:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(LEFT_UNPRESS,0);
                    }
                    break;
                case ALLEGRO_KEY_L:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(RIGHT_UNPRESS,0);
                    }
                    break;
                case ALLEGRO_KEY_O:
                    if(PG_PLAY->get_count_down()){
                        PG_PLAY->control(ATTACK_UNPRESS,0);
                    }
                    break;
            }
        }
        else if(page == PAGE_WIN){
             switch(event.keyboard.keycode){
                case ALLEGRO_KEY_W:
                case ALLEGRO_KEY_S:
                case ALLEGRO_KEY_A:
                case ALLEGRO_KEY_D:
                    next_page=PG_WIN->control(1);
                    break;
                case ALLEGRO_KEY_I:
                case ALLEGRO_KEY_K:
                case ALLEGRO_KEY_L:
                case ALLEGRO_KEY_J:
                    next_page=PG_WIN->control(3);
                    break;
             }
        }
        else if(page == PAGE_ESC){
             switch(event.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                case ALLEGRO_KEY_DOWN:
                    al_stop_sample_instance(PG_ESC->get_sample_instance(0));
                    break;
                case ALLEGRO_KEY_ENTER:
                    al_stop_sample_instance(PG_ESC->get_sample_instance(1));
                    break;
             }
        }
    }
    if(!draw_running_map()) return GAME_EXIT;
    return instruction;
}
bool Game_window::draw_running_map(){
    if(page == PAGE_MENU){
        if(next_page){
            if(PG_MENU->get_quit()){
                delete PG_MENU;
                return GAME_EXIT;
            }
            else{
                delete PG_MENU;
                next_page=false;
                page=PAGE_CHOOSE;
                PG_CHOOSE=new Page_choose;
                for(int i=0;i<2;i++) al_attach_sample_instance_to_mixer(PG_CHOOSE->get_sample_instance(i,1),al_get_default_mixer());
                for(int i=0;i<2;i++) al_attach_sample_instance_to_mixer(PG_CHOOSE->get_sample_instance(i,0),al_get_default_mixer());
            }
        }
        else{
            PG_MENU->draw();
        }
    }
    else if(page == PAGE_CHOOSE){
        if(next_page){
            int sel1=PG_CHOOSE->get_values(0);
            int sel2=PG_CHOOSE->get_values(1);
            PG_PLAY=new Page_play(sel1,sel2);
            page=PAGE_PLAY;
            next_page=false;
            delete PG_CHOOSE;
            for(int i=0;i<4;i++) al_attach_sample_instance_to_mixer(PG_PLAY->get_sample_instance(i,1),al_get_default_mixer());
            for(int i=0;i<4;i++) al_attach_sample_instance_to_mixer(PG_PLAY->get_sample_instance(i,0),al_get_default_mixer());
        }
        else{
            PG_CHOOSE->draw();
        }
    }
    else if(page == PAGE_PLAY){
        if(next_page){
            bool first_win=PG_PLAY->get_values();
            PG_WIN=new Page_win(first_win);
            delete PG_PLAY;
            next_page=false;
            page=PAGE_WIN;
            al_attach_sample_instance_to_mixer(PG_WIN->get_sample_instance(),al_get_default_mixer());
            al_play_sample_instance(PG_WIN->get_sample_instance());
        }
        else{
            PG_PLAY->draw();
        }
    }
    else if(page == PAGE_WIN){
        if(next_page){
            delete PG_WIN;
            next_page=false;
            page=PAGE_MENU;
            PG_MENU=new Page_menu;
            for(int i=0;i<2;i++) al_attach_sample_instance_to_mixer(PG_MENU->get_sample_instance(i),al_get_default_mixer());
        }
        else{
            PG_WIN->draw();
        }
    }
    else if(page == PAGE_ESC){
        if(next_page){
            if(PG_ESC->get_control_selector()==0){//BACK
                next_page=false;
                page=PG_ESC->get_back_page();
            }
            else if(PG_ESC->get_control_selector()==1){//MENU
                if(PG_ESC->get_back_page()==PAGE_CHOOSE) delete PG_CHOOSE;
                else if(PG_ESC->get_back_page()==PAGE_PLAY) delete PG_PLAY;

                PG_MENU=new Page_menu;
                page=PAGE_MENU;
                next_page=false;
                for(int i=0;i<2;i++) al_attach_sample_instance_to_mixer(PG_MENU->get_sample_instance(i),al_get_default_mixer());
            }
            else if(PG_ESC->get_control_selector()==2){//QUIT
                delete PG_ESC;
                return GAME_EXIT;
            }
            delete PG_ESC;
        }
        else{
            PG_ESC->draw();
        }
    }
    al_flip_display();
    al_clear_to_color(al_map_rgb(0,0,0));
    return GAME_CONTINUE;
}
void Game_window::game_destroy(){
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_bitmap(icon);
    al_destroy_sample(sample);
    al_destroy_sample_instance(sound_background);

    if(page==PAGE_MENU) delete PG_MENU;
    else if(page==PAGE_CHOOSE)delete PG_CHOOSE;
    else if(page==PAGE_PLAY)delete PG_PLAY;
    else if(page==PAGE_WIN)delete PG_WIN;
}
