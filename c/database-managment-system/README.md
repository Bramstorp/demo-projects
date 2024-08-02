# Setup C

`sudo apt-get install sqlite3`

`mkdir build`

# Build

`gcc -o build/dbms main.c database.c -l sqlite3`

# Run

`./build/dbms`

# Test DB

`sqlite3 dbms.db`

# Build and Run

`chmod +x run.sh`
`./run`
