#ifndef BUFFER_POOL_H
#define BUFFER_POOL_H

#include <stdint.h>

#define PAGE_SIZE 4096
#define BUFFER_POOL_SIZE 1024

typedef struct
{
    int page_id;
    char data[PAGE_SIZE];
    int is_dirty;
    int pin_count;
} Page;

typedef struct
{
    Page pages[BUFFER_POOL_SIZE];
    int page_table[BUFFER_POOL_SIZE];
} BufferPool;

void init_buffer_pool();

#endif