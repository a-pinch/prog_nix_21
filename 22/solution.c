#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <dlfcn.h>

int (*shared_function)(int);

bool init_library(const char *libname, const char *funcname){
    void *hdl = dlopen(libname, RTLD_LAZY);
    if( NULL == hdl )
        return false;
    *(void **)(&shared_function)  = dlsym(hdl,funcname);
    if( NULL == shared_function )
        return false;
    return true;
}

int main(int c, char **v){
    if(init_library(v[1], v[2]))
        printf("%d\n",shared_function(atoi(v[3])));
    else
        return -1;
    return 0;
}
