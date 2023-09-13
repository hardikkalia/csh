#include "../headers.h"
void fg(char* command){
    char* temp=malloc(strlen(command)+1);
    strcpy(temp,command);
    char* arg=strtok(command," \n");
    arg=strtok(NULL," \n");
    if(arg==NULL){
        fprintf(stderr,RED"ERROR: " RESET "Enter a process id\n");
        return;
    }
    pid_t pid=convert_str_to_int(arg);
    pid_t pgid=getpgid(pid);
    BGQueElems* iter=BG_QUE->Front;
    int found=BG_QUE->remove(pid);
    if(found==0){
        fprintf(stderr,RED"ERROR: " RESET"No such background process\n");
    }
    int status;

    struct termios settings;
    if(tcgetattr(STDIN_FILENO, &settings)==1){
        perror("tcgetattr");
        return;
    }
    if(tcsetpgrp(STDIN_FILENO, pgid)==-1){
        perror("tcsetpgrp");
        return;
    }
    kill(pid, SIGCONT);
    waitpid(pid, &status, WUNTRACED);
    
    if(tcsetpgrp(STDIN_FILENO, getpgrp())==-1){
        perror("tcsetpgrp");
        return;
    }
    if(tcsetattr(STDIN_FILENO, TCSADRAIN, &settings)==-1){
        perror("tcsetattr");
        return;
    }
   
    
}