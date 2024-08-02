// src/database.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/database.h"
#include "../includes/table_ops.h"

int get_num_columns(const char *table_name)
{
    char filename[256];
    snprintf(filename, sizeof(filename), "data/%s.tbl", table_name);

    FILE *file = fopen(filename, "rb");
    if (!file)
        return -1;

    int num_columns;
    fread(&num_columns, sizeof(int), 1, file);

    fclose(file);
    return num_columns;
}

Column *get_columns(const char *table_name)
{
    char filename[256];
    snprintf(filename, sizeof(filename), "data/%s.tbl", table_name);

    FILE *file = fopen(filename, "rb");
    if (!file)
        return NULL;

    int num_columns;
    fread(&num_columns, sizeof(int), 1, file);

    Column *columns = malloc(num_columns * sizeof(Column));
    fread(columns, sizeof(Column), num_columns, file);

    fclose(file);
    return columns;
}