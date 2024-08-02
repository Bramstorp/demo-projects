#ifndef TABLE_OPS_H
#define TABLE_OPS_H

#include <sqlite3.h>

#define MAX_COLUMNS 16
#define MAX_COLUMN_NAME 64

typedef enum
{
    INT,
    FLOAT,
    VARCHAR
} DataType;

typedef struct
{
    char name[MAX_COLUMN_NAME];
    DataType type;
    int size;
} Column;

int create_table(const char *table_name, int num_columns, Column *columns);
int delete_table(const char *table_name);
int insert_record(const char *table_name, void **values);

// TODO
int read_record(const char *table_name, int record_number, void **values);
int update_record(const char *table_name, int record_number, void **values);
int delete_record(const char *table_name, int record_number);

#endif