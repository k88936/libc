
#include "../include/stdlib.h"
#ifndef MALLOC_H
#define MALLOC_H
inline void* malloc(unsigned size){
int id= ipSct(11);
    ipCall(id, 2);
    return (void *)(long)ipRet(id);
};
#endif