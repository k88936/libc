
#include "../include/stdlib.h"
#include "../string/string.c"

void *malloc(size_t size)
{
	void *result;

	if (unlikely(size == 0)) {
		size++;
	}

	/* prevent Undefined Behaviour for pointer arithmetic (substract) of too big pointers
	 * see: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63303
	 * No need to check for size + sizeof(size_t) integer overflow since we already check for PTRDIFF_MAX
	 */
	if (unlikely(size > PTRDIFF_MAX)) {
		__set_errno(ENOMEM);
		return 0;
	}


	result = mmap((void *) 0, size + sizeof(size_t), PROT_READ | PROT_WRITE,
	              MMAP_FLAGS, 0, 0);
	if (result == MAP_FAILED) {
		__set_errno(ENOMEM);
		return 0;
	}
	* (size_t *) result = size;
	return(result + sizeof(size_t));
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
		size_t old_size = *((size_t *) (ptr - sizeof(size_t)));
		memcpy(newptr, ptr, (old_size < size ? old_size : size));
		free(ptr);
	}
	return newptr;
}











// int main (){
// 	int size=100;
// void * ip= (void *)malloc(size);
// }