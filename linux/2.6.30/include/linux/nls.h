#ifndef _LINUX_NLS_H
#define _LINUX_NLS_H

#include <linux/init.h>

/* unicode character */
typedef __u16 wchar_t;
#if defined(CONFIG_USB_HSAN_USB3_0)
/* Arbitrary Unicode character */
typedef u32 unicode_t;
#endif

struct nls_table {
	const char *charset;
	const char *alias;
	int (*uni2char) (wchar_t uni, unsigned char *out, int boundlen);
	int (*char2uni) (const unsigned char *rawstring, int boundlen,
			 wchar_t *uni);
	const unsigned char *charset2lower;
	const unsigned char *charset2upper;
	struct module *owner;
	struct nls_table *next;
};

/* this value hold the maximum octet of charset */
#define NLS_MAX_CHARSET_SIZE 6 /* for UTF-8 */

#if defined(CONFIG_USB_HSAN_USB3_0)
/* Byte order for UTF-16 strings */
enum utf16_endian {
	UTF16_HOST_ENDIAN,
	UTF16_LITTLE_ENDIAN,
	UTF16_BIG_ENDIAN
};
#endif

/* nls_base.c */
extern int register_nls(struct nls_table *);
extern int unregister_nls(struct nls_table *);
extern struct nls_table *load_nls(char *);
extern void unload_nls(struct nls_table *);
extern struct nls_table *load_nls_default(void);

#if defined(CONFIG_USB_HSAN_USB3_0)
extern int utf8_to_utf32(const u8 *s, int len, unicode_t *pu);
extern int utf16s_to_utf8s(const wchar_t *pwcs, int len,
		enum utf16_endian endian, u8 *s, int maxlen);
#endif
extern int utf8_mbtowc(wchar_t *, const __u8 *, int);
extern int utf8_mbstowcs(wchar_t *, const __u8 *, int);
extern int utf8_wctomb(__u8 *, wchar_t, int);
extern int utf8_wcstombs(__u8 *, const wchar_t *, int);

static inline unsigned char nls_tolower(struct nls_table *t, unsigned char c)
{
	unsigned char nc = t->charset2lower[c];

	return nc ? nc : c;
}

static inline unsigned char nls_toupper(struct nls_table *t, unsigned char c)
{
	unsigned char nc = t->charset2upper[c];

	return nc ? nc : c;
}

static inline int nls_strnicmp(struct nls_table *t, const unsigned char *s1,
		const unsigned char *s2, int len)
{
	while (len--) {
		if (nls_tolower(t, *s1++) != nls_tolower(t, *s2++))
			return 1;
	}

	return 0;
}

/*
 * nls_nullsize - return length of null character for codepage
 * @codepage - codepage for which to return length of NULL terminator
 *
 * Since we can't guarantee that the null terminator will be a particular
 * length, we have to check against the codepage. If there's a problem
 * determining it, assume a single-byte NULL terminator.
 */
static inline int
nls_nullsize(const struct nls_table *codepage)
{
	int charlen;
	char tmp[NLS_MAX_CHARSET_SIZE];

	charlen = codepage->uni2char(0, tmp, NLS_MAX_CHARSET_SIZE);

	return charlen > 0 ? charlen : 1;
}

#define MODULE_ALIAS_NLS(name)	MODULE_ALIAS("nls_" __stringify(name))

#endif /* _LINUX_NLS_H */

