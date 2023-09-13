#include "../headers.h"

void sequential(char* str){
    command_que list=create_command_que(str);
    commnd command;
    while(!IsEmpty(list)){
        command=deque(list);
        char* temp=malloc(strlen(command->command_name)+1);
        strcpy(temp,command->command_name);
        char* rest=temp;

        char* arg=strtok_r(rest,"|",&rest);
        if(!isCommand(arg) || strcmp(arg,command->command_name)==0){
            redirect io_info=getredirect(command->command_name);
            run_command(command->command_name,command->type,io_info);
        }
        else{
            redirect io_info=getredirect(arg);
            io_info->pipeout=1;
            run_command(arg,FG,io_info);
            arg=strtok_r(rest,"|",&rest);
            while(arg!=NULL){
                io_info=getredirect(arg);
                io_info->pipein=1;
                io_info->pipeout=1;
                run_command(arg,FG,io_info);
                arg=strtok_r(rest,"|\n",&rest);
            }
            io_info->pipeout=0;
            print(io_info);
        }
    }
}


void run_command(char* command,enum ptype type,redirect io_info){
    if(io_info->pipein==0)
        {PRINT_BUFFER[0]='\0';}
    Write_History();
    char arg[strlen(command)];
    strcpy(arg,command);
    char* function=strtok(arg," \n");
    if(strcmp("pastevents",function)!=0 && type !=BG)
        {AddEvent(command);}
    if(strcmp("warp",function)==0)
       {warp(command,io_info);}
    else if(strcmp("peek",function)==0)
        {peek(command,io_info);}
    else if(strcmp("pastevents",function)==0)
        {pastevents_handler(command,io_info);}
    else if(strcmp("proclore",function)==0)
        {proclore(command,io_info);}
    else if(strcmp("seek",function)==0)
        {seek(command,io_info);}
    else if(strcmp("activities",function)==0)
        {activities(io_info);}
    else if(strcmp("iMan",function)==0)
        {iMan(command,io_info);}
    else if(strcmp("ping",function)==0)
        {ping(command);}
    else if(strcmp("fg",function)==0)
        {fg(command);}
    else if(strcmp("bg",function)==0)
        {bg(command);}
    else if(strcmp("neonate",function)==0)
        {neonate(command);}
    else{
         run_bash(command,type,io_info);
    }
}


int isCommand(char* str){
     if(strcmp("warp",str)==0)
       return 1;
    else if(strcmp("peek",str)==0)
       return 1;
    else if(strcmp("pastevents",str)==0)
        return 1;
    else if(strcmp("proclore",str)==0)
        return 1;
    else if(strcmp("seek",str)==0)
       return 1;
    else if(strcmp("activities",str)==0)
       return 1;
    else if(strcmp("iMan",str)==0)
       return 1;
    else if(strcmp("ping",str)==0)
        return 1;
    else if(strcmp("fg",str)==0)
       return 1;
    else if(strcmp("bg",str)==0)
        return 1;
    else if(strcmp("neonate",str)==0)
       return 1;
    else
        return 0;
}