#include "../headers.h"
void iMan(char* command){
    char* temp=malloc(strlen(command)+1);
    strcpy(temp,command);
    char* arg=strtok(temp," \n");
    arg=strtok(NULL," \n");
    if(arg==NULL){
        fprintf(stderr,RED "ERROR: "RESET"No argument found for iMan");
        return;
    }
    char* hostname=malloc(strlen("www.man.he.net")+1);
    sprintf(hostname,"www.man.he.net");

    struct addrinfo hints;
    struct addrinfo *result,*rp;
    int status,sfd;

    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;

    status=getaddrinfo(hostname,"http",&hints,&result);
    if(status!=0){
        perror("getaddrinfo");
        return;
    }
    for(rp=result;rp!=NULL;rp=rp->ai_next){
        sfd=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
        if(sfd==-1)
            continue;
        if(connect(sfd,rp->ai_addr,rp->ai_addrlen)==0)
            break;
        close(sfd);
    }
    freeaddrinfo(result);
    if(rp==NULL){
        fprintf(stderr,RED"ERROR: "RESET"No such command");
        return;
    }
    char url[1024];
    
    sprintf(url,"GET /?topic=%s&section=all HTTP/1.1\r\nHost: %s\r\nUser-Agent: iMan.c\r\n\r\n",arg,hostname);
    if(send(sfd,url,strlen(url),0)<0){
        perror("send");
        close(sfd);
        return;
    }
    int nread;
    int i=0;
    while(1){
        nread=recvfrom(sfd,PRINT_BUFFER,PRINT_BUF_SIZE-1,0,0,0);
        if(nread<=0)
            break;
        PRINT_BUFFER[PRINT_BUF_SIZE]='\0';
          char *start = strstr(PRINT_BUFFER, "NAME\n");
        if (start) {
        char *end = strstr(start, "AUTHOR\n");
        if (end) {
            *end = '\0';
        } 
        memmove(PRINT_BUFFER,start, strlen(start) + 1);
        printf("%s",PRINT_BUFFER);
        }
    }
    if(nread==-1)
        perror("recv");
    close(sfd);

}
