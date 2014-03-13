void term_scan(void);
ptu32_t module_init_char_term(ptu32_t para);
s32 djy_getchar(void);
s32 djy_scanf( const char *format, char *buf );

extern char * djy_itoa(int d, char *buf, int scale);
char * strsep(char **stringp, char *delim);
extern u32 djy_atol(char *s);
extern void djy_putchar(char c);
extern int djy_printf(const char *fmt, ...);
