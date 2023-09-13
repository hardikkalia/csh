#ifndef BG_H_
#define BG_H_

void bg(char* command);



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
    int (*remove)(pid_t);
    int (*find)(pid_t);
}stBGQue;

typedef stBGQue* BGQue;
void InitBGQue();
BGQueElems* Create_BGElem(char* command,pid_t pid);
void BGEnque(char* command,pid_t pid);
BGQueElems* BGDeque();
int Remove(pid_t pid);
int Find(pid_t pid);
void printBG();
#endif