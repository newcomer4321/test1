#include "../../include/loadlib.h"

void readQueryFromClientHook(/*aeEventLoop*/ char *el, int fd, void *privdata, int mask)
{
	findBestThread();
	sendToWorker();
}




void *primary(void *value)
{
    void *value1 = malloc(sizeof(char) *10);
    void *value2 = malloc(sizeof(char) *10);
    void *value3 = malloc(sizeof(char) *10);
    sprintf(value1,"value1!!");
    sprintf(value2,"value2!!");
    sprintf(value3,"value3!!");

    int fd;
    if(!channelIsCreate(PRIMARY_TO_WORKER)){
        fd = createChannel(PRIMARY_TO_WORKER);
    }

    int writeMode = WR_BLOCK;
    int pipefd = openChannel(PRIMARY_TO_WORKER, writeMode);



    list *l = listCreate();
    writeChannel(pipefd, value1);
    sleep(10);
    writeChannel(pipefd, value2);
    sleep(10);
    writeChannel(pipefd, value3);
    sleep(100);
    free(value1);
    free(value2);
    free(value3);
    close(pipefd);
    return NULL;
}


void *worker(void *value)
{


/*
 * recFromPrimary()
 *
 * parseQuery()
 *
 * processCommandHook()-->sendToCombiner()
 *
 *
 *
 */
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
            printf("in worker %s\n",(char *)turnToAddr(node->value));
            //char * d = (char*)malloc(sizeof(void*)*10);
            //sprintf(d,"worker!");
            writeChannel(fdWorkerToCombiner,(char *)turnToAddr(node->value));
            zfree(node);
        }
        i = 10;
    }
    
    close(fdWorkerToCombiner);
    close(fdPrimaryToWorker);
    
}


void *combiner(void *value)
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
            printf("in comber:%s\n",(char *)turnToAddr(node->value));
            zfree(node);
        }
        i = 10;
    }
    return NULL;
}


int main()
{

    pthread_t pCombiner, pWorker, pPrimary;

    int primaryId = pthread_create(&pPrimary, NULL, primary, NULL);
    int workerId = pthread_create(&pWorker, NULL, worker, NULL);
    int combinerId = pthread_create(&pCombiner, NULL, combiner, NULL);

    pthread_join(pPrimary, NULL);
    pthread_join(pWorker, NULL);
    pthread_join(pCombiner, NULL);
    return 0;
}
