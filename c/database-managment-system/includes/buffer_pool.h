#ifndef BUFFER_POOL_H
#define BUFFER_POOL_H

#include <stdint.h>

#define PAGE_SIZE 4096
#define BUFFER_POOL_SIZE 1024

typedef struct
{
    int page_id;          // the unique identifier of the page
    char data[PAGE_SIZE]; // the actual data stored in the page
    int is_dirty;         // 1 if the page has been modified, 0 otherwise
    int pin_count;        // number of users currently using the page
} Page;                   // a fixed-size block of data

typedef struct
{
    Page pages[BUFFER_POOL_SIZE];     // the actual pages stored in the buffer pool
    int page_table[BUFFER_POOL_SIZE]; // maps page_id to index in pages array
} BufferPool;                         // a collection of pages

void init_buffer_pool();

#endif