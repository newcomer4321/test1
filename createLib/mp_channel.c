#include "../include/loadlib.h"

//addReplyErrorFormat

int channelIsOpen(char *channelName)
{
    int res = 1;
    if(access(channelName, F_OK) == -1) {
        res = 0;
    } 

    return res;

}


int createChannel(char *channelName)
{
    int res = 0;
    res = mkfifo(channelName, 0777);
    if(res != 0) {
        addReplyErrorFormat(c, "can't create fifo %s\n",channelName);
    }

    return res;
}

int openChannel(char *channelName, int mode)
{
    int pipefd = open(channelName, mode);
    if(pipefd < 0) {
        addReplyErrorFormat(c, "can't open pipe %s\n",channelName);
    } 
    return pipefd;
}

list *listPush(list *l, void *value)
{
    return listAddNodeTail(l, value);
}


listNode *listPop(list *l)
{

    listNode * node = listFirst(l);

    if (node->prev)
        node->prev->next = node->next;
    else
        l->head = node->next;
    if (node->next)
        node->next->prev = node->prev;
    else
        l->tail = node->prev;

    l->len--;
    return node;    
}


list *readChannel(char *channelName, list *l)
{
    
    int pipefd;
    int res;
    int readlen;
    int openMode = O_RDONLY | O_NONBLOCK;
    void *buf = zmalloc(CLIENT_POINT_SIZE);

    if(l == NULL) {
        l = listCreate();
    }

    pipefd = open(channelName, openMode);

    if(pipefd != -1) {
        do{
            readlen = read(pipefd, buf, CLIENT_POINT_SIZE);
            if(readlen > 0) {
                printf("%s\n",(char *)buf);
                l = listPush(l,buf);
                buf = NULL;
                buf = zmalloc(CLIENT_POINT_SIZE);
            }
        }while(readlen > 0);

        close(pipefd);
    } else {
        addReplyErrorFormat(c, "can't open pipe %s\n",channelName);
    }
    
    return l;

}

int writeChannel(char* channelName, void* value)
{
    int res;
    int writelen;
    int openMode = O_WRONLY;
    int pipefd;

    
    pipefd = open(channelName, openMode);
    if(pipefd != -1) {
        writelen = write(pipefd, (void *)&value, CLIENT_POINT_SIZE);

        if(writelen != CLIENT_POINT_SIZE){
            addReplyErrorFormat(c, "can't write pipe %s sizeof %d\n",channelName, CLIENT_POINT_SIZE);
        }
    } else {
        addReplyErrorFormat(c, "can't open pipe %s\n",channelName);
    }
    
    return writelen;
}

