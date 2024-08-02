
#define MAX_INPUT 100
#include "../includes/table_ops.h"
#include <stdio.h>
#include <string.h>

int check_login(char *username, char *password)
{
    char filename[256];
    snprintf(filename, sizeof(filename), "data/users.tbl");

    FILE *file = fopen(filename, "rb");
    if (!file)
        return 0;

    int num_columns;
    fread(&num_columns, sizeof(int), 1, file);

    Column columns[MAX_COLUMNS];
    fread(columns, sizeof(Column), num_columns, file);

    char stored_username[50], stored_password[50];
    while (fread(stored_username, columns[0].size, 1, file) &&
           fread(stored_password, columns[1].size, 1, file))
    {
        if (strcmp(username, stored_username) == 0 &&
            strcmp(password, stored_password) == 0)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void create_account()
{
    char username[MAX_INPUT], password[MAX_INPUT];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (check_login(username, password))
    {
        printf("Account already exists.\n");
        return;
    }
    else
    {
        void *values[] = {username, password};
        if (insert_record("users", values))
        {
            printf("Account created successfully!\n");
        }
        else
        {
            printf("Failed to create account.\n");
        }
    }
}

int login()
{
    char username[MAX_INPUT], password[MAX_INPUT];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    return check_login(username, password);
}