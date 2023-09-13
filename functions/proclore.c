#include "../headers.h"
#include<signal.h>
int convert_str_to_int(char* str){
    int x=0;
    int i=0;
    while(str[i]!='\0'){
        if(str[i]>'9' || str[i]<'0'){
            return -1;
        }
        x=10*x+str[i]-'0';
        i++;
    }
    return x;
}

void proclore(char* command,redirect io_info){
    char* arg=strtok(command," /n");
    arg=strtok(NULL," \n");
    pid_t pid;
    
    if(arg==NULL || arg[0]=='>' || arg[0]=='<')
        pid=getpid();
    else
        pid=convert_str_to_int(arg);
    if(pid==-1){
        fprintf(stderr,RED"ERROR: "RESET "Invalid argument for function proclore\n");
        return;
    }
    char* procFile=malloc(sizeof(char)*22);
    snprintf(procFile,22,"/proc/%d/stat",pid);
    FILE* fptr=fopen(procFile,"r");
    if(fptr==NULL){
        fprintf(stderr,RED"ERROR: " RESET "Process does not exist\n");
        return;
    }
    char* info=NULL;
    size_t size=0;
    if(getline(&info,&size,fptr)==-1){
        perror("proclore");
        return;
    }    
    int i;
    arg=strtok(info," ");
    char** data=malloc(sizeof(char*)*23);
    for(i=0;i<23;i++){
        data[i]=malloc(strlen(arg)+1);
        strcpy(data[i],arg);
        arg=strtok(NULL," ");
    }
    snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,"pid : %d\n",pid);
    snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,"process Status : %s",data[2]);
    if(strcmp(data[4],data[7])==0)
        snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,"+\n");
    else
        snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,"\n");
    snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,"Process Group : %d\n",getpgid(pid));
    snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,"Virtual Memory : %s\n",data[22]);
    fclose(fptr);
    char* exeFile=malloc(22);
    snprintf(exeFile,22,"/proc/%d/exe",pid);
    char exePath[PATH_SIZE];
    int read=readlink(exeFile,exePath,PATH_SIZE);
    if(read==-1){
        perror("readlink");
        return;
    }
    exePath[read]='\0';
    snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,"Executable Path : %s\n",exePath);
    print(io_info);
}