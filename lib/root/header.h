#ifndef __ROOT_H__
#define __ROOT_H__

#include <stdio.h>
#include <stdbool.h>

typedef void * handler_p;

handler_p mem_handler_alloc(size_t size, char const func[]);
void mem_handler_free(handler_p h);
bool mem_empty();
void mem_report();

#define malloc(SIZE) mem_handler_alloc(SIZE, __FILE__, __LINE__)
#define free(HANDLER) mem_handler_free(HANDLER)

#endif
