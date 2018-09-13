#include "../../include/loadlib.h"

int main()
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
    writeChannel(pipefd, value2);
    writeChannel(pipefd, value3);
    free(value1);
    free(value2);
    free(value3);
    close(pipefd);
    return 0;
}

