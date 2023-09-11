#include "../headers.h"

    int check_exec(char* fname){
        struct stat st;
        if (stat(fname, &st) == 0) {
        if (S_ISREG(st.st_mode) && ((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH))) {
            return 1;
        }
         }
        return 0;
    }

    void print_long(char* fname,struct stat* st,char* relative,redirect io_info){
        struct passwd *pwd;
        struct group *grp;
        char date_string[80];

        pwd = getpwuid(st->st_uid);
        grp = getgrgid(st->st_gid);

        strftime(date_string, sizeof(date_string), "%b %d %H:%M", localtime(&st->st_mtime));
        snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,
            "%c%c%c%c%c%c%c%c%c%c %2ld %s %s %6ld %s ",
            (S_ISDIR(st->st_mode)) ? 'd' : '-',
            (st->st_mode & S_IRUSR) ? 'r' : '-',
            (st->st_mode & S_IWUSR) ? 'w' : '-',
            (st->st_mode & S_IXUSR) ? 'x' : '-',
            (st->st_mode & S_IRGRP) ? 'r' : '-',
            (st->st_mode & S_IWGRP) ? 'w' : '-',
            (st->st_mode & S_IXGRP) ? 'x' : '-',
            (st->st_mode & S_IROTH) ? 'r' : '-',
            (st->st_mode & S_IWOTH) ? 'w' : '-',
            (st->st_mode & S_IXOTH) ? 'x' : '-',
            (long)st->st_nlink, pwd->pw_name, grp->gr_name,
            (long)st->st_size, date_string);
            snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,"%s%s%s\n", S_ISDIR(st->st_mode) ? BLUE : (check_exec(fname) ? GREEN : RESET), relative, RESET);
    }


    void peek(char* str,redirect io_info){
            int a_flag=0;
            int l_flag=0;
            char* temp=malloc(sizeof(char)*(strlen(str)+1));
            strcpy(temp,str);
             char* arg=strtok(str," \n");
            arg=strtok(NULL," \n");
    while(1){
        if(arg==NULL || arg[0]!='-'){
            break;
        }
        for(int i=1;i<strlen(arg);i++){
        if(arg[i]=='a')
            a_flag=1;
        else if(arg[i]=='l')
            l_flag=1;
        else{
            fprintf(stderr,RED "ERROR: "RESET"invalid flags\n");
            return;
        }
    }
        arg=strtok(NULL," \n");
    }
            // char* args=strtok(temp," \n");
            char path[PATH_SIZE];
            if(io_info->pipein==1){
                strcpy(path,PRINT_BUFFER);
                path[strlen(path)-1]='\0';
                PRINT_BUFFER[0]='\0';
            }
            // args=strtok(NULL," \n");
            else if(arg==NULL || arg[0]=='>'){
                strcpy(path,".");
            }
            else{
                strcpy(path,arg);
            }
            if(strcmp(path,"~")==0){
                strcpy(path,HOME_DIR);
            }
            if(strcmp(path,"-")==0){
                strcpy(path,WARP_PREV);
            }
            char full_path[NAME_SIZE];
           struct dirent **namelist;
           int n;
           n = scandir(path, &namelist, NULL,alphasort);
           if (n == -1) {
               fprintf(stderr,RED "ERROR: "RESET "No such file or directory\n");
               return;
           }
           struct stat st;
           if(l_flag!=0){
                stat(path,&st);
                snprintf(PRINT_BUFFER,PRINT_BUF_SIZE,"Total Block Size: %d\n",st.st_blksize);
           }
           for(int i=0;i<n;i++) {
            if(!a_flag && namelist[i]->d_name[0]=='.')
                continue;
            if(!io_info->wrfile && !io_info->apfile){
            if(check_exec(namelist[i]->d_name))
                snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,GREEN);
            else if(namelist[i]->d_type== DT_DIR)
                snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,BLUE);
            else
                snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,RESET);
            }
            if(l_flag==0){
                // if(check_exec(namelist[i]->d_name)){
                //     snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,GREEN "%s\n" RESET,namelist[i]->d_name);
                //     // printf("%s",PRINT_BUFFER);
                //     // print(io_info);
                // }
                // else if(namelist[i]->d_type== DT_DIR){
                //     snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,BLUE "%s\n" RESET, namelist[i]->d_name);
                //     // printf("%s",PRINT_BUFFER);
                //     // print(io_info);
                // }
                // else{
                    snprintf(PRINT_BUFFER+strlen(PRINT_BUFFER),PRINT_BUF_SIZE,"%s\n",namelist[i]->d_name);
                //     printf("%d\n%s",i,PRINT_BUFFER);
                //     print(io_info);
                // }
                free(namelist[i]);
            }
            else{
                strcpy(full_path,path);
                strcat(full_path,"/");
                strcat(full_path,namelist[i]->d_name);
                if (stat(full_path, &st) == 0) {   
                    print_long(full_path, &st,namelist[i]->d_name,io_info);
                }
                free(namelist[i]);
            }
            printf(RESET);
           }
           print(io_info);
           free(namelist);
           free(temp);
    }