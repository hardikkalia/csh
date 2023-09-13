#include "../headers.h"

void initialize_shell(){
        SHELL_PID=malloc(sizeof(pid_t));
        HOME_DIR=malloc(sizeof(char)*NAME_SIZE);
        WARP_PREV=malloc(sizeof(char)*PATH_SIZE);
        PRINT_BUFFER=malloc(sizeof(char)*PRINT_BUF_SIZE);
        TIME=malloc(sizeof(struct sttime));
        TIME->command=NULL;
        TIME->time=NULL;

        FG_PROC=malloc(sizeof(struct fg));
        FG_PROC->FG_PID=getpid();
        WARP_PREV[0]='\0';
        getcwd(HOME_DIR,128);
        EVENT_QUE=InitEventsQ();
        Create_history();
        InitBGQue();
        *SHELL_PID=getpid();
        signal(SIGINT,interrupt_fg);
        signal(SIGTSTP,send_to_bg);
}