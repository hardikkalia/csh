#include "../headers.h"

void terminate_shell(){
    free(SHELL_PID);
    free(FG_PROC);
    free(HOME_DIR);
    free(WARP_PREV);
    free(PRINT_BUFFER);
    free(TIME);
    signal(SIGINT,SIG_DFL);
    SHELL_PID=NULL;
    FG_PROC=NULL;
    HOME_DIR=NULL;
    WARP_PREV=NULL;
    PRINT_BUFFER=NULL;
    TIME=NULL;
}