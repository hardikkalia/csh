#include "../headers.h"
void warp(char* command,redirect io_info){
    char* temp=malloc(strlen(command)+1);
    strcpy(temp,command);
    char* arg=strtok(temp," \n");
    arg=strtok(NULL," \n");
    char directory[PATH_SIZE];
    if(arg==NULL){
        getcwd(WARP_PREV,2048);
        chdir(HOME_DIR);
        getcwd(directory,2048);
        snprintf(PRINT_BUFFER,PRINT_BUF_SIZE,"%s\n",directory);
        print(io_info);
    }

    while(arg!=NULL){
        if(arg[0]!='~'){
            if(strncmp(arg,"-",1)!=0){
                getcwd(WARP_PREV,2048);
                chdir(arg);
            }
            else{
                    if(strlen(WARP_PREV)==0){
                        fprintf(stderr,RED"ERROR: " RESET"OLDPWD not set\n");
                    }
                    else{
                        char* temp=malloc(sizeof(char)*strlen(WARP_PREV));
                        strcpy(temp,WARP_PREV);
                        getcwd(WARP_PREV,2048);
                        chdir(temp);
                        free(temp);
                }
            }
        }
       
        else{
            char* home=HOME_DIR;
            strcat(home,arg+1);
            getcwd(WARP_PREV,2048);
            chdir(home);
        }
        getcwd(directory,2048);
        snprintf(PRINT_BUFFER,PRINT_BUF_SIZE,"%s\n",directory);
        print(io_info);
        return;
        arg=strtok(NULL," \n");
    }
}
