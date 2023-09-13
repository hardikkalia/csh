#include "../headers.h"

void bg(char* command){
    char* temp=malloc(strlen(command)+1);
    strcpy(temp,command);
    char* arg=strtok(temp," \n");
    arg=strtok(NULL," \n");
    if(arg==NULL){
        fprintf(stderr,RED"ERROR: "RESET "Enter a process id\n");
        return;
    }
    pid_t pid=convert_str_to_int(arg);
    int result=kill(pid,0);
    if(!BG_QUE->find(pid)){
        fprintf(stderr,RED"ERROR: " RESET "No such process in the background");
        return;
    }
    if(kill(pid,SIGCONT)<0){
        perror("bg");
    }
}

void InitBGQue(){
    BG_QUE=malloc(sizeof(stBGQue));
    BG_QUE->Front=NULL;
    BG_QUE->Rear=NULL;
    BG_QUE->Deque=BGDeque;
    BG_QUE->Enque=BGEnque;
    BG_QUE->Create_Elem=Create_BGElem;
    BG_QUE->print=printBG;
    BG_QUE->remove=Remove;
    BG_QUE->find=Find;
}

BGQueElems* Create_BGElem(char* command,pid_t pid){
    BGQueElems* New=malloc(sizeof(BGQueElems));
    New->command=malloc(strlen(command)+1);
    strcpy(New->command,command);
    New->pid=pid;
    New->Next=NULL;
    return New;
}

void BGEnque(char* command,pid_t pid){
    BGQueElems* Elem=BG_QUE->Create_Elem(command,pid);
    if(BG_QUE->Front==NULL){
        BG_QUE->Front=Elem;
        BG_QUE->Rear=Elem;
    }
    else{
        BG_QUE->Rear->Next=Elem;
        BG_QUE->Rear=Elem;
    }

}

BGQueElems* BGDeque(){
    if(BG_QUE->Front==BG_QUE->Rear){
        BGQueElems* c=BG_QUE->Front;
        BG_QUE->Front=NULL;
        BG_QUE->Rear=NULL;
        return c;
    }
    else{
        BGQueElems* c=BG_QUE->Front;
        BG_QUE->Front=BG_QUE->Front->Next;
        return c;
    }
}

void printBG(){
    if(BG_QUE->Front==NULL)
        return;
      BGQueElems* temp=BG_QUE->Rear;
        while(1){
            BGQueElems* E=BG_QUE->Deque();
            int status;
            int result=waitpid(E->pid,&status,WNOHANG);
            if(result==-1)
                perror("waitpid");
            else if (result==0){
                BG_QUE->Enque(E->command,E->pid);
            }
            else{
                if (WIFEXITED(status)) {
                    int exit_status = WEXITSTATUS(status);
                    printf("%s has exited normally with status %d (%d)\n", E->command, exit_status, E->pid);
                } 
                else {
                    printf("%s has exited abnormally (%d)\n", E->command, E->pid);
                }
            }
            if(temp==E)
                break;
            free(E);
        }
}


int Remove(pid_t pid){
    int found=0;
    BGQueElems* iter=BG_QUE->Front;
    if(iter==NULL)
        return 0;
    if(iter->pid==pid){
        BG_QUE->Deque();
        return 1;
    }
    while(iter->Next){
        if(iter->Next->pid==pid){
            found=1;
            BGQueElems* temp=iter->Next;
            iter->Next=iter->Next->Next;
            free(temp);
            return 1;
        }
    }
    return 0;
}

int Find(pid_t pid){
    int found=0;
    BGQueElems* iter=BG_QUE->Front;
    while(iter!=NULL){
        if(iter->pid==pid){
            found=1;
            break;
        }
    }
    return found;
}