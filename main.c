#include "headers.h"
char* HOME_DIR=NULL;
char* WARP_PREV=NULL;
Events EVENT_QUE=NULL;
char* historyFile=NULL;
BGQue BG_QUE;
int main()
{
        // HOME_DIR=malloc(sizeof(char)*NAME_SIZE);
        // WARP_PREV=malloc(sizeof(char)*PATH_SIZE);
        // WARP_PREV[0]='\0';
        // getcwd(HOME_DIR,128);
        // EVENT_QUE=InitEventsQ();
        // Create_history();
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
