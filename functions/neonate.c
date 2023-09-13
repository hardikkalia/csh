#include "../headers.h"

void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

/**
 * Enable row mode for the terminal
 * The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing.
 * Terminal attributes can be read into a termios struct by tcgetattr().
 * After modifying them, you can then apply them to the terminal using tcsetattr().
 * The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.
 * The c_lflag field is for “local flags”
*/
void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

/**
 * stdout and stdin are buffered we disable buffering on that
 * After entering in raw mode we read characters one by one
 * Up arrow keys and down arrow keys are represented by 3 byte escape codes
 * starting with ascii number 27 i.e. ESC key
 * This way we interpret arrow keys
 * Tabs are usually handled by the term, but here we are simulating tabs for the sake of simplicity
 * Backspace move the cursor one control character to the left
 * @return
*/

void neonate(char* command){
    char* temp=malloc(strlen(command)+1);
    strcpy(temp,command);
    char* arg=strtok(temp," \n");
    arg=strtok(NULL," \n");
    if(arg==NULL){
        fprintf(stderr,RED "ERROR: " RESET"No arguments entered");
    }
    if(arg[0]!='-'){
        fprintf(stderr,RED "ERROR: "RESET"No flags entered");
        return;
    }
    if(strlen(arg)==1 || arg[1]!='n' || strlen(arg)>2){
        fprintf(stderr,RED "ERROR: " RESET "Invalid flags");
        return;
    }
    arg=strtok(NULL," \n");
    int time=convert_str_to_int(arg);
    pid_t pid=fork();
    if(pid==0){
        while(1){
            FILE* fptr=fopen("/proc/loadavg","r");
            if(fptr==NULL){
                perror("fopen");
                continue;
            }
            char* buf;
            size_t size;
            getline(&buf,&size,fptr);
            char* info=strtok(buf," \n");
            for(int i=0;i<4;i++){
                info=strtok(NULL," \n");
            }
            printf("%s\n",info);
            sleep(time);
        }
    }
    else{
        char c;
        setbuf(stdout,NULL);
        enableRawMode();
        while(read(STDIN_FILENO,&c,1)==1){
            if(c=='x'){
                kill(pid, SIGTERM);
                break;
            }
        }
        disableRawMode();
    }
    
}