#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

extern sqlite3 *db;

int openDatabase();
int createTable();
void createAccount();
int checkLogin(char *username, char *password);
void closeDatabase();

#endif