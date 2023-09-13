#include "../headers.h"
void ping(char* command){
    char* temp=malloc(strlen(command));
    strcpy(temp,command);
    char* arg=strtok(command," \n");
    arg=strtok(NULL," \n");
    if(arg==NULL){
        fprintf(stderr,RED"ERROR: "RESET"Enter a process id\n");
        free(temp);
        return;
    }
    pid_t pid=convert_str_to_int(arg);
    arg=strtok(NULL," \n");
    if(arg==NULL){
        fprintf(stderr,RED "ERROR: " RESET "Enter a signal no\n");
        free(temp);
        return;
    }
    int signal=convert_str_to_int(arg);
    signal%=32;
    free(temp);
    BGQueElems* iter=BG_QUE->Front;
    int found=0;
    while(iter!=NULL){
        if(iter->pid==pid){
            found=1;
            break;
        }
        iter=iter->Next;
    }
    if(found==0){
        fprintf(stderr,RED"ERROR: " RESET "Process does not exist\n");
        return;
    }
    int id=fork();
    if(id==0){
        if(kill(pid,signal)<0){
            perror("ping");
            return;
        }
        printf("Sent signal %d to process with pid %d\n",signal,pid);
        exit(0);
    }
    else{
            waitpid(id,NULL,0);
            int result=waitpid(pid,NULL,WNOHANG);
            if(result>0){
                BG_QUE->remove(pid);
         }
    }
}