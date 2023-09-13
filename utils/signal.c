#include "../headers.h"
void interrupt_fg(){
    
    if(FG_PROC->FG_PID==*(SHELL_PID)){
        printf("\n");
        prompt();
    }
    else{
        kill(FG_PROC->FG_PID,SIGINT);
        FG_PROC->FG_PID=*(SHELL_PID);
        printf("\n");
    }
    fflush(stdout);
}

void send_to_bg(){
    if(FG_PROC->FG_PID==*(SHELL_PID)){
        printf("\n");
        prompt();
    }
    else{
        printf("\n");
        kill(FG_PROC->FG_PID,SIGSTOP);
        BG_QUE->Enque(strtok(FG_PROC->command," \n"),FG_PROC->FG_PID);
        free(FG_PROC->command);
    }
    fflush(stdout);
}