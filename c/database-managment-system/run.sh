#!/bin/bash

# Build the project
gcc -o build/dbms main.c database.c -l sqlite3

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Run the program
    ./build/dbms
else
    echo "Compilation failed"
fi