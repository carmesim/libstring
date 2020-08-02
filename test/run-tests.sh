#!/bin/bash
gcc -o test tests.c ../src/libstring.c -lcriterion
if valgrind --leak-check=full --error-exitcode=23 ./test; then
    echo "Valgrind did not find any errors!"
else
    exit $127
fi
