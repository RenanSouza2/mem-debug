#ifndef __ROOT_H__
#define __ROOT_H__

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef void * handler_p;

handler_p mem_handler_alloc(size_t size, char format[], ...);
bool mem_handler_free(handler_p h, char format[], ...);

bool mem_empty();
void mem_report(char tag[]);
void mem_report_full(char tag[]);
handler_p mem_get_pointer(int x, int y);

#define malloc(SIZE) mem_handler_alloc(SIZE, "f|%s|l|%d", __func__, __LINE__)
#define free(HANDLER) assert(mem_handler_free(HANDLER, "f|%s|l|%d", __func__, __LINE__))

#endif
