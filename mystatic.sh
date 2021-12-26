gcc -c mystatic.c
ar -rv libmystatic.a mystatic.o
gcc mymain1.c -o mymain1 -L. -lmystatic
