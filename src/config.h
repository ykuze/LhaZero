/*
 * LHa for UNIX ver 1.14i �R���t�B�O���[�V���� (Makefile, SWITCHES�}�N���Q��)
 *
 * �@��ˑ��}�N���́AMACHINES �t�@�C���ɐݒ�Ⴊ����܂��̂ŎQ�Ɗ肢�܂��B
 */
/*
 *	Windows 95/98/Me �� DOS ���œ��� lha 
 *	�g�p�R���p�C�� BORLAND C++ 5.01
 */
/* �@���ˑ��̃}�N�� */

#undef NEED_INCREMENTAL_INDICATOR	/* �o�ߕ\���O���t��\������悤�ɂ��܂��B */
#undef EUC				/* �����R�[�h�ϊ����s�Ȃ� e �I�v�V������p�ӂ��܂��B */
#undef ARCHIVENAME_EXTENTION		/* �f�t�H���g�̃A�[�J�C�u�g���q�B�f�t�H���g�� ".lzh" �B */
#undef BACKUPNAME_EXTENTION		/* �o�b�N�A�b�v�A�[�J�C�u�̊g���q�B�f�t�H���g�� ".bak" �B */
#define TMP_FILENAME_TEMPLATE "lhXXXXXX" /* ��ƃt�@�C���̃e���v���[�g�B */
#define SUPPORT_LH7			/* -lh7- method���T�|�[�g����Ƃ��ɒ�`���܂��B*/

/* �@��ˑ��}�N�� */

/* --�C���N���[�h�t�@�C���֌W */
#define USG			/* <strings.h> ���Ȃ��Ƃ��ɒ�`���܂��B */
#define SYSTIME_HAS_NO_TM	/* <sys/time.h> �� struct tm ���Ȃ��Ƃ��ɒ�`���܂��B */

/* --������֌W */
#define NOBSTRING		/* bstring(3) ���Ȃ��Ƃ��ɒ�`���܂��B */
#define NOINDEX			/* index(3) ���Ȃ��Ƃ��ɒ�`���܂��B */
#undef NOSTRDUP			/* strdup(3) ���Ȃ��Ƃ��ɒ�`���܂��B */
#undef USESTRCASECMP		/* strcasecmp(3) ������Ƃ��ɒ�`���܂��B */
#undef NOMEMSET			/* memset(3)���Ȃ��Ƃ��ɒ�`���܂��B */

/* --timezone ���̎擾�֌W */
#define FTIME			/* ftime(3C) ���g�p�����ϊ����s�Ȃ����ɒ�`���܂��B */
#undef GETTIMEOFDAY		/* gettimeofday(2) ���g�p�����ϊ����s�Ȃ����ɒ�`���܂��B */
#define MKTIME			/* mktime(3C) ���g�p�����ϊ����s�Ȃ����ɒ�`���܂��B */
#undef TIMELOCAL		/* timelocal(3V) ���g�p�����ϊ����s�Ȃ����ɒ�`���܂��B */
#undef TZSET			/* tzset(3C) ���g�p�����ϊ����s�Ȃ����ɒ�`���܂��B */
#undef TIMEZONE_HOOK

/* --�f�B���N�g������֌W */
#undef NONSYSTEM_DIR_LIBRARY	/* �f�B���N�g������֐�(opendir,readdir,closedir)�� */
				/* �Ȃ��Ƃ��ɒ�`���܂��BMakefile �� LIBRARYOBJS �� */
				/* lhdir$(O) ��ǉ����Ă��������B */
#if __BORLANDC__
#define SYSV_SYSTEM_DIR		/* struct dirent (direct �ł͂Ȃ�)������Ƃ��ɒ�`���܂��B */
#undef NODIRECTORY		/* ��L�}�N�����g�p���Ă����s���鎞�ɒ�`���܂��B */
#endif /* __BORLANDC__ */
#if _MSC_VER
#undef SYSV_SYSTEM_DIR		/* struct dirent (direct �ł͂Ȃ�)������Ƃ��ɒ�`���܂��B */
#define NODIRECTORY		/* ��L�}�N�����g�p���Ă����s���鎞�ɒ�`���܂��B */
#endif /* _MSC_VER */

/* --���̑� */
#define NOFTRUNCATE		/* ftruncate(2) ���Ȃ����ɒ�`���܂��B */
#undef NOMKDIR			/* mkdir(2) ���Ȃ��Ƃ��ɒ�`���܂��B */
#undef MKDIRPATH		/* mkdir �̊O���R�}���h�����`���܂��BNOMKDIR �� */
				/* �����ɋ@�\���܂��B�f�t�H���g�� "/bin/mkdir" �ł��B */
#undef RMDIRPATH		/* rmdir �̊O���R�}���h�����`���܂��BNOMKDIR �� */
				/* �����ɋ@�\���܂��B�f�t�H���g�� "/bin/rmdir" �ł��B */
#define NOT_COMPATIBLE_MODE
#undef HAVE_NO_LCHOWN		/* lchown(2)�������Ƃ��ɒ�`���܂� */

/* �ǉ���` */
#define PROTO			/* �v���g�^�C�v�錾���L�� */
#undef NORENAME			/* rename �֐����Ȃ����ɒ�`���܂��B */
#define NEED_INCREMENTAL_INDICATOR
#define NO_INODE
#define MULTIBYTE_CHAR
#define JAPAN_DATE		/* ���t�� YY/MM/DD HH:MM �ɂ��� */

#if defined(__BORLANDC__) || defined(_MSC_VER)
#define __STDC__	1
#define WIN32	1
#define MSDOS	1
#endif
