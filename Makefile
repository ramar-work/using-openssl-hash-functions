CC=clang
CFLAGS=-Wall -Werror -Wno-unused

main:
	$(CC) $(CFLAGS) -lssl -o hash main.c