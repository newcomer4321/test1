#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <string.h>
#include "../include/loadlib.h"

typedef int (*loadLibFunc)();


int fileExists(char *name)
{
    struct stat st;
    if(stat(name, &st) == 0)
        return S_ISDIR(st.st_mode) ? 0 : 1;
    else if(!(errno == ENOENT || errno == ENOTDIR))
        addReplyErrorFormat(c,"can't find file %s",name);
    return 0;
        
}

int loadLibCommand(char *path, char *name)
{
	if(path == NULL || name == NULL) {
        addReplyErrorFormat(c,"lib's path or name can't be NULL\n");
        return -1;	
	}
    
    int res = 0;
    int pathLen = strlen(path);
    int nameLen = strlen(name);

    char *filename = NULL;

    if(path[pathLen - 1] == '/') {
        filename = (char *)malloc(sizeof(char)*(pathLen + nameLen - 1));
        sprintf(filename, "%s%s", path, name);
    } else {
        filename = (char *)malloc(sizeof(char)*(pathLen + nameLen));
        sprintf(filename, "%s/%s", path, name);
    }

    if(fileExists(filename)) {
        void *handle = dlopen(filename, RTLD_GLOBAL | RTLD_NOW);

        if(handle == NULL) {
            addReplyErrorFormat(c,"%s\n",dlerror());
            res = -1;
        } else {
            loadLibFunc loadInit = dlsym(handle, "loadInit");

            if(loadInit == NULL) {
                addReplyErrorFormat(c,"lib must have func  loadInit() and return int\n");
                res = -1;
            } else {
                loadInit();
            }
            close(handle);
        }    
    }
    return res;
}

#ifdef loadDebug
int main(int argc, char **argv)
{
    if(argc != 3) {
        addReplyErrorFormat(c,"./func path name.so\n");
    }

    int res = loadLibCommand(argv[1], argv[2]);
    return res;
}
#endif
