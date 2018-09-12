#include "Page_esc.h"

Page_esc::Page_esc(int Page){
    ///Button
    button = new Button;
    button->setting(PG_ESC_BUTTON_MAXCUR,PG_ESC_BUTTON_NUMBER,PG_ESC_BUTTON_WIDTH,PG_ESC_BUTTON_HEIGHT,
        PG_ESC_BUTTON_X,PG_ESC_BUTTON_Y,PG_ESC_BUTTON_dX,PG_ESC_BUTTON_dY,PG_ESC_BUTTON_DISPLACEMENT,PG_ESC_BUTTON_FILENAME1,PG_ESC_BUTTON_FILENAME2,8.5);
    control_selector=0;
    back_page=Page;
}
Page_esc::~Page_esc(){
    delete button;
}
void Page_esc::run(){
    button->run();
}
void Page_esc::draw(){
    button->draw();
    for(int i=0;i<PG_ESC_BUTTON_NUMBER;i++) button->draw_text(PG_ESC_BTN_name[i],i);
}
bool Page_esc::control(int command){
    /*
    UP->0
    DOWN->1
    ENTER->2
    */
    if(command == 2){
        if(control_selector==0){//BACK
            return true;
        }
        else if(control_selector==1){//MENU
            return true;
        }
        else if(control_selector==2){//QUIT
            return true;
        }
    }
    else if(command==0||command==1){
        control_selector=button->control(command);
    }
    return false;
}
ALLEGRO_SAMPLE_INSTANCE *Page_esc::get_sample_instance(int command){
    //shift->0
    //enter->1
    return button->get_sample_instance(command);
}
