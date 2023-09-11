#include "../headers.h"
int search(char* path,char* name,int d_flag,int e_flag,int f_flag,int depth){
    struct dirent* entry;
    struct stat st;
    DIR* dp;
    dp=opendir(path);
    if(dp==NULL){
        fprintf(stderr,RED "Error: " RESET"Invalid search path\n");
        return -1;
    }
    char print_path[PATH_SIZE];
    char temp[PATH_SIZE];
    char* check=malloc(PATH_SIZE);
    int num=0,num_dir=0,num_fil=0;
    while(1){
        entry=readdir(dp);
        if(entry==NULL)
            break;
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0)
            continue;
        snprintf(print_path,PATH_SIZE,"%s/%s",path,entry->d_name);
        lstat(print_path,&st);
        if(S_ISDIR(st.st_mode)){
            
            if(strcmp(entry->d_name,name)==0 && !f_flag){
                snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,BLUE"%s\n"RESET,print_path);
                strcpy(temp,print_path);
                num++;num_dir++;
            }  
         num+=search(print_path,name,d_flag,e_flag,f_flag,depth+1);
        }
        else if(S_ISREG(st.st_mode)){
            if(d_flag)
                continue;
            strcpy(check,entry->d_name);
            check=strtok(check,".");
            if(strcmp(check,name)==0){
                snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,GREEN"%s\n"RESET,print_path);
                strcpy(temp,print_path);
                num++;num_fil++;
            }  
        }
    }
    if(num==1 && e_flag && depth==0){
        if(num_dir==1){
            // char* command=malloc(sizeof(char)*(strlen(temp)+6));
            // snprintf(command,PATH_SIZE,"warp %s",temp);
            // warp(command);
            if(chdir(temp)==-1)
                printf("Missing permissions for task!\n");
        }
        else if(num_fil==1){
            FILE* fptr=fopen(temp,"r");
            if(fptr==NULL)
                printf("Missing permissions for task!\n");
            else{
                int c;
                while((c=fgetc(fptr))!=EOF)
                    putchar(c);
            }
            snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,"\n");
            fclose(fptr);
        }
    }
    // free(check);
    return num;
}
void seek(char* command,redirect io_info){
    char* arg=strtok(command," \n");
    arg=strtok(NULL," \n");

    int d_flag=0,f_flag=0,e_flag=0;
    while(1){
        if(arg==NULL || arg[0]!='-'){
            break;
        }
        for(int i=1;i<strlen(arg);i++){
        if(arg[i]=='d')
            d_flag=1;
        else if(arg[i]=='f')
            f_flag=1;
        else if(arg[i]=='e')
            e_flag=1;
        else{
            fprintf(stderr,RED "ERROR: "RESET"invalid flags\n");
            return;
        }
    }
        arg=strtok(NULL," \n");
    }
    if(arg==NULL){
        fprintf(stderr,RED"ERROR: " RESET"No name specified\n");
        return;
    }
    if(d_flag==1 && f_flag==1){
        fprintf(stderr,RED"Invalid Flags!\n"RESET);
        return;
    }
    char name[strlen(arg)+1];
    strcpy(name,arg);
    arg=strtok(NULL," \n");
    char path[PATH_SIZE];
    if(io_info ->pipein==1){
        strcpy(path,PRINT_BUFFER);
        path[strlen(path)-1]='\0';
        PRINT_BUFFER[0]='\0';
    }
    else if(arg==NULL || arg[0]=='>'){
        strcpy(path,".");
    }
    else if(strcmp(arg,"~")==0){
        strcpy(path,HOME_DIR);
    }
    else{
        strcpy(path,arg);
    }
    int num=search(path,name,d_flag,e_flag,f_flag,0);
    if(num==0){
        snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,"No match found!\n");
    }
    print(io_info);
}