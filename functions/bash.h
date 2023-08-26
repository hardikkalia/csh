#ifndef BASH_H_
#define BASH_H_
void run_bash(char* command,enum ptype type);
typedef struct BGQueElems{
    char* command;
    pid_t pid;
    struct BGQueElems* Next;
}BGQueElems;

typedef struct stBGQue{
    BGQueElems* Front;
    BGQueElems* Rear;
}stBGQue;

typedef stBGQue* BGQue;
BGQue InitBGQue();
BGQueElems* Create_BGElem(char* command,pid_t pid);
void BGEnque(char* command,pid_t pid);
BGQueElems* BGDeque();
#endif