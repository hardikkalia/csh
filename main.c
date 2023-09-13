#include "headers.h"
char* PRINT_BUFFER=NULL;
char* HOME_DIR=NULL;
char* WARP_PREV=NULL;
Events EVENT_QUE=NULL;
char* historyFile=NULL;
BGQue BG_QUE=NULL;
struct sttime* TIME=NULL;
pid_t *SHELL_PID=NULL;
struct fg* FG_PROC=NULL;
int main()
{  
 
    initialize_shell();
    size_t size=4096;
    char* input=malloc(sizeof(int)*size);
    // Keep accepting commands
    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt();
        
        // fgets(input, 4096, stdin);
        if(getline(&input,&size,stdin)==EOF)
            break;
        sequential(input);
    }
    free(input);
    input=NULL;
    terminate_shell();
}
