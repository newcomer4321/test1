#include "../../include/loadlib.h"

int main()
{

    void *value1 = malloc(sizeof(char) *10);
    void *value2 = malloc(sizeof(char) *10);
    void *value3 = malloc(sizeof(char) *10);
    int fd;
    sprintf(value1,"value1!!");
    sprintf(value2,"value2!!");
    sprintf(value3,"value3!!");
    fd = createChannel(FIFO_NAME);
    list *l = listCreate();
    writeChannel(FIFO_NAME, value1);
    writeChannel(FIFO_NAME, value2);
    writeChannel(FIFO_NAME, value3);
    close(fd);
    return 0;
}

