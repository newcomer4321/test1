#include "../../include/loadlib.h"

int main()
{
    list *l = listCreate();
    int i = 10;
    int fd;
    if(!channelIsCreate(FIFO_NAME)){
        fd = createChannel(FIFO_NAME);
    }

    int readMode = RD_NOBLOCK;
    int pipefd = openChannel(FIFO_NAME, readMode);

    do {
        readChannel(pipefd, l);
        i--;
        sleep(1);
    }while (i > 0);
    while(l->len > 0) {
        listNode *node = listPop(l);
        printf("%s\n",(char *)node->value);
        zfree(node);
    }
    return 0;
}
