#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <string.h>

#define addReplyErrorFormat(c,tmp,args...) fprintf(stdout,tmp,##args)

int fileExists(char *name)
{
    struct stat st;
    if(stat(name, &st) == 0)
        return S_ISDIR(st.st_mode) ? 0 : 1;
    else if(!(errno == ENOENT || errno == ENOTDIR))
        addReplyErrorFormat(c,"can't find file %s",name);
    return 0;
        
}

int main(int argc, char **argv)
{
    if(argc != 3) {
        addReplyErrorFormat(c,"./func path name.so\n");
    }
}
