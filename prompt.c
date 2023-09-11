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
    BG_QUE->print();
    printf(CYAN "<%s@%s:%s>" RESET,username,systemname,dir);
}
