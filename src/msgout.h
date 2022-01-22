//---------------------------------------------------------------------------

#ifndef msgoutH
#define msgoutH
//---------------------------------------------------------------------------
#include <stdio.h>

extern char _MprintBuf[BUFSIZ];

#define printf(...)          do {sprintf(_MprintBuf, __VA_ARGS__ );  mprintf(_MprintBuf);} while(0)
#define fprintf(fp, ...)     do { \
								 if (fp==stderr) {sprintf(_MprintBuf, __VA_ARGS__ );  mprintf(_MprintBuf);} \
								 else            fprintf(fp, __VA_ARGS__ );                                 \
							 } while(0)
#define putc(c, fp)          do { \
								 if (fp==stderr) {sprintf(_MprintBuf, "%c", c );  mprintf(_MprintBuf);} \
								 else            putc(c, fp);                                 \
							 } while(0)
#define putchar(c);          do {sprintf(_MprintBuf, "%c", c ); mprintf(_MprintBuf);} while(0)

#ifdef __cplusplus
extern "C" {
#endif

	extern int mprintf(const char *fmt);

#ifdef __cplusplus
}
#endif

#endif
