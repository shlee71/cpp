gcc myssl.c -o myssl  -I /usr/local/ssl/include -L /usr/local/ssl/lib -lssl -lcrypto -Wno-unused-value
