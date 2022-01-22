/* ------------------------------------------------------------------------ */
/* LHa for UNIX    Archiver Driver											*/
/*																			*/
/*		Modified          		Nobutaka Watazaki							*/
/*																			*/
/*	Ver. 1.14 	Soruce All chagned				1995.01.14	N.Watazaki		*/
/*	Ver. 1.14i 	Modified and bug fixed			2000.10.06	t.okamoto   	*/
/* ------------------------------------------------------------------------ */
/*
	Included...
		lharc.h		interface.h		slidehuf.h
*/
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#if unix
#include <sys/file.h>
#endif
#include <sys/stat.h>

#include <signal.h>

#ifdef __FreeBSD__
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <utime.h>
#endif

#if !unix
#include "config.h"
#endif

#include "lha_macro.h"

#if WIN32
/* Win32 include files */
#include <stdlib.h>
#include <io.h>
#endif /* WIN32 */

#if __BORLANDC__
#include <utime.h>
#include <dir.h>

#define SIGHUP		SIGSEGV
#ifdef interface
#undef interface
#endif
#define interface interface_
#define child	_child_

#include "msgout.h"			// kuze
#endif /* __BORLANDC__ */

#ifdef _MSC_VER
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <direct.h>

#define SIGHUP		SIGSEGV

#define	rmdir _rmdir
#define	chmod _chmod
#define	strdup _strdup
#define	umask	_umask
#define isatty	_isatty
#define mktemp	_mktemp
#define mkdir	_mkdir
#define	utime	_utime
#endif /* _MSC_VER */

struct encode_option {
#if defined(__STDC__) || defined(AIX)
	void            (*output) (); /* (unsigned int, unsigned int); */
	void            (*encode_start) (void);
	void            (*encode_end) (void);
#else
	int             (*output) ();
	int             (*encode_start) ();
	int             (*encode_end) ();
#endif
};

struct decode_option {
#if defined(__STDC__) || defined(AIX)
	unsigned short  (*decode_c) (void);
	unsigned short  (*decode_p) (void);
	void            (*decode_start) (void);
#else
	unsigned short  (*decode_c) ();
	unsigned short  (*decode_p) ();
	int             (*decode_start) ();
#endif
};

/* ------------------------------------------------------------------------ */
/*	LHa File Type Definition												*/
/* ------------------------------------------------------------------------ */
struct string_pool {
	int             used;
	int             size;
	int             n;
	char           *buffer;
};

typedef struct LzHeader {
	unsigned char   header_size;
	char            method[METHOD_TYPE_STRAGE];
	long            packed_size;
	long            original_size;
	long            last_modified_stamp;
	unsigned char   attribute;
	unsigned char   header_level;
	char            name[256];
	unsigned short  crc;
	_Boolean         has_crc;
	unsigned char   extend_type;
	unsigned char   minor_version;

	/* extend_type == EXTEND_UNIX  and convert from other type. */
	time_t          unix_last_modified_stamp;
	unsigned short  unix_mode;
	unsigned short  unix_uid;
	unsigned short  unix_gid;
}  LzHeader;

struct interfacing {
	FILE			*infile;
	FILE			*outfile;
	unsigned long   original;
	unsigned long   packed;
	int             dicbit;
	int             method;
};


/* ------------------------------------------------------------------------ */
/*	Option switch variable													*/
/* ------------------------------------------------------------------------ */
/* command line options (common options) */
EXTERN _Boolean  quiet;
EXTERN _Boolean  text_mode;
EXTERN _Boolean  verbose;
EXTERN _Boolean  noexec;		/* debugging option */
EXTERN _Boolean  force;
EXTERN _Boolean  prof;
EXTERN _Boolean  delete_after_append;
EXTERN int		compress_method;
EXTERN int		header_level;
/* EXTERN int		quiet_mode; */   /* 1996.8.13 t.okamoto */
#ifdef EUC
EXTERN _Boolean	euc_mode;
#endif

/* list command flags */
EXTERN _Boolean  verbose_listing;

/* extract/print command flags */
EXTERN _Boolean  output_to_stdout;

/* add/update/delete command flags */
EXTERN _Boolean  new_archive;
EXTERN _Boolean  update_if_newer;
EXTERN _Boolean  generic_format;

EXTERN _Boolean	remove_temporary_at_error;
EXTERN _Boolean	recover_archive_when_interrupt;
EXTERN _Boolean	remove_extracting_file_when_interrupt;
EXTERN _Boolean	get_filename_from_stdin;
EXTERN _Boolean	ignore_directory;
EXTERN _Boolean	verify_mode;

/* Indicator flag */
EXTERN int		quiet_mode;

/* ------------------------------------------------------------------------ */
/*	Globale Variable														*/
/* ------------------------------------------------------------------------ */
EXTERN char		**cmd_filev;
EXTERN int      cmd_filec;

EXTERN char		*archive_name;
EXTERN char     expanded_archive_name[FILENAME_LENGTH];
EXTERN char     temporary_name[FILENAME_LENGTH];
EXTERN char     backup_archive_name[FILENAME_LENGTH];

EXTERN char		*reading_filename, *writting_filename;

/* 1996.8.13 t.okamoto */
#if 0
EXTERN _Boolean  remove_temporary_at_error;
EXTERN _Boolean  recover_archive_when_interrupt;
EXTERN _Boolean  remove_extracting_file_when_interrupt;
#endif

EXTERN int      archive_file_mode;
EXTERN int      archive_file_gid;

EXTERN struct	interfacing interface;
EXTERN node		*next;
/* EXTERN unsigned short crc; */  /* 1996.8.13 t.okamoto */

EXTERN int      noconvertcase; /* 2000.10.6 */

/* slide.c */
EXTERN int      unpackable;
EXTERN unsigned long origsize, compsize;
EXTERN unsigned short dicbit;
EXTERN unsigned short maxmatch;
EXTERN unsigned long count;
EXTERN unsigned long loc;			/* short -> long .. Changed N.Watazaki */
EXTERN unsigned char *text;
EXTERN int		prev_char;

/* huf.c */
#ifndef LHA_MAIN_SRC  /* t.okamoto 96/2/20 */
EXTERN unsigned short left[], right[];
EXTERN unsigned char c_len[], pt_len[];
EXTERN unsigned short c_freq[], c_table[], c_code[];
EXTERN unsigned short p_freq[], pt_table[], pt_code[], t_freq[];
#endif

/* append.c */
#ifdef NEED_INCREMENTAL_INDICATOR
EXTERN long		indicator_count;
EXTERN long		indicator_threshold;
#endif

/* crcio.c */
EXTERN FILE		*infile, *outfile;
EXTERN unsigned short crc, bitbuf;
EXTERN int      dispflg;
EXTERN long		reading_size;

/* from dhuf.c */
EXTERN unsigned int n_max;

/* lhadd.c */
EXTERN FILE		*temporary_fp;

/* ------------------------------------------------------------------------ */
/*	Functions																*/
/* ------------------------------------------------------------------------ */
/* from lharc.c */
extern _Boolean	ignore_directory;
extern _Boolean	compress_method;
extern _Boolean	verify_mode;

extern char		*extract_directory;
extern char		*base_directory;

#ifdef __cplusplus
extern "C" {
#endif

/* from lharc.c */
extern int main P((int argc, char *argv[]));
extern void message P((char *subject, char *name));
extern void warning P((char *subject, char *name));
extern void error P((char *subject, char *msg));
extern void fatal_error P((char *msg));
extern void write_error P((void));
extern void read_error P((void));
extern void interrupt P((int signo));
extern char *xmalloc P((int size));
extern char *xrealloc P((char *old, int size));
extern void init_sp P((struct string_pool *sp));
extern void add_sp P((struct string_pool *sp, char *name, int len));
extern void finish_sp P((register struct string_pool *sp, int *v_count, char ***v_vector));
extern void free_sp P((char **vector));
extern void cleaning_files P((int *v_filec, char ***v_filev));
extern _Boolean find_files P((char *name, int *v_filec, char ***v_filev));
extern void free_files P((int filec, char **filev));
extern _Boolean find_files P((char *name, int *v_filec, char ***v_filev));
extern void free_files P((int filec, char **filev));
extern void build_temporary_name P((void));
extern void build_backup_name P((char *buffer, char *original));
extern void build_standard_archive_name P((char *buffer, char *orginal));
extern _Boolean need_file P((char *name));
extern FILE *xfopen P((char *name, char *mode));
extern FILE *open_old_archive P((void));
extern int inquire P((char *msg, char *name, char *selective));
extern void write_archive_tail P((FILE *nafp));
extern void copy_old_one P((FILE *oafp, FILE *nafp, LzHeader *hdr));

/* from slide.c */
extern int encode_alloc P((int method));
extern void get_next_match P((void));
extern void encode P((struct interfacing *interface_));
extern void decode P((struct interfacing *interface_));

/* from append.c */
extern int encode_lzhuf P((FILE *infp, FILE *outfp, long size,
	long *original_size_var, long *packed_size_var, char *name,
	char *hdr_method));
extern void start_indicator P((char *name, long size, char *msg,
	long def_indicator_threshold));
extern void finish_indicator2 P((char *name, char *msg, int pcnt));
extern void finish_indicator P((char *name, char *msg));

/* huf.c */
extern void output_st1 P((unsigned short c, unsigned short p));
extern unsigned char *alloc_buf P((void));
extern void encode_start_st1 P((void));
extern void encode_end_st1 P((void));
extern unsigned short decode_c_st1 P((void));
extern unsigned short decode_p_st1 P((void));
extern void decode_start_st1 P((void));

/* from shuf.c */
extern void decode_start_st0 P((void));
extern void encode_p_st0 P((unsigned short j));
extern void encode_start_fix P((void));
extern void decode_start_fix P((void));
extern unsigned short decode_c_st0 P((void));
extern unsigned short decode_p_st0 P((void));

/* from dhuf.c */
extern void start_c_dyn P((void));
extern void decode_start_dyn P((void));
extern unsigned short decode_c_dyn P((void));
extern unsigned short decode_p_dyn P((void));
extern void output_dyn P((unsigned int code, unsigned int pos));
extern void encode_end_dyn P((void));

/* from extract.c */
extern int decode_lzhuf P((FILE *infp, FILE *outfp, long original_size,
	long packed_size, char *name, int method));

/* header.c */
extern int calc_sum P((register char *p, register int len));
extern _Boolean get_header P((FILE *fp, register LzHeader *hdr));
extern void init_header P((char *name, struct stat *v_stat, LzHeader *hdr));
extern void write_header P((FILE *nafp, LzHeader *hdr));

/* from larc.c */
extern unsigned short decode_c_lzs P((void));
extern unsigned short decode_p_lzs P((void));
extern void decode_start_lzs P((void));
extern unsigned short decode_c_lz5 P((void));
extern unsigned short decode_p_lz5 P((void));
extern void decode_start_lz5 P((void));

/* from lhext.c */
extern void cmd_extract P((void));

/* from lhlist.c */
extern void cmd_list P((void));

/* from maketbl.c */
extern void make_table P((short nchar, unsigned char bitlen[], short tablebits,
	unsigned short table[]));

/* from maketree.c */
extern void make_code P((int n, unsigned char len[], unsigned short code[]));
extern short make_tree P((int nparm, unsigned short freqparm[],
	unsigned char lenparm[], unsigned short codeparm[]));

/* from patmatch.c */
extern int patmatch P((register char *p, register char *s, int f));

/* from crcio.c */
extern void make_crctable P((void));
extern unsigned short calccrc P((unsigned char *p, unsigned int n));
extern void fillbuf P((unsigned char n));
extern unsigned short getbits P((unsigned char n));
extern void putcode P((unsigned char n, unsigned short x));
extern void putbits P((unsigned char n, unsigned short x));
extern int fread_crc P((unsigned char *p, int n, FILE *fp));
extern void fwrite_crc P((unsigned char *p, int n, FILE *fp));
extern void init_code_cache P((void));
extern void init_getbits P((void));
extern void init_putbits P((void));
#ifdef EUC
extern void putc_euc P((int c, FILE *fd));
#endif
extern int fwrite_txt P((unsigned char *p, int n, FILE *fp));
extern int fread_txt P((unsigned char *p, int n, FILE *fp));
extern unsigned short calc_header_crc P((unsigned char *p, unsigned int n));

/* from lhadd.c */
extern FILE *append_it P((char *name, FILE *oafp, FILE *nafp));
extern void temporary_to_new_archive_file P((long new_archive_size));
extern void cmd_add P((void));
extern void cmd_delete P((void));
extern int strcmp_filename P((char *str1, char *str2));

/* from util.c */
extern long copyfile P((FILE *f1, FILE *f2, long size, int crc_flg));
extern int encode_stored_crc P((FILE *ifp, FILE *ofp, long size,
	long *original_size_var, long *write_size_var));
extern unsigned char *convdelim P((unsigned char *path, unsigned char delim));
extern _Boolean archive_is_msdos_sfx1 P((char *name));
extern _Boolean skip_msdos_sfx1_code P((FILE *fp));
#ifdef NOSTRDUP
extern char *strdup P((char *buf));
#endif
#if defined (NOBSTRING) && !defined (__STDC__)
extern void *memmove P((register char *dst, register char *src, register int cnt));
#endif
#if defined(NOFTRUNCATE) && !defined(_MINIX) && defined(NORENAME)
extern int rename P((char *from, char *to));
#endif
#ifdef	NOMKDIR
extern int rmdir P((char *path));
extern int mkdir P((char *path, int mode));
#endif
#ifndef USESTRCASECMP
extern int strucmp P((register char *s, register char *t));
#endif
#ifdef NOMEMSET
extern char *memset P((char *s, int c, int n));
#endif

//#if __BORLANDC__
//char *strdup P((char *));
//#endif /* __BORLANDC__ */

#ifdef __cplusplus
}
#endif

/* Local Variables: */
/* mode:c */
/* tab-width:4 */
/* End: */


