#include "../headers.h"

int comp(const void* a,const void* b){
    BGQueElems** x=(BGQueElems**)a;
    BGQueElems** y=(BGQueElems**)b;
    return (*x)->pid-(*y)->pid;
}

void activities(redirect io_info){
    int num=0;
    BGQueElems* temp=BG_QUE->Front;
    if(temp==NULL){
        printf("No processes\n");
        return;
    }
    while(temp!=NULL){
        temp=temp->Next;
        num++;
    }
    BGQueElems** active=malloc(sizeof(BGQueElems*)*num);
    temp=BG_QUE->Front;
    num=0;
    while(temp!=NULL){
        active[num++]=temp;
        temp=temp->Next;
    }
    qsort(active,num,sizeof(BGQueElems*),comp);
    char* procFile=malloc(sizeof(char)*22);
    char* status=malloc(sizeof(char)*8);
    for(int i=0;i<num;i++){
        pid_t pid=active[i]->pid;
        snprintf(procFile,22,"/proc/%d/stat",pid);
        FILE* fptr=fopen(procFile,"r");
        if(fptr==NULL){
            perror("activities");
            return;
        }
        char* info=NULL;
        size_t size=0;
        if(getline(&info,&size,fptr)==-1){
            perror("getline");
            return;
        }    
        int j;
        char* arg=strtok(info," ");
        for(j=0;j<2;j++){
            arg=strtok(NULL," ");
        }
        if(arg[0]=='T')
            strcpy(status,"Stopped");
        else 
            strcpy(status,"Running");
        printf("%d : %s - %s\n",pid,active[i]->command,status);
    }
    free(active);
    free(procFile);
    free(status);

}