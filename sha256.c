/*
 * https://github.com/rafaelvanoni/C.git
 * gcc sha256.c -o sha256 -lcrypto -Wall
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define	OUT_LEN ((2*SHA256_DIGEST_LENGTH) + 1)

int
main(int argc, char **argv)
{
	unsigned char h[SHA256_DIGEST_LENGTH];
	SHA256_CTX ctx;
	char out[OUT_LEN] = { 0 };
	char *str = "foobar";

	SHA256_Init(&ctx);
	SHA256_Update(&ctx, str, strlen(str));
	SHA256_Final(h, &ctx);

	printf("%s ", str);

	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		(void) sprintf(out + (i * 2), "%02x", h[i]);
	}

	out[OUT_LEN - 1] = '\0';

	printf("%s\n", out);

	return (0);
}
