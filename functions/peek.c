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

    void print_long(char* fname,struct stat* st,char* relative){
        struct passwd *pwd;
        struct group *grp;
        char date_string[80];

        pwd = getpwuid(st->st_uid);
        grp = getgrgid(st->st_gid);

        strftime(date_string, sizeof(date_string), "%b %d %H:%M", localtime(&st->st_mtime));
        printf("%c%c%c%c%c%c%c%c%c%c %2ld %s %s %6ld %s ",
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
            printf("%s%s%s\n", S_ISDIR(st->st_mode) ? BLUE : (check_exec(fname) ? GREEN : RESET), relative, RESET);
    }


    void peek(char* str){
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
            // args=strtok(NULL," \n");
            if(arg==NULL){
                strcpy(path,".");
            }
            else{
                strcpy(path,arg);
            }
            // else{
            //      strcpy(temp,str);
            //      args=strtok(temp," \n");
            //      args=strtok(NULL," \n");
            //     if(args[0]!='-'){
            //         strcpy(path,args);
            //     }
            //     else{
            //         if(args[1]=='l'){
            //             l_flag=1;
            //         if(args[2]=='a')
            //                 a_flag=1;
            //         }
            //         else if(args[1]=='a'){
            //             a_flag=1;
            //             if(args[2]=='l')
            //                 l_flag=1;
            //         }
            //         else{
            //             fprintf(stderr,RED "ERROR: " RESET "'%s' No such file or directory exists\n",args);
            //             return;
            //         }
            //         args=strtok(NULL," \n");
            //         if(args==NULL){
            //             strcpy(path,".");
            //         }
            //         else if(args[0]!='-'){
            //             strcpy(path,args);
            //         }
            //         else{
            //             if(args[1]=='l')
            //                 l_flag=1;
            //             else
            //                 a_flag=1;
            //             args=strtok(NULL," \n");
            //             if(args==NULL)
            //                 strcpy(path,".");
            //             else
            //                 strcpy(path,args);
            //         }
            //     }
            //  }
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
                printf("Total Block Size: %d\n",st.st_blksize);
           }
           
           for(int i=0;i<n;i++) {
            if(!a_flag && namelist[i]->d_name[0]=='.')
                continue;
            if(l_flag==0){
                if(check_exec(namelist[i]->d_name))
                    printf(GREEN "%s\n" RESET,namelist[i]->d_name);
                else if(namelist[i]->d_type== DT_DIR)
                printf(BLUE "%s\n" RESET, namelist[i]->d_name);
                else   
                    printf("%s\n",namelist[i]->d_name);
                free(namelist[i]);
            }
            else{
                strcpy(full_path,path);
                strcat(full_path,"/");
                strcat(full_path,namelist[i]->d_name);
                if (stat(full_path, &st) == 0) {   
                    print_long(full_path, &st,namelist[i]->d_name);
                }
                free(namelist[i]);
            }
           }
           free(namelist);
           free(temp);
    }