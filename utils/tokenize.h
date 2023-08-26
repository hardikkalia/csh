#ifndef __TOKENIZE_H
#define __TOKENIZE_H


enum ptype{FG,BG};
typedef struct stcommand{
    char* command_name;
    enum ptype type;
}stcommand;

typedef stcommand* commnd;
typedef struct QueElems{
    commnd Command;
    struct QueElems* Next;
}QueElems;

typedef struct stcommand_que{
     QueElems* Front;
     QueElems* Rear;
}stcommand_que;

typedef stcommand_que* command_que;

command_que InitCQ();
QueElems* Create_Elem(char* str);
void enque(char* command,command_que Q,enum ptype type);
commnd deque(command_que Q);
int IsEmpty(command_que Q);
command_que create_command_que(char* str);
void Enque_handler(char* command,command_que Q);
#endif
