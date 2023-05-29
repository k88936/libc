
#include "../include/string.h"





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