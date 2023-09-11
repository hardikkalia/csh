#ifndef IOHANDLER_H_
#define IOHANDLER_H_
typedef struct stredirect{
    char* rdfile;
    char* wrfile;
    char* apfile;
    int pipein;
    int pipeout;
}stredirect;
typedef stredirect* redirect;
redirect getredirect(char* command);
void print(redirect io_info);
#endif