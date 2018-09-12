#include "../../include/loadlib.h"

int main()
{
    list *l = listCreate();
    int i = 100;
    createChannel(FIFO_NAME);
    do {
        readChannel(FIFO_NAME, l);
        i--;
    }while (i > 0);
    while(l->len > 0) {
        listNode *node = listPop(l);
        printf("%s\n",(char *)node->value);
        zfree(node);
    }
    return 0;
}
