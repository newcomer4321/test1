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
#define PRIMARY_TO_WORKER "/tmp/worker_pipo"
#define WORKER_TO_COMINBER  "/tmp/cominber_pipo"



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

#define RD_NOBLOCK  O_RDONLY | O_NONBLOCK
#define RD_BLOCK    O_RDONLY
#define WR_NOBLOCK  O_WRONLY | O_NONBLOCK
#define WR_BLOCK    O_WRONLY 





int createChannel(char *channelName);
int readChannel(int pipefd, list *l);
int writeChannel(int pipefd, void* value);
listNode *listPop(list *l);
list *listPush(list *l, void *value);
int channelIsCreate(char *channelName);
int openChannel(char *channelName, int mode);



