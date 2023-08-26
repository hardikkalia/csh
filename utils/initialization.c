#include "../headers.h"

void initialize_shell(){
        HOME_DIR=malloc(sizeof(char)*NAME_SIZE);
        WARP_PREV=malloc(sizeof(char)*PATH_SIZE);
        WARP_PREV[0]='\0';
        getcwd(HOME_DIR,128);
        EVENT_QUE=InitEventsQ();
        Create_history();
        BG_QUE=InitBGQue();
}