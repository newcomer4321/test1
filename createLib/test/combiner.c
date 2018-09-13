#include "../../include/loadlib.h"

int main()
{
    list *l = listCreate();
    int i = 10;
    int fd;
    if(!channelIsCreate(WORKER_TO_COMINBER)){
        fd = createChannel(WORKER_TO_COMINBER);
    }

    int readMode = RD_NOBLOCK;
    int pipefd = openChannel(WORKER_TO_COMINBER, readMode);
    int readlen = 0;
    while(1) {
        while(l->len == 0 || readlen > 0) {
            readlen = readChannel(pipefd, l);
            i--;
            sleep(1);
        }
        while(l->len > 0) {
            listNode *node = listPop(l);
            printf("%s\n",(char *)node->value);
            zfree(node);
        }
        i = 10;
    }
    return 0;
}
