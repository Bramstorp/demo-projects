#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

int main()
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Welcome to this amazing bank system, please sign in \n");

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);


    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Login succesfully Welcome: %s\n", username);
    } else {
        printf("Login failed try again. \n");
    }

    return 0;
}