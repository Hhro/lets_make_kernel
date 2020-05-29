#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <fried/stdio.h>
#include <fried/string.h>
#include <vga.h>

static bool kPrint(const char* data, size_t length) {
	for (size_t i = 0; i < length; i++)
		terminal_putchar(data[i]);
	return true;
}


/**
 * Print integer in specified base format
 * 
 * @param i integer to print
 * @param b base conversions
 * @param sg 1 if signed value, 0 otherwise
 * @param letbase character to use when digit is over 10
 * 
 * @returns printed length
 **/
static int kPrinti(int i, int b, int sg, int letbase)
{
	int t, len = 0;
	unsigned int u = i;

	if (i == 0) {
		kPutchar('0');
		len++;
	}

	if (sg && b == 10 && i < 0) {
		u = -i;
		kPutchar('-');
		len++;
	}

	char printi_buf[100];
	int idx = 0;
	while (u) {
		t = u % b;
		if( t >= 10 )
			t += letbase - '0' - 10;
		printi_buf[100-++idx] = t + '0';
		u /= b;
		len++;
	}
	if(!kPrint(&printi_buf[100-idx], idx))
		return -1;


	return len;
}
int kPrintf(const char* format, ...) {
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!kPrint(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format++;

		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!kPrint(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!kPrint(str, len))
				return -1;
			written += len;
		}
		else if( *format == 'd' ) {
			format++;
			int i = va_arg(parameters, int);
			int len = kPrinti(i, 10, 1, 'a');
			if(len == -1)
				return -1;
			written += len;
			continue;
		}
		else if( *format == 'x' ) {
			format++;
			int i = va_arg(parameters, int);
			int len = kPrinti(i, 16, 1, 'a');
			if(len == -1)
				return -1;
			written += len;
			continue;
		}
		else if( *format == 'X' ) {
			format++;
			int i = va_arg(parameters, int);
			int len = kPrinti(i, 16, 1, 'A');
			if(len == -1)
				return -1;
			written += len;
			continue;
		}
		else if( *format == 'u' ) {
			format++;
			int i = va_arg(parameters, int);
			int len = kPrinti(i, 10, 0, 'a'); 
			if(len == -1)
				return -1;
			written += len;
			continue;
		}else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!kPrint(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}
