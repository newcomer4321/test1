#include "../../include/loadlib.h"


workerInfo * findBestThread(struct reWorkerTable *workerTable)
{
	int size = workerTable->currWorkers;
	int worker;
	workerInfo *bestWorker, *worker;
	if(size > 0) {
		bestWorker = workerTable->workers[0];
		for(worker = 1; worker < size; worker++) {
			worker = workerTable->workers[i];
			if(worker->workerList->len < bestWorker->workerList->len) {
				bestWorker = worker;
			}
		}

		return bestWorker;
	} else {
		return NULL;
	} 
}


struct reWorkerTable * workerInit(int workerSize)
{
	reWorkerTable *workerTable;
	int i;
	workerTable->currWorkers = workerSize;
	workerTable->workers = (struct reWorkerInfo *) malloc(sizeof(reWorkerInfo)*workerSize);
	workerInfo * workerinfo = workerTable->workers;
	for(i = 0; i < workerSize; i++) {
		workerinfo[i]->workerList = listCreate();
		workerinfo[i]->threadRun = 1;
		if(pthread_create(&(workerinfo[i]->threadId),NULL,worker,&(workerinfo[i]))! = 0) {
			addReplyErrorFormat(c,"can't create pthread\n");
		}
	}
}

int sendToWork(workerInfo *worker, client *clientData)
{
	char *workerChannel = (char *)malloc(sizeof(char)*CHANNEL_LEN);
	sprintf(workerChannel, "%s_%d", WORKER, worker->threadId);
	int res;
	if(!channelIsCreate(workerChannel)) {
		res = createChannel(workerChannel);	
	}

	int writeMode = WR_BLOCK;
	int pipefd = openChannel(PRIMARY_TO_WORKER, writeMode);
	return writeChannel(pipefd, clientData);
}

int processCommandRE(client *cilientData)
{
	workerInfo * worker = findBestThread(workerTable);
	sendToWork(worker, c);
}

void  parseQuery(client * clientData)
{

/*
 * do parese
 *
 */	

	sendToCombiner();

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
	workerInfo *worker = (workerInfo *)value;
    list *l = worker->workerList;
	char *workerChannel = (char *)malloc(sizeof(char)*CHANNEL_LEN);
	char *combinerChannel = (char *)malloc(sizeof(char)*CHANNEL_LEN);
	sprintf(workerChannel,"%s_%d", WORKER, worker->threadId);
	sprintf(combinerChannel,"%s_%d", COMINBER, combinerId);
	int run = worker->threadRun;
    int res = 0;
    if(!channelIsCreate(workerChannel)){
        res = createChannel(workerChannel);
    }
    if(!channelIsCreate(combinerChannel)){
        res = createChannel(combinerChannel);
    }
    
    
    int readMode = RD_NOBLOCK;
    int writeMode = WR_BLOCK;
    int fdPrimaryToWorker = openChannel(workerChannel, readMode);
    int fdWorkerToCombiner = openChannel(combinerChannel, writeMode);
    int readlen = 0;
    while(run) {
        while(l->len == 0 || readlen > 0) {
            readlen = readChannel(fdPrimaryToWorker, l);
            sleep(1);
        }
        while(l->len > 0) {
            listNode *node = listPop(l);
			client * clientData = (client *)turnToAddr(node->value);

			parseQuery(clientData);
            //char * d = (char*)malloc(sizeof(void*)*10);
            //sprintf(d,"worker!");
            //writeChannel(fdWorkerToCombiner,(char *)turnToAddr(node->value));
            zfree(node);
        }
    }
    
    close(fdWorkerToCombiner);
    close(fdPrimaryToWorker);
    
}

void beforeSleepRE(struct aeEventLoop *eventLoop)
{
/*
 * we do nothing here, combiner thread will do it.
 */
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
