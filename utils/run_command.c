#include "../headers.h"

void sequential(char* str){
    command_que list=create_command_que(str);
    commnd command;
    while(!IsEmpty(list)){
        command=deque(list);
        // int id=fork();
        // if(id==0){
            // char* arg[]={command->command_name,NULL};
            run_command(command->command_name,command->type);
        //     exit(0);
        // }
        // else{
        //     if(command->type==FG)
        //         waitpid(id,NULL,0);
        //      }
        }
}


void run_command(char* command,enum ptype type){
    Write_History();
    char arg[strlen(command)];
    strcpy(arg,command);
    char* function=strtok(arg," \n");
    if(strcmp("pastevents",function)!=0 && type !=BG)
        AddEvent(command);
    if(strcmp("warp",function)==0)
       warp(command);
    else if(strcmp("peek",function)==0)
        peek(command);
    else if(strcmp("pastevents",function)==0)
        pastevents_handler(command);
    else if(strcmp("proclore",function)==0)
        proclore(command);
    else if(strcmp("seek",function)==0)
        seek(command);
    else{
         run_bash(command,type);
    }
}
