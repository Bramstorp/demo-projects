#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 50

int main()
{
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("Welcome to the login screen\n");

    printf("Username: ");
    scanf("%s", username);
    getchar();

    printf("Password: ");
    scanf(password);
    getchar();

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0)
    {
        printf("Login successful!\n");
    }
    else
    {
        printf("Login failed. Incorrect username or password.\n");
    }

    return 0;
}