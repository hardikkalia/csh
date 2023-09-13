#include "../headers.h"
void print(redirect io_info){
      if(io_info->pipeout==1)
          return;
      if(io_info->wrfile==NULL && io_info->apfile==NULL){
            printf("%s",PRINT_BUFFER);
        }
        else if(io_info->wrfile!=NULL){
             char* path=malloc(strlen(HOME_DIR)+2+strlen(io_info->wrfile));

            sprintf(path,"%s/%s",HOME_DIR,io_info->wrfile);
            int fd=open(path,O_CREAT | O_TRUNC | O_WRONLY ,0644);
                if(fd==-1){
                fprintf(stderr,RED "ERROR: "RESET"Can't open file %s\n",path);
                return;
            }
            int wr=write(fd,PRINT_BUFFER,strlen(PRINT_BUFFER));
            close(fd);
            return;
        }
        else{
            char* path=malloc(strlen(HOME_DIR)+2+strlen(io_info->apfile));

            sprintf(path,"%s/%s",HOME_DIR,io_info->apfile);
            int fd=open(path,O_CREAT | O_APPEND | O_WRONLY ,0644);
                if(fd==-1){
                fprintf(stderr,RED "ERROR: "RESET"Can't open file %s\n",path);
                return;
            }
            int wr=write(fd,PRINT_BUFFER,strlen(PRINT_BUFFER));
            close(fd);
            return;
        }
}




redirect getredirect(char* command){
     char* temp=malloc(strlen(command)+1);
     strcpy(temp,command);
    redirect R=malloc(sizeof(stredirect));
    R->rdfile=NULL;
    R->wrfile=NULL;
    R->apfile=NULL;
    R->pipein=0;
    R->pipeout=0;
    int rd=0,wr=0,ap=0;
   for(int i=0;i<strlen(command);i++){
        if(command[i]=='<'){
          rd=1;
          break;
        }
        else if(command[i]=='>' && i+1<strlen(command) && command[i+1]=='>'){
          ap=1;
          break;
        }
        else if(command[i]=='>'){
          wr=1;
          break;
        }
   }
   if(wr==1){
     char* arg=strtok(temp,">");
     arg=strtok(NULL," \n");
     R->wrfile=malloc(strlen(arg));
      strcpy(R->wrfile,arg);
   }
   else if(rd==1){
    char* arg=strtok(temp,"<");
    arg=strtok(NULL," \n");
    R->rdfile=malloc(strlen(arg));
    strcpy(R->rdfile,arg);
   }
   else if(ap==1){
    char* arg=strtok(temp,">");
    arg=strtok(NULL," >\n");
    R->apfile=malloc(strlen(arg));
    strcpy(R->apfile,arg);
   }
   free(temp);
   return R;
}

