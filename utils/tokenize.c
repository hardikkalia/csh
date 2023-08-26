#include "../headers.h"

command_que InitCQ(){
    command_que Q=malloc(sizeof(stcommand_que));
    Q->Front=NULL;
    Q->Rear=NULL;
    return Q;
}

QueElems* Create_Elem(char* str){
    QueElems* Elem=malloc(sizeof(QueElems));
    Elem->Next=NULL;
    Elem->Command=malloc(sizeof(stcommand));
    Elem->Command->type=FG;
    Elem->Command->command_name=malloc(strlen(str)+1);
    strcpy(Elem->Command->command_name,str);
    return Elem;
}

void enque(char* command,command_que Q,enum ptype type){
    QueElems* Elem=Create_Elem(command);
    if(type==BG)
        Elem->Command->type=BG;
    if(Q->Front==NULL){
        Q->Front=Elem;
        Q->Rear=Elem;
    }
    else{
        Q->Rear->Next=Elem;
        Q->Rear=Elem;
    }
}

commnd deque(command_que Q){
    if(Q->Front==Q->Rear){
        commnd c=Q->Front->Command;
        Q->Front=NULL;
        Q->Rear=NULL;
        return c;
    }
    else{
        commnd c=Q->Front->Command;
        Q->Front=Q->Front->Next;
        return c;
    }
}

int IsEmpty(command_que Q){
    return (Q->Front==NULL);
}

command_que create_command_que(char* str){
    command_que Q=InitCQ();
    char* saveptr;
    char* command=strtok_r(str,";\n",&saveptr);
    while(command!=NULL){
        Enque_handler(command,Q);
        command=strtok_r(NULL,";\n",&saveptr);
    
    }
    return Q;
}

void Enque_handler(char* command,command_que Q){
    char temp[strlen(command)];
    strcpy(temp,command);
    char* arg=strtok(temp,"&\n");
    if(strcmp(command,arg)==0){
        enque(command,Q,FG);
    }
    else{
        strcpy(temp,command);
        arg=strtok(temp,"&");
        while(arg!=NULL){
            enque(arg,Q,BG);
            arg=strtok(NULL,"&");
        }
        int last;
        for(int i=strlen(command)-1;i>=0;i--){
            if(command[i]==' ')
                continue;
            if(command[i]!='&')
                Q->Rear->Command->type=FG;
            break;
        }
    }
}




