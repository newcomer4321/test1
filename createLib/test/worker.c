#include "../../include/loadlib.h"

int main()
{
    list *l = listCreate();
    int i = 10;
    int res = 0;
    if(!channelIsCreate(PRIMARY_TO_WORKER)){
        res = createChannel(PRIMARY_TO_WORKER);
    }
    if(!channelIsCreate(WORKER_TO_COMINBER)){
        res = createChannel(WORKER_TO_COMINBER);
    }


    int readMode = RD_NOBLOCK;
    int writeMode = WR_BLOCK;
    int fdPrimaryToWorker = openChannel(PRIMARY_TO_WORKER, readMode);
    int fdWorkerToCombiner = openChannel(WORKER_TO_COMINBER, writeMode);
    int readlen = 0;
    while(1) {
        while(l->len == 0 || readlen > 0) {
            readlen = readChannel(fdPrimaryToWorker, l);
            i--;
            sleep(1);
        }
        while(l->len > 0) {
            listNode *node = listPop(l);
            printf("in worker %s len:%d\n",(char *)node->value, strlen((char*)node->value));
  //          sprintf(node->value, "worker!");
            char * d = (char*)malloc(sizeof(void*)*10);
            sprintf(d,"worker!");
            writeChannel(fdWorkerToCombiner,d);
            zfree(node);
        }
        i = 10;
    }

    close(fdWorkerToCombiner);
    close(fdPrimaryToWorker);
    return 0;
}
