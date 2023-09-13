#include "../headers.h"
void run_bash(char* command,enum ptype type,redirect io_info){

       int id=fork();
            if(id==0){
                char *args[] = { "/bin/bash", "-c", command, NULL};
                if(execvp(args[0], args)==-1){
                    perror(command);
                }
                exit(0);
            }
        else{   
                if(type==FG){
                    FG_PROC->command=malloc(strlen(command)+1);
                    strcpy(FG_PROC->command,command);
                    FG_PROC->FG_PID=id;
                    FG_PROC->FG_PPID=getpid();
                    time_t start_time = time(NULL);

                    int status;
                    
                    do {
                        waitpid(id, &status, WUNTRACED);
                    } while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status));

                    time_t end_time = time(NULL);
                    double exec_time=difftime(end_time,start_time);
                    if(exec_time>2){
                        char* arg=strtok(command," \n");
                        TIME->command=malloc(strlen(arg)+1);
                        strcpy(TIME->command,arg);
                        TIME->time=malloc(sizeof(int));
                        *(TIME->time)=(int)exec_time;
                    }
                    FG_PROC->FG_PID=*(SHELL_PID);
                }
                else if(type==BG){
                    printf("%d\n",id);
                    BG_QUE->Enque(strtok(command," \n"),id);
                }
        }
}


