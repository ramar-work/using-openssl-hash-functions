#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include <openssl/sha.h>


struct algo_choice {
	const char *alg;
	int bufsize;
	unsigned char *(*calc)( const unsigned char *, size_t, unsigned char *);	
} algo_choices[] = {
	{ "sha1"  , SHA_DIGEST_LENGTH, SHA1 }
,	{ "sha224", SHA224_DIGEST_LENGTH, SHA224 }
,	{ "sha256", SHA256_DIGEST_LENGTH, SHA256 }
,	{ "sha384", SHA384_DIGEST_LENGTH, SHA384 }
,	{ "sha512", SHA512_DIGEST_LENGTH, SHA512 }
,	{ NULL }
};


int main ( int argc, char *argv[] ) {

	unsigned char *arg = NULL;
	char *algo = NULL;
	int status = 0, arglen = 0, v = 0;

	if ( argc < 2 ) {
		fprintf( stderr, "%s\n", "Usage: hash [ -a $ALGO ] <string>" );
		return 1;
	}

	while ( *argv ) {
		if ( !strcmp( "-a", *argv ) || !strcmp( "--algorithm", *argv ) )
			++argv, algo = *argv;	
		else if ( !strcmp( "-f", *argv ) || !strcmp( "--file", *argv ) )
			++argv, arg = (unsigned char *)*argv;	
		else if ( !strcmp( "-v", *argv ) || !strcmp( "--verbose", *argv ) )
			v = 1;	
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

	if ( !algo ) {
		algo = "sha256";
	}

	for ( struct algo_choice *c = algo_choices; c->alg; c++ ) {
		if ( !strcasecmp( c->alg, algo ) ) {
			sel = c;
			break;
		}
	}

	if ( !sel ) {
		fprintf( stderr, "hash: No algorithm '%s' available\n", algo );
		return 1;
	}

	unsigned char *sha, *usr, buf[ sel->bufsize ], ret[ sel->bufsize * 2 ];
	memset( buf, 0, sel->bufsize ), memset( ret, 0, sel->bufsize * 2 );	
	sha = sel->calc( arg, arglen, buf ), usr = ret;

	//Spits out a sequence of unsigned characters
	//fprintf( stdout, "%s\n", sha );
	
	//We can do the following to show only printable characters
	//THANKS to this StackOverflow post: 
	//https://stackoverflow.com/questions/59112701/sha512-c-program-using-the-openssl-library 
	for ( int i = 0; i < sel->bufsize; i++, sha++, usr += 2 ) {
		sprintf( (char *)usr, "%02x", *sha );
	}

	printf( "%s\n", ret );
	return 0;
}
