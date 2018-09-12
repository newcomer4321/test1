#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <fcntl.h>  
#include <limits.h>  
#include <sys/types.h>  
#include <sys/stat.h> 
#include "../../adlist.h"
#include "../../zmalloc.h"

#define FIFO_NAME "/tmp/loadlib_fifo"

#define BUFFER_SIZE PIPE_BUF


#define loadDebug

#ifdef loadDebug


#define LL_DEBUG 0
#define LL_VERBOSE 1
#define LL_NOTICE 2
#define LL_WARNING 3


#define addReplyErrorFormat(c,tmp,args...) fprintf(stdout,tmp,##args)
#define serverLog(level, fmt, args...) printf(fmt, ##args)

typedef struct channelData {
    void *client;
}channelData;

#define CLIENT_POINT_SIZE   (sizeof(void*))


#endif

int createChannel(char *channelName);
extern list *readChannel(char *channelName, list *l);
int writeChannel(char* channelName, void* value);
listNode *listPop(list *l);
list *listPush(list *l, void *value);




