/*
 * Copyright (c) 2013 Sunil Nimmagadda <sunil@sunilnimmagadda.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "openbsd-compat.h"

#define PASSWORD_LEN	128

static unsigned char itoa64[] =	 /* 0 ... 63 => ascii - 64 */
	"./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

static void to64(char *, long int, int);
static void print_passwd(const char *);

int
main(int argc, char *argv[])
{
	char	*s;
	size_t	len;

	if (argc == 2) {
		print_passwd(argv[1]);
		return (0);
	} else if (argc > 2) {
		fprintf(stderr, "usage: encrypt string\n");
		return (1);
	}

	while ((s = fgetln(stdin, &len)) != NULL) {
		s[len - 1] = '\0';
		print_passwd(s);
	}

	return (0);
}

void
print_passwd(const char *string)
{
	char *c, salt[PASSWORD_LEN];

	to64(&salt[0], chacha_random(), 2);
	salt[2] = '\0';
	if ((c = crypt(string, salt)) == NULL) {
		fprintf(stderr, "crypt failed");
		exit(1);
	}

	printf("%s\n", c);
}

void
to64(char *s, long int v, int n)
{
	while (--n >= 0) {
		*s++ = itoa64[v&0x3f];
		v >>= 6;
	}
}