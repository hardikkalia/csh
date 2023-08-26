#include "../headers.h"
void run_bash(char* command,enum ptype type){
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
                    BGEnque(strtok(command," \n"),id);
                }
        }
}



BGQue InitBGQue(){
    BGQue Q=malloc(sizeof(BGQueElems));
    Q->Front=NULL;
    Q->Rear=NULL;
    return Q;
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
   
    BGQueElems* Elem=Create_BGElem(command,pid);
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

