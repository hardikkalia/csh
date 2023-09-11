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
                    waitpid(id,NULL,0);
                }
                else if(type==BG){
                    printf("%d\n",id);
                    BG_QUE->Enque(strtok(command," \n"),id);
                }
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
                printf("%s has ended normally(%d)\n",E->command,E->pid);
            }
            if(temp==E)
                break;
            free(E);
        }
}