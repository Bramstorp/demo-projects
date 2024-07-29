#include <stdio.h>
#include "database.h"

int login()
{
    char username[50];
    char password[50];

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

    closeDatabase();
    return 0;
}