#include "Page_choose.h"

Page_choose::Page_choose(){
    ///Animation
    char buffer[70];
    for(int i=0;i<PG_CHOOSE_ANI_SIZE;i++){
        Animation_obj *p=new Animation_obj;
        sprintf(buffer, "./image/Page_choose/%s.png", PG_CHOOSE_ANI_filename[i]);
        p->setting(PG_CHOOSE_ANI_max_cur[i], PG_CHOOSE_ANI_width[i], PG_CHOOSE_ANI_height[i],
            PG_CHOOSE_ANI_position_x[i], PG_CHOOSE_ANI_position_y[i], buffer);
        ani_set.push_back(p);
    }
    ani_set[3]->flip_appear();ani_set[4]->flip_appear();
    ani_set[6]->flip_appear();ani_set[7]->flip_appear();
    ///Button
    button1 = new Button;
    button1->setting(PG_CHOOSE_BUTTON_MAXCUR,PG_CHOOSE_BUTTON_NUMBER,PG_CHOOSE_BUTTON_WIDTH,PG_CHOOSE_BUTTON_HEIGHT,
        PG_CHOOSE_BUTTON_X,PG_CHOOSE_BUTTON_Y,PG_CHOOSE_BUTTON_dX,PG_CHOOSE_BUTTON_dY,PG_CHOOSE_BUTTON_DISPLACEMENT,PG_CHOOSE_BUTTON_FILENAME1,PG_CHOOSE_BUTTON_FILENAME2,8.5);
    button2 = new Button;
    button2->setting(PG_CHOOSE_BUTTON_MAXCUR,PG_CHOOSE_BUTTON_NUMBER,PG_CHOOSE_BUTTON_WIDTH,PG_CHOOSE_BUTTON_HEIGHT,
        PG_CHOOSE_BUTTON_X+355,PG_CHOOSE_BUTTON_Y,PG_CHOOSE_BUTTON_dX,PG_CHOOSE_BUTTON_dY,PG_CHOOSE_BUTTON_DISPLACEMENT,PG_CHOOSE_BUTTON_FILENAME1,PG_CHOOSE_BUTTON_FILENAME2,8.5);

    crown=al_load_bitmap("./image/Page_choose/crown.png");
    go=al_load_bitmap("./image/Page_choose/go.png");
    control_selector1=0;
    control_selector2=0;
    check1=false;
    check2=false;
}
Page_choose::~Page_choose(){
    for(auto e:ani_set){delete e;}
    ani_set.clear();
    delete button1;
    delete button2;
    al_destroy_bitmap(crown);
}
void Page_choose::run(){
    for(int i=0;i<PG_CHOOSE_ANI_SIZE;i++) ani_set[i]->animate();
    button1->run();
    button2->run();
}
void Page_choose::draw(){
    for(int i=0;i<PG_CHOOSE_ANI_SIZE;i++) ani_set[i]->draw();
    for(int i=0;i<PG_CHOOSE_BUTTON_NUMBER;i++) {
        button1->draw_text(PG_CHOOSE_BTN_name[i],i);
        button2->draw_text(PG_CHOOSE_BTN_name[i],i);
    }
    if(check1) al_draw_bitmap(crown,183,270,0);
    if(check2) al_draw_bitmap(crown,535,270,0);
    if(check1&&check2) al_draw_bitmap(go,350,200,0);
    button1->draw();
    button2->draw();
}
bool Page_choose::control(int command, bool first){
    if(check1&&check2&&command==2) return true;
    if(first){
        if((command == 0||command == 1)&&!check1){
            ani_set[2+control_selector1]->flip_appear();
            control_selector1=button1->control(command);
            ani_set[2+control_selector1]->flip_appear();
        }
        else if(command == 3){
            check1=!check1;
            button1->flip_move();
        }
    }
    else{
        if((command == 0||command == 1)&&!check2){
            ani_set[5+control_selector2]->flip_appear();
            control_selector2=button2->control(command);
            ani_set[5+control_selector2]->flip_appear();
        }
        else if(command == 3){
            check2=!check2;
            button2->flip_move();
        }
    }
    return false;
}
int Page_choose::get_values(int sel){
    //0->control_selector1
    //1->control_selector2
    //0->check1
    //1->check2
    if(sel == 0) return control_selector1;
    else if(sel == 1) return control_selector2;
    else if(sel == 2) return check1;
    else if(sel == 3) return check2;
}
ALLEGRO_SAMPLE_INSTANCE *Page_choose::get_sample_instance(int command, bool first){
    //shift->0
    //enter->1
    if(first) return button1->get_sample_instance(command);
    else return button2->get_sample_instance(command);
}
