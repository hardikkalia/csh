#ifndef BASH_H_
#define BASH_H_
void run_bash(char* command,enum ptype type,redirect io_info);
typedef struct BGQueElems{
    char* command;
    pid_t pid;
    struct BGQueElems* Next;
}BGQueElems;

typedef struct stBGQue{
    BGQueElems* Front;
    BGQueElems* Rear;
    BGQueElems* (*Create_Elem)(char*,pid_t);
    void (*Enque)(char*,pid_t);
    BGQueElems* (*Deque)();
    void (*print)();
}stBGQue;

typedef stBGQue* BGQue;
void InitBGQue();
BGQueElems* Create_BGElem(char* command,pid_t pid);
void BGEnque(char* command,pid_t pid);
BGQueElems* BGDeque();

void printBG();
#endif