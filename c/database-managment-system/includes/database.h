#ifndef DATABASE_H
#define DATABASE_H

#include "table_ops.h"

int get_num_columns(const char *table_name);
Column *get_columns(const char *table_name);

#endif