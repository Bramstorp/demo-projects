# Setup

`sudo apt-get install sqlite3`

`mkdir build`

# Build

`gcc -o build/dbms database-managment-system.c -l sqlite3`

`./build/dbms`

# Test DB

`sqlite3 dbms.db`
