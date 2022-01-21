/*
 * LHa for UNIX ver 1.14i コンフィグレーション (Makefile, SWITCHESマクロ参照)
 *
 * 機種依存マクロは、MACHINES ファイルに設定例がありますので参照願います。
 */
/*
 *	Windows 95/98/Me の DOS 窓で動く lha 
 *	使用コンパイラ BORLAND C++ 5.01
 */
/* 機種非依存のマクロ */

#undef NEED_INCREMENTAL_INDICATOR	/* 経過表示グラフを表示するようにします。 */
#undef EUC				/* 漢字コード変換を行なう e オプションを用意します。 */
#undef ARCHIVENAME_EXTENTION		/* デフォルトのアーカイブ拡張子。デフォルトは ".lzh" 。 */
#undef BACKUPNAME_EXTENTION		/* バックアップアーカイブの拡張子。デフォルトは ".bak" 。 */
#define TMP_FILENAME_TEMPLATE "lhXXXXXX" /* 作業ファイルのテンプレート。 */
#define SUPPORT_LH7			/* -lh7- methodをサポートするときに定義します。*/

/* 機種依存マクロ */

/* --インクルードファイル関係 */
#define USG			/* <strings.h> がないときに定義します。 */
#define SYSTIME_HAS_NO_TM	/* <sys/time.h> に struct tm がないときに定義します。 */

/* --文字列関係 */
#define NOBSTRING		/* bstring(3) がないときに定義します。 */
#define NOINDEX			/* index(3) がないときに定義します。 */
#undef NOSTRDUP			/* strdup(3) がないときに定義します。 */
#undef USESTRCASECMP		/* strcasecmp(3) があるときに定義します。 */
#undef NOMEMSET			/* memset(3)がないときに定義します。 */

/* --timezone 情報の取得関係 */
#define FTIME			/* ftime(3C) を使用した変換を行なう時に定義します。 */
#undef GETTIMEOFDAY		/* gettimeofday(2) を使用した変換を行なう時に定義します。 */
#define MKTIME			/* mktime(3C) を使用した変換を行なう時に定義します。 */
#undef TIMELOCAL		/* timelocal(3V) を使用した変換を行なう時に定義します。 */
#undef TZSET			/* tzset(3C) を使用した変換を行なう時に定義します。 */
#undef TIMEZONE_HOOK

/* --ディレクトリ操作関係 */
#undef NONSYSTEM_DIR_LIBRARY	/* ディレクトリ操作関数(opendir,readdir,closedir)が */
				/* ないときに定義します。Makefile の LIBRARYOBJS に */
				/* lhdir$(O) を追加してください。 */
#if __BORLANDC__
#define SYSV_SYSTEM_DIR		/* struct dirent (direct ではない)があるときに定義します。 */
#undef NODIRECTORY		/* 上記マクロを使用しても失敗する時に定義します。 */
#endif /* __BORLANDC__ */
#if _MSC_VER
#undef SYSV_SYSTEM_DIR		/* struct dirent (direct ではない)があるときに定義します。 */
#define NODIRECTORY		/* 上記マクロを使用しても失敗する時に定義します。 */
#endif /* _MSC_VER */

/* --その他 */
#define NOFTRUNCATE		/* ftruncate(2) がない時に定義します。 */
#undef NOMKDIR			/* mkdir(2) がないときに定義します。 */
#undef MKDIRPATH		/* mkdir の外部コマンド名を定義します。NOMKDIR と */
				/* 同時に機能します。デフォルトは "/bin/mkdir" です。 */
#undef RMDIRPATH		/* rmdir の外部コマンド名を定義します。NOMKDIR と */
				/* 同時に機能します。デフォルトは "/bin/rmdir" です。 */
#define NOT_COMPATIBLE_MODE
#undef HAVE_NO_LCHOWN		/* lchown(2)が無いときに定義します */

/* 追加定義 */
#define PROTO			/* プロトタイプ宣言が有効 */
#undef NORENAME			/* rename 関数がない時に定義します。 */
#define NEED_INCREMENTAL_INDICATOR
#define NO_INODE
#define MULTIBYTE_CHAR
#define JAPAN_DATE		/* 日付を YY/MM/DD HH:MM にする */

#if defined(__BORLANDC__) || defined(_MSC_VER)
#define __STDC__	1
#define WIN32	1
#define MSDOS	1
#endif
