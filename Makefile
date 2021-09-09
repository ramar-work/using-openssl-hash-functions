CC=gcc
CFLAGS=-Wall -Werror -Wno-unused


# libgcrypt is part of GnuPG and handles different hashing functions
main:
	$(CC) $(CFLAGS) -lssl -lcrypto -o hash main.c

# Neither of the crypto libs are working on Cygwin (wouldn't care, but this is what I'm stuck with for now)
gnutls:
	$(CC) $(CFLAGS) -o hash gt.c

openssl:
	$(CC) $(CFLAGS) -o hash os.c libssl.a
