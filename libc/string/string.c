
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

}
/*
while (*((Wuchar *)s1) == *((Wuchar *)s2)) {
		if (!*s1++) {
			return 0;
		}
		++s2;
	}

	return (*((Wuchar *)s1) < *((Wuchar *)s2)) ? -1 : 1;
#else
	int r;

	while (((r = ((int)(*((Wuchar *)s1))) - *((Wuchar *)s2++))
			== 0) && *s1++);

	return r;
#endif
}
*/