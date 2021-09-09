#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include <openssl/sha.h>

int main ( int argc, char *argv[] ) {

	unsigned char *arg = NULL;
	char *algo = NULL;
	int status = 0, arglen = 0;
	SHA256_CTX c;

	if ( argc < 2 ) {
		fprintf( stderr, "%s\n", "Usage: hash [ -a $ALGO ] <string>" );
		return 1;
	}

	while ( *argv ) {
		if ( !strcmp( "-a", *argv ) || !strcmp( "--algorithm", *argv ) ) {
			++argv, algo = *argv;	
		}	
		else if ( !strcmp( "-f", *argv ) || !strcmp( "--file", *argv ) ) {
			++argv, arg = (unsigned char *)*argv;	
		}	
		else if ( **argv == '-' ) {
			fprintf( stderr, "hash: Unknown argument '%s'\n", *argv );
			return 1;
		}
		else {
			arg = (unsigned char *)*argv;
			arglen = strlen( *argv );
		}
		argv++;
	}

	if ( !arg ) {
		fprintf( stderr, "hash: No string specified '%s'\n", *argv );
		return 1;
	}

	unsigned char buf[ SHA512_DIGEST_LENGTH ];
	memset( buf, 0, SHA512_DIGEST_LENGTH );	
	unsigned char *sha = SHA256( arg, arglen, buf );
	return 0;
}
