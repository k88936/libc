#include "sys.h"
#ifndef LIBC4M
#define LIBC4M
inline void* malloc(unsigned size){
int id= sys_itpSct(11);
    sys_itpCall(id, 2);
    return (void *)(long)sys_itpRet(id);
};
#endif
