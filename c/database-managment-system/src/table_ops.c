#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/table_ops.h"

int create_table(const char *table_name, int num_columns, Column *columns)
{
    char filename[256];
    snprintf(filename, sizeof(filename), "data/%s.tbl", table_name);

    FILE *file = fopen(filename, "wb");
    if (!file)
        return 0;

    fwrite(&num_columns, sizeof(int), 1, file);
    fwrite(columns, sizeof(Column), num_columns, file);

    fclose(file);
    return 1;
}

int delete_table(const char *table_name)
{
    char filename[256];
    snprintf(filename, sizeof(filename), "data/%s.tbl", table_name);
    return remove(filename) == 0;
}

int insert_record(const char *table_name, void **values)
{
    char filename[256];
    snprintf(filename, sizeof(filename), "data/%s.tbl", table_name);

    FILE *file = fopen(filename, "r+b");
    if (!file)
        return 0;

    int num_columns;
    fread(&num_columns, sizeof(int), 1, file);

    Column columns[MAX_COLUMNS];
    fread(columns, sizeof(Column), num_columns, file);

    fseek(file, 0, SEEK_END);

    for (int i = 0; i < num_columns; i++)
    {
        switch (columns[i].type)
        {
        case INT:
            fwrite(values[i], sizeof(int), 1, file);
            break;
        case FLOAT:
            fwrite(values[i], sizeof(float), 1, file);
            break;
        case VARCHAR:
            fwrite(values[i], columns[i].size, 1, file);
            break;
        }
    }

    fclose(file);
    return 1;
}

// TODO: Implement read_record, update_record, and delete_record