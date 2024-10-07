#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

sqlite3 *db;

int create_account_table() {
    char *sql = "CREATE TABLE IF NOT EXISTS accounts (username TEXT PRIMARY KEY, password TEXT NOT NULL);";
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 0;
    }
    return 1;
}

void create_account() {
    
}

int init_db()
{
    int rc = sqlite3_open("bank.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr, "Open");
    }
    return 1;
}

void show_main_menu()
{
    int choice;
    do
    {
        printf("\nMain Menu:\n");
        printf("1. Create account\n");
        printf("2. Sign in\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            printf("1");
            break;
        case 2:
            printf("2");
            break;
        case 3:
            printf("Exit...\n");
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

int main()
{
    if (!create_account_table() || !init_db)
    {
        return 1;
    }

    show_main_menu();
    sqlite3_close(db);
    return 0;
}