// src/main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/database.h"
#include "../includes/table_ops.h"
#include "../includes/users.h"
#include "../includes/buffer_pool.h"

#define MAX_INPUT 100

void create_user_table()
{
    Column columns[] = {
        {"username", VARCHAR, 50},
        {"password", VARCHAR, 50},
    };

    int lengthOfColumns = sizeof(columns) / sizeof(Column);

    create_table("users", lengthOfColumns, columns);
    return;
}

void createCustomTableMenu()
{
    char table_name[MAX_INPUT];
    int num_columns;
    Column columns[MAX_COLUMNS];

    printf("Enter table name: ");
    scanf("%s", table_name);

    printf("Enter number of columns: ");
    scanf("%d", &num_columns);

    for (int i = 0; i < num_columns; i++)
    {
        printf("Column %d name: ", i + 1);
        scanf("%s", columns[i].name);

        printf("Column %d type (0=INT, 1=FLOAT, 2=VARCHAR): ", i + 1);
        int type;
        scanf("%d", &type);
        columns[i].type = (DataType)type;

        if (type == VARCHAR)
        {
            printf("Column %d size: ", i + 1);
            scanf("%d", &columns[i].size);
        }
        else
        {
            columns[i].size = 0;
        }
    }

    if (create_table(table_name, num_columns, columns))
    {
        printf("Table created successfully!\n");
    }
    else
    {
        printf("Failed to create table.\n");
    }
}

void insertIntoTableMenu()
{
    char table_name[MAX_INPUT];
    printf("Enter table name: ");
    scanf("%s", table_name);

    int num_columns = get_num_columns(table_name);
    if (num_columns == -1)
    {
        printf("Table not found.\n");
        return;
    }

    Column *columns = get_columns(table_name);
    if (columns == NULL)
    {
        printf("Failed to get column information.\n");
        return;
    }

    void *values[MAX_COLUMNS];
    for (int i = 0; i < num_columns; i++)
    {
        printf("Enter value for %s: ", columns[i].name);
        switch (columns[i].type)
        {
        case INT:
        {
            int *value = malloc(sizeof(int));
            scanf("%d", value);
            values[i] = value;
            break;
        }
        case FLOAT:
        {
            float *value = malloc(sizeof(float));
            scanf("%f", value);
            values[i] = value;
            break;
        }
        case VARCHAR:
        {
            char *value = malloc(columns[i].size);
            scanf("%s", value);
            values[i] = value;
            break;
        }
        }
    }

    if (insert_record(table_name, values))
    {
        printf("Record inserted successfully!\n");
    }
    else
    {
        printf("Failed to insert record.\n");
    }

    for (int i = 0; i < num_columns; i++)
    {
        free(values[i]);
    }
    free(columns);
}

void show_main_menu()
{
    int choice;
    do
    {
        printf("\nMain Menu:\n");
        printf("1. Create Custom Table\n");
        printf("2. Insert Into Table\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            createCustomTableMenu();
            break;
        case 2:
            insertIntoTableMenu();
            break;
        case 3:
            printf("Logging out...\n");
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

int main()
{
    int choice;
    int loggedIn = 0;

    init_buffer_pool();
    create_user_table();

    do
    {
        if (!loggedIn)
        {
            printf("\nLogin Menu:\n");
            printf("1. Login\n");
            printf("2. Create Account\n");
            printf("0. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar();

            switch (choice)
            {
            case 1:
                if (login())
                {
                    printf("Login successful!\n");
                    loggedIn = 1;
                    show_main_menu();
                    loggedIn = 0;
                }
                else
                {
                    printf("Login failed. Incorrect username or password.\n");
                }
                break;
            case 2:
                create_account();
                break;
            case 0:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
    } while (choice != 0);

    return 0;
}