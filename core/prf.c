#include "core/core.h"

/*
 * set of base character
 * because we can't just subtract '0'
 * from ASCII value
 */
static char bchars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWZYZ";

/*
 * keep track of panic string
 * in case it's not printed immediately
 */
static char *panicstr;

/*
 * puts a char to console
 * uses serial debug console for now
 */
int putchar(int c) {
	if (c == '\n')
		putchar('\r');
	swrite(c);
}

/*
 * stripped down version of printf
 * only supports basic formats
 * works with %c, %s, %d, %u
 */
int printf(const char *fmt, ...) {
	va_list arg;
	va_start(fmt);

	for (;;) {
		while (*fmt++ != '%') {
			if (*fmt++ == 0)
				goto out;
			putchar(*fmt);
		}

		switch (*fmt++) {
		case 'c':
			putchar(va_arg(arg, int));
			break;
		case 's':
			char *s = (char *)va_arg(arg, const char *);
			while (*s++)
				putchar(*s);
			break;
		case 'd':
			printd((long)va_arg(arg, int), 10);
			break;
		case 'u':
			printu((unsigned long)va_arg(arg, int), 10);
			break;
		case 'o':
			printd((long)va_arg(arg, int), 8);
			break;
		case 'x':
			printd((long)va_arg(arg, int), 16);
			break;
		}
	}
out:
	va_end(arg);
}

/*
 * initiates a panic
 * used for fatal, unsolvable errors
 */
int panic(const char *str) {
	printf("panic: %s", str);
	panicstr = str;
	cli();
	for (;;)
		halt();
}

/*
 * prints an usigned int
 * can be used for all bases
 */
int printu(long n, int b) {
	long a;

	if (a = n/b)
		printu(a, b);
	putchar(bchars + (n%b));
}

/*
 * prints a signed int
 * can be used for all bases
 */
int printd(long n, int b) {
	int s = n < 0;
	long a;

	if (s) {
		putchar('-');
		n = -n;
	}
	if (a = n/b)
		printu(a, b);
	putchar(bchars + (n%b));
}
