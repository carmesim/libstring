#!/bin/bash
echo "Testing libstring under Valgrind (on -std=gnu11)"
gcc -std=gnu11 -o test tests.c ../src/libstring.c -lcriterion
if valgrind --leak-check=full --error-exitcode=23 ./test; then
    echo "Valgrind did not find any errors!"
else
    exit $127
fi

echo "Testing libstring under Valgrind (on -std=c89)"
gcc -fpreprocessed -dD -E ../src/libstring.c >> ../src/89libstring.c
gcc -fpreprocessed -dD -E ../src/libstring.h >> ../src/89libstring.h
cp ../src/libstring.c ../src/libstring-backup.c 
cp ../src/libstring.h ../src/libstring-backup.h 
mv ../src/89libstring.c ../src/libstring.c
mv ../src/89libstring.h ../src/libstring.h
cd ..
gcc -std=c89 -c -o libstring.o src/libstring.c -lcriterion
cd test
gcc ../libstring.o tests.c -lcriterion -o test-ansi
if valgrind --leak-check=full --error-exitcode=23 ./test-ansi; then
    echo "Valgrind did not find any errors!"
else
    exit $127
fi

mv ../src/libstring-backup.h ../src/libstring.h
mv ../src/libstring-backup.c ../src/libstring.c