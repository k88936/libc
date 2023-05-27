
#include "../include/stdlib.h"
typedef long Align;/*for alignment to long boundary*/
 union header { 
    struct {
        union header *ptr; /*next block if on Mfree list*/
        unsigned size; /*size of this block*/
    } s;
   Align x;
};
typedef union header Header;
//static char space[200] ;
static Header base;
static Header *freep = NULL;
extern void free(void *ap)
{

    Header *bp,*p;
    bp = (Header *)ap -1; /* point to block header */
    for(p=freep;!(bp>p && bp< p->s.ptr);p=p->s.ptr)
        if(p>=p->s.ptr && (bp>p || bp<p->s.ptr))
            break;    /* freed block at start or end of arena*/
    if (bp+bp->s.size==p->s.ptr) {    /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p+p->s.size == bp) {     /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
 }



#define NALLOC 8 /* minimum #units to request */
static Header *morecore(unsigned nu)
{
  

   char *cp;
   Header *up;
   if(nu < NALLOC)
       nu = NALLOC;
   cp = (char *)Msbrk(
       nu * sizeof(Header)
       );
   if(cp == (char *)-1)    /* no space at all*/
       return NULL;
    up = (Header *)cp;
    up->s.size = nu;
    free((void *)(up+1));
    return freep;
}



extern void *malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;
    nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
    if((prevp = freep) == NULL) { /* no Mfree list */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for(p = prevp->s.ptr; ;prevp = p, p= p->s.ptr) {
        if(p->s.size >= nunits) { /* big enough */
            if (p->s.size == nunits)  /* exactly */
                prevp->s.ptr = p->s.ptr;
            else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
      //   cout << p+1 << endl;
            return (void*)(p+1);
        }
        if (p== freep) /* wrapped around Mfree list */
            if ((p = morecore(nunits)) == NULL)
                return NULL; /* none left */
    }
}
// int main (){
// 	int size=100;
// void * ip= (void *)malloc(size);
// }