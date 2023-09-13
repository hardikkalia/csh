#ifndef GLOBAL_H
#define GLOBAL_H
#include "./functions/pastevents.h"
#include "./functions/bg.h"
extern pid_t* SHELL_PID;
extern char *HOME_DIR;
extern char* WARP_PREV;
extern Events EVENT_QUE;
extern char* historyFile;
extern BGQue BG_QUE;
extern char* PRINT_BUFFER;
extern struct sttime{
    char* command;
    int* time;
}* TIME;

extern struct fg{
    char* command;
    pid_t FG_PID;
    pid_t FG_PPID;
}* FG_PROC;
#endif