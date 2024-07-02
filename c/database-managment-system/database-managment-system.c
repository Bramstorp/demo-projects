#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_LENGTH 50

void createDatabase()
{
    sqlite3 *db;
    char *errMessage = 0;
    int rc;

    rc = sqlite3_open("dbms.db", &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
    }

    sqlite3_close(db);
}

int main()
{
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("Welcome to the login screen\n");

    printf("Username: ");
    scanf("%s", username);
    getchar();

    printf("Password: ");
    scanf("%s", password);
    getchar();

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
    {
        printf("Login successful!\n");
        createDatabase();
    }
    else
    {
        printf("Login failed. Incorrect username or password.\n");
    }

    return 0;
}