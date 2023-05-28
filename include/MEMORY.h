
#include "../libc/include/libc.h"
#ifndef MEMORY_H
#define MEMORY_H
inline void* malloc(unsigned size){
int id= sys_itpSct(11);
    sys_itpCall(id, 2);
    return (void *)(long)sys_itpRet(id);
};
#endif
