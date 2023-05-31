
#include "sys.h"
#define NULL 0
typedef unsigned size_t;


void *memchr(const void *s, int c, size_t n)
{
	register const char *r = (const char *) s;

	while (n) {
		if (*r == ((char)c)) {
			return (void *) r;	/* silence the warning */
		}
		++r;
		--n;
	}

	return NULL;
}

void *memcpy(void * __restrict s1, const void * __restrict s2, size_t n)
{
	register char *r1 = s1;
	register const char *r2 = s2;

	while (n) {
		*r1++ = *r2++;
		--n;
	}

	return s1;
}
void *memmove(void *s1, const void *s2, size_t n)
{
	register char *s = (char *) s1;
	register const char *p = (const char *) s2;

	if (p >= s) {
		while (n) {
			*s++ = *p++;
			--n;
		}
	} else {
		while (n) {
			--n;
			s[n] = p[n];
		}
	}

	return s1;
}
void *memset(void *s, int c, size_t n)
{
	register char *p = (char *) s;

	while (n) {
		*p++ = (char) c;
		--n;
	}

	return s;
}
char *strcat(char * __restrict s1, register const char * __restrict s2)
{
	register char *s = s1;

	while (*s++);
	--s;
	while ((*s++ = *s2++) != 0);

	return s1;
}
char *strchr(register const char *s, int c)
{
	do {
		if (*s == ((char)c)) {
			return (char *) s;	/* silence the warning */
		}
	} while (*s++);

	return NULL;
}
size_t strlen(const char *s)
{
	register const char *p;

	for (p=s ; *p ; p++);

	return p - s;
}
int strcmp(register const char *s1, register const char *s2)
{
	while (*((char *)s1) == *((char *)s2)) {
		if (!*s1++) {
			return 0;
		}
		++s2;
	}

	return (*((char *)s1) < *((char *)s2)) ? -1 : 1;

}char *strncpy(char * __restrict s1, register const char * __restrict s2,
				size_t n)
{
	register char *s = s1;

	while (n) {
		if ((*s = *s2) != 0) s2++; /* Need to fill tail with 0s. */
		++s;
		--n;
	}

	return s1;
}

size_t strcspn(const char *s1, const char *s2)
{
	register const char *s;
	register const char *p;

	for ( s=s1 ; *s ; s++ ) {
		for ( p=s2 ; *p ; p++ ) {
			if (*p == *s) goto done;
		}
	}
 done:
	return s - s1;
}
// char *strerror(int errnum)
// {
//     static char buf[_STRERROR_BUFSIZE];

// 	__xpg_strerror_r(errnum, buf, sizeof(buf));

// 	return buf;
// }
char *strpbrk(const char *s1, const char *s2)
{
	register const char *s;
	register const char *p;

	for ( s=s1 ; *s ; s++ ) {
		for ( p=s2 ; *p ; p++ ) {
			if (*p == *s) return (char *) s; /* silence the warning */
		}
	}
	return NULL;
}
char *strrchr(register const  char *s, int c)
{
	register const char *p;

	p = NULL;
	do {
		if (*s == (char) c) {
			p = s;
		}
	} while (*s++);

	return (char *) p;			/* silence the warning */
}
size_t strspn(const char *s1, const char *s2)
{
	register const char *s = s1;
	register const char *p = s2;

	while (*p) {
		if (*p++ == *s) {
			++s;
			p = s2;
		}
	}
	return s - s1;
}
char *strstr(const char *s1, const char *s2)
{
	register const char *s = s1;
	register const char *p = s2;

	do {
		if (!*p) {
			return (char *) s1;;
		}
		if (*p == *s) {
			++p;
			++s;
		} else {
			p = s2;
			if (!*s) {
				return NULL;
			}
			s = ++s1;
		}
	} while (1);
}

char *strtok_r(char * __restrict s1, const char * __restrict s2,
				 char ** __restrict next_start)
{
	register char *s;
	register char *p;


	if (((s = s1) != NULL) || ((s = *next_start) != NULL)) {
		if (*(s += strspn(s, s2))) {
			if ((p = strpbrk(s, s2)) != NULL) {
				*p++ = 0;
			}
		} else {
			p = s = NULL;
		}
		*next_start = p;
	}
	return s;

}
char *strtok(char * __restrict s1, const char * __restrict s2)
{
	static char *next_start;	/* Initialized to 0 since in bss. */
	return strtok_r(s1, s2, &next_start);
}









typedef long Align;/*for alignment to long boundary*/
 union header { 
    struct {
        union header *ptr; /*next block if on Mfree list*/
        size_t size; /*size of this block*/
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
   cp = (char *)sys_sbrk(
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


void *calloc(size_t nitems, size_t size){
    unsigned n=size*nitems;
    void *ptr=malloc(n);
    memset(ptr,0,n);
	return ptr;
}
void *realloc(void *ptr, size_t size)
{
	void *newptr = NULL;

	if (!ptr)
		return malloc(size);
	if (!size) {
		free(ptr);
		return malloc(0);
	}

	newptr = malloc(size);
	if (newptr) {
		size_t old_size = ((Header *) (ptr - 1))->s.size;
		memcpy(newptr, ptr, (old_size < size ? old_size : size));
		free(ptr);
	}
	return newptr;
}






#define TABLE_BASE 0x2e
#define TABLE_SIZE 0x4d

#define XX ((char)0x40)


static const char a64l_table[TABLE_SIZE] =
{
  /* 0x2e */                                                           0,  1,
  /* 0x30 */   2,  3,  4,  5,  6,  7,  8,  9, 10, 11, XX, XX, XX, XX, XX, XX,
  /* 0x40 */  XX, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
  /* 0x50 */  27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, XX, XX, XX, XX, XX,
  /* 0x60 */  XX, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
  /* 0x70 */  53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63
};


long int a64l (const char *string)
{
  const char *ptr = string;
  unsigned long int result = 0ul;
  const char *end = ptr + 6;
  int shift = 0;

  do
    {
      unsigned index;
      unsigned value;

      index = *ptr - TABLE_BASE;
      if ((unsigned int) index >= TABLE_SIZE)
	break;
      value = (int) a64l_table[index];
      if (value == (int) XX)
	break;
      ++ptr;
      result |= value << shift;
      shift += 6;
    }
  while (ptr != end);

  return (long int) result;
}

double atof(const char *nptr)
{
	return strtod(nptr, (char **) NULL);
}
int atoi(const char *nptr)
{
	return (int) strtol(nptr, (char **) NULL, 10);
}
long atol(const char *nptr)
{
	return strtol(nptr, (char **) NULL, 10);
}
long long atoll(const char *nptr)
{
	return strtoll(nptr, (char **) NULL, 10);
}

void *bsearch(const void *key, const void *base, size_t /* nmemb */ high,
			  size_t size, int (*compar)(const void *, const void *))
{
	register char *p;
	size_t low;
	size_t mid;
	int r;

	if (size > 0) {				/* TODO: change this to an assert?? */
		low = 0;
		while (low < high) {
			mid = low + ((high - low) >> 1); /* Avoid possible overflow here. */
			p = ((char *)base) + mid * size; /* Could overflow here... */
			r = (*compar)(key, p); /* but that's an application problem! */
			if (r > 0) {
				low = mid + 1;
			} else if (r < 0) {
				high = mid;
			} else {
				return p;
			}
		}
	}
	return NULL;
}

void ssort(void  *base,
           size_t nel,
           size_t width,
           int (*comp)(const void *, const void *))
{
	size_t wnel, gap, wgap, i, j, k;
	char *a, *b, tmp;

	wnel = width * nel;
	for (gap = 0; ++gap < nel;)
		gap *= 3;
	while ((gap /= 3) != 0) {
		wgap = width * gap;
		for (i = wgap; i < wnel; i += width) {
			for (j = i - wgap; ;j -= wgap) {
				a = j + (char *)base;
				b = a + wgap;
				if ((*comp)(a, b) <= 0)
					break;
				k = width;
				do {
					tmp = *a;
					*a++ = *b;
					*b++ = tmp;
				} while (--k);
				if (j < wgap)
					break;
			}
		}
	}
}
void qsort(void  *base,
           size_t nel,
           size_t width,
           __compar_fn_t comp)
{
	return qsort_r (base, nel, width, (__compar_d_fn_t) comp, NULL);
}

void qsort_r(void  *base,
           size_t nel,
           size_t width,
           __compar_d_fn_t comp,
		   void *arg)
{
	size_t wgap, i, j, k;
	char tmp;

	if ((nel > 1) && (width > 0)) {
		assert(nel <= ((size_t)(-1)) / width); /* check for overflow */
		wgap = 0;
		do {
			wgap = 3 * wgap + 1;
		} while (wgap < (nel-1)/3);
		/* From the above, we know that either wgap == 1 < nel or */
		/* ((wgap-1)/3 < (int) ((nel-1)/3) <= (nel-1)/3 ==> wgap <  nel. */
		wgap *= width;			/* So this can not overflow if wnel doesn't. */
		nel *= width;			/* Convert nel to 'wnel' */
		do {
			i = wgap;
			do {
				j = i;
				do {
					register char *a;
					register char *b;

					j -= wgap;
					a = j + ((char *)base);
					b = a + wgap;
					if ((*comp)(a, b, arg) <= 0) {
						break;
					}
					k = width;
					do {
						tmp = *a;
						*a++ = *b;
						*b++ = tmp;
					} while (--k);
				} while (j >= wgap);
				i += width;
			} while (i < nel);
			wgap = (wgap - width)/3;
		} while (wgap);
	}
}