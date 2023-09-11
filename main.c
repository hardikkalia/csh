#include "headers.h"
char* PRINT_BUFFER=NULL;
char* HOME_DIR=NULL;
char* WARP_PREV=NULL;
Events EVENT_QUE=NULL;
char* historyFile=NULL;
BGQue BG_QUE=NULL;
int main()
{
        initialize_shell();
    // Keep accepting commands
    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt();
        char input[4096];
        fgets(input, 4096, stdin);
        sequential(input);
    }
}
