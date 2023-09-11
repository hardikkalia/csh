#include "../headers.h"

Events InitEventsQ(){
    Events Q=malloc(sizeof(stEvents));
    Q->Front=NULL;
    Q->Rear=NULL;
    Q->num_events=0;
    return Q;
}

Event Create_Event(char* command){
        Event E=malloc(sizeof(PEQueElems));
        E->command=malloc(sizeof(char)*(strlen(command)+1));
        strcpy(E->command,command);
        E->Next=NULL;
        return E;
}

void AddEvent(char* command){
    command=strtok(command,"\n");
    if(EVENT_QUE->Rear!=NULL && strcmp(command,EVENT_QUE->Rear->command)==0)
        return;
    Event E=Create_Event(command);
    if(EVENT_QUE->num_events<15){
        EVENT_QUE->num_events++;
        if(EVENT_QUE->Front==NULL){
            EVENT_QUE->Front=E;
            EVENT_QUE->Rear=E;
        }
        else{
            EVENT_QUE->Rear->Next=E;
            EVENT_QUE->Rear=E;
        }
    }
    else{
        Event temp=EVENT_QUE->Front;
        EVENT_QUE->Front=temp->Next;
        free(temp->command);
        free(temp);
        EVENT_QUE->Rear->Next=E;
        EVENT_QUE->Rear=E;
    }
}

void pastevents_handler(char* command,redirect io_info){
    char* temp=malloc(sizeof(char)*(strlen(command)+1));
    strcpy(temp,command);
    char* arg=strtok(temp," \n");
    arg=strtok(NULL," \n");
    if(arg==NULL || arg[0]=='>'){
        free(temp);
        pastevents();
        print(io_info);
    }
    else if(strncmp(arg,"purge",5)==0){
        free(temp);
        pastevents_purge();
    }
    else if(strncmp(arg,"execute",7)==0){
        arg=strtok(NULL," \n");
        if(arg==NULL){
            fprintf(stderr,RED "ERROR: Enter a Valid command number\n" RESET);
            return;
        }
            pastevents_execute(arg);
    }
    else{
        fprintf(stderr,RED "ERROR: " RESET"Invalid argument for command 'pastevents'-%s\n",arg);
    }

}

void Create_history(){
    historyFile=malloc(strlen(HOME_DIR)+strlen("/history.txt")+1);
    struct stat st;
    sprintf(historyFile,"%s/history.txt",HOME_DIR);
    // if(stat(historyFile,&st)==0)
    //     return
    int file=open(historyFile,O_CREAT | O_RDONLY,0600);
    if(file==-1){ 
        fprintf(stderr,RED"Error Getting History\n"RESET);
        return;
    }
    close(file);
    FILE* fptr=fopen(historyFile,"r");
    char* command;
    size_t n=0;
    while(getline(&command,&n,fptr)!=-1){
        command=strtok(command,"\n");
        AddEvent(command);
    }  
}

void Write_History(){
    int fd=open(historyFile,O_TRUNC | O_WRONLY,0600);
    Event E=EVENT_QUE->Front;
    while(E!=NULL){
        write(fd,E->command,strlen(E->command));
        write(fd,"\n",1);
        E=E->Next;
    }
    close(fd);
}


void pastevents(){
    Event E=EVENT_QUE->Front;
    if(E==NULL){
        fprintf(stderr,RED"ERROR: "RESET "No pastevents\n");
    }
    while(E!=NULL){
        snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,"%s\n",E->command);
        E=E->Next;
    }
}

void pastevents_purge(){
    int fd=open(historyFile,O_TRUNC);
    close(fd);
    EVENT_QUE->Front=NULL;
    EVENT_QUE->Rear=NULL;

}

void pastevents_execute(char* command_num){
    if(strlen(command_num)>2){
        fprintf(stderr,RED "ERROR: argument outside range\n"RESET);
        return;
    }
    int num;
    if(strlen(command_num)==1)
        num=(int)command_num[0]-'0';
    else
        num=(command_num[0]-'0')*10+ command_num[1]-'0';
    if(num>EVENT_QUE->num_events){
        fprintf(stderr,RED "ERROR: argument outside range\n"RESET);
        return;
    }
        Event E=EVENT_QUE->Front;
        for(int i=0;i<EVENT_QUE->num_events-num;i++){
            E=E->Next;
        }
        redirect io_info=getredirect(E->command);
        run_command(E->command,0,io_info);
    
}