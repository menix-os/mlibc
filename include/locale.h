#ifndef _MLIBC_LOCALE_H
#define _MLIBC_LOCALE_H

#include <sys/cdefs.h>
#include <bits/locale.h>

#define NULL ((void*)0)

#define LC_ALL		__LC_ALL
#define LC_COLLATE	__LC_COLLATE
#define LC_CTYPE	__LC_CTYPE
#define LC_MESSAGES	__LC_MESSAGES
#define LC_MONETARY	__LC_MONETARY
#define LC_NUMERIC	__LC_NUMERIC
#define LC_TIME		__LC_TIME

_MLIBC_DECL_BEGIN

struct lconv
{
	char* currency_symbol;
	char* decimal_point;
	char frac_digits;
	char* grouping;
	char* int_curr_symbol;
	char int_frac_digits;
	char int_n_cs_precedes;
	char int_n_sep_by_space;
	char int_n_sign_posn;
	char int_p_cs_precedes;
	char int_p_sep_by_space;
	char int_p_sign_posn;
	char* mon_decimal_point;
	char* mon_grouping;
	char* mon_thousands_sep;
	char* negative_sign;
	char n_cs_precedes;
	char n_sep_by_space;
	char n_sign_posn;
	char* positive_sign;
	char p_cs_precedes;
	char p_sep_by_space;
	char p_sign_posn;
	char* thousands_sep;
};

locale_t duplocale(locale_t);
void freelocale(locale_t);
struct lconv* localeconv(void);
locale_t newlocale(int, const char*, locale_t);
char* setlocale(int, const char*);
locale_t uselocale(locale_t);

_MLIBC_DECL_END

#endif // <locale.h>
