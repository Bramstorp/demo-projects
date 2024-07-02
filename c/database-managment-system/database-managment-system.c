#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_LENGTH 50

sqlite3 *db;

int openDatabase()
{
    int rc = sqlite3_open("dbms.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    return 1;
}

int createTable()
{
    char *sql = "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT NOT NULL);";
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

void createAccount()
{
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char *sql;
    char *errMsg = 0;
    int rc;

    printf("Create a new account\n");

    printf("Enter new username: ");
    scanf("%s", username);
    getchar();

    printf("Enter new password: ");
    scanf("%s", password);
    getchar();

    sql = sqlite3_mprintf("INSERT INTO users (username, password) VALUES ('%q', '%q');", username, password);

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
    else
    {
        printf("\nAccount created successfully!\n");
    }

    sqlite3_free(sql);
}

int checkLogin(const char *username, const char *password)
{
    char *sql = sqlite3_mprintf("SELECT * FROM users WHERE username = '%q' AND password = '%q';", username, password);
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare statement\n");
        return 0;
    }

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_free(sql);

    return (rc == SQLITE_ROW);
}

int login()
{
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("Login\n");

    printf("Username: ");
    scanf("%s", username);
    getchar();

    printf("Password: ");
    scanf("%s", password);
    getchar();

    if (checkLogin(username, password))
    {
        printf("Login successful!\n");
        return 1;
    }
    else
    {
        printf("Login failed. Incorrect username or password.\n");
        return 0;
    }
}

int main()
{
    int choice;

    if (!openDatabase() || !createTable())
    {
        return 1;
    }

    do
    {
        printf("\nMenu:\n");
        printf("1. Login\n");
        printf("2. Create Account\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            login();
            break;
        case 2:
            createAccount();
            break;
        case 0:
            printf("Exiting program. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    sqlite3_close(db);
    return 0;
}