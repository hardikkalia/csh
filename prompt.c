#include "headers.h"

void prompt() {
    // Do not hardcode the prmopt
    uid_t uid = getuid(); 
    struct passwd *pw = getpwuid(uid);
    char*username=pw->pw_name;
    char systemname[128];
    assert(gethostname(systemname,128)!=-1);
    char cur_dir[2048];
    getcwd(cur_dir,2048);
    char dir[2048];
    if(strncmp(cur_dir,HOME_DIR,strlen(HOME_DIR))==0){
        if(strlen(cur_dir)==strlen(HOME_DIR))
            strcpy(dir,"~");
        else{
            strcpy(dir,"~");
            strcat(dir,cur_dir+strlen(HOME_DIR));
        }
    }
    else{
        strcpy(dir,cur_dir);
    }
    if(BG_QUE->Front!=NULL){
        BGQueElems* temp=BG_QUE->Rear;
        while(1){
            BGQueElems* E=BGDeque();
            int status;
            int result=waitpid(E->pid,&status,WNOHANG);
            if(result==-1)
                perror("waitpid");
            else if (result==0){
                BGEnque(E->command,E->pid);
            }
            else{
                printf("%s has ended normally(%d)\n",E->command,E->pid);
            }
            if(temp==E)
                break;
            free(E);
        }
    }
    printf(CYAN "<%s@%s:%s>" RESET,username,systemname,dir);
}
