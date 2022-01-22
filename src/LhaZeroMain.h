//---------------------------------------------------------------------------

#ifndef LhaZeroMainH
#define LhaZeroMainH
//---------------------------------------------------------------------------

#define VERSION         1       // 0.01
#define FNAME_MAX32		512

#ifndef FA_RDONLY
/* Attribute */
#define FA_RDONLY       0x01            /* 書き込み保護属性 */
#define FA_HIDDEN       0x02            /* 隠し属性 */
#define FA_SYSTEM       0x04            /* システム属性 */
#define FA_LABEL        0x08            /* ボリューム・ラベル */
#define FA_DIREC        0x10            /* ディレクトリ */
#define FA_ARCH         0x20            /* アーカイブ属性 */
#endif

#if !defined(SFXFLAG_AUTO)
#define SFXFLAG_AUTO			1
#define SFXFLAG_OVERWRITE		2
#define SFXFLAG_CHECKCRC		4
#define SFXFLAG_CHECKTIME		8
#endif

#if !defined(ERROR_START)
#define ERROR_START				0x8000
/* WARNING */
#define ERROR_DISK_SPACE		0x8005
#define ERROR_READ_ONLY			0x8006
#define ERROR_USER_SKIP			0x8007
#define ERROR_UNKNOWN_TYPE		0x8008
#define ERROR_METHOD			0x8009
#define ERROR_PASSWORD_FILE		0x800A
#define ERROR_VERSION			0x800B
#define ERROR_FILE_CRC			0x800C
#define ERROR_FILE_OPEN			0x800D
#define ERROR_MORE_FRESH		0x800E
#define ERROR_NOT_EXIST			0x800F
#define ERROR_ALREADY_EXIST		0x8010

#define ERROR_TOO_MANY_FILES	0x8011

/* ERROR */
#define ERROR_MAKEDIRECTORY		0x8012
#define ERROR_CANNOT_WRITE		0x8013
#define ERROR_HUFFMAN_CODE		0x8014
#define ERROR_COMMENT_HEADER	0x8015
#define ERROR_HEADER_CRC		0x8016
#define ERROR_HEADER_BROKEN		0x8017
#define ERROR_ARC_FILE_OPEN		0x8018
#define ERROR_NOT_ARC_FILE		0x8019
#define ERROR_CANNOT_READ		0x801A
#define ERROR_FILE_STYLE		0x801B
#define ERROR_COMMAND_NAME		0x801C
#define ERROR_MORE_HEAP_MEMORY	0x801D
#define ERROR_ENOUGH_MEMORY		0x801E
#if !defined(ERROR_ALREADY_RUNNING)
#define ERROR_ALREADY_RUNNING	0x801F
#endif
#define ERROR_USER_CANCEL		0x8020
#define ERROR_HARC_ISNOT_OPENED	0x8021
#define ERROR_NOT_SEARCH_MODE	0x8022
#define ERROR_NOT_SUPPORT		0x8023
#define ERROR_TIME_STAMP		0x8024
#define ERROR_TMP_OPEN			0x8025
#define ERROR_LONG_FILE_NAME	0x8026
#define ERROR_ARC_READ_ONLY		0x8027
#define ERROR_SAME_NAME_FILE	0x8028
#define ERROR_NOT_FIND_ARC_FILE 0x8029
#define ERROR_RESPONSE_READ		0x802A
#define ERROR_NOT_FILENAME		0x802B
#define ERROR_TMP_COPY			0x802C
#define ERROR_EOF				0x802D
#define ERROR_ADD_TO_LARC		0x802E
#define ERROR_TMP_BACK_SPACE	0x802F
#define ERROR_SHARING			0x8030
#define ERROR_NOT_FIND_FILE		0x8031
#define ERROR_LOG_FILE			0x8032
#define	ERROR_NO_DEVICE			0x8033
#endif /* ERROR_START */

typedef int				_Boolean;
typedef	HGLOBAL	HARC;

typedef struct {
	DWORD 			dwOriginalSize;		/* ファイルのサイズ */
	DWORD 			dwCompressedSize;	/* 圧縮後のサイズ */
	DWORD			dwCRC;				/* 格納ファイルのチェックサム */
	UINT			uFlag;				/* 処理結果 */
										/* Status flag */
	UINT			uOSType;			/* 書庫作成に使われた OS */
	WORD			wRatio;				/* 圧縮率 */
	WORD			wDate;				/* 格納ファイルの日付(DOS 形式) */
	WORD 			wTime;				/* 格納ファイルの時刻(〃) */
	char			szFileName[FNAME_MAX32 + 1];	/* 格納ファイル名 */
	char			dummy1[3];
	char			szAttribute[8];		/* 格納ファイルの属性(書庫固有) */
	char			szMode[8];			/* 格納ファイルの格納モード(〃) */
}	INDIVIDUALINFOA, *LPINDIVIDUALINFOA;

typedef INDIVIDUALINFOA    INDIVIDUALINFO;
typedef LPINDIVIDUALINFOA  PINDIVIDUALINFO;

extern HWND OwnerHandle;

extern "C" {

WORD
WINAPI __declspec(dllexport)
LhaZeroGetVersion(
		VOID
	);

int
WINAPI __declspec(dllexport)
LhaZero(
		HWND		_hwnd,
		LPCSTR		_szCmdLine,
		LPSTR		_szOutput,
		const DWORD	_dwSize
	);

BOOL
WINAPI __declspec(dllexport)
LhaZeroSetOwnerWindow(
		const HWND	_hwnd
	);

BOOL
WINAPI __declspec(dllexport)
LhaZeroClearOwnerWindow(
		VOID
	);


HARC
WINAPI __declspec(dllexport)
LhaZeroOpenArchive(
		HWND		_hwnd,
		LPCSTR		_szFileName,
		const DWORD	_dwMode
	);

int
WINAPI __declspec(dllexport)
LhaZeroCloseArchive(
		HARC	_harc
	);
int
WINAPI __declspec(dllexport)
LhaZeroFindFirst(
		HARC			_harc,
		LPCSTR			_szWildName,
		INDIVIDUALINFOA	*_lpSubInfo
	);

int
WINAPI __declspec(dllexport)
LhaZeroFindNext(
		HARC			_harc,
		INDIVIDUALINFOA	*_lpSubInfo
	);

int
WINAPI __declspec(dllexport)
LhaZeroGetFileName(
		HARC		_harc,
		LPSTR		_lpBuffer,
		const int	_nSize
	);

BOOL
WINAPI __declspec(dllexport)
LhaZeroGetWriteTimeEx(
		HARC		_harc,
		FILETIME	*_lpftLastWriteTime
	);

int
WINAPI __declspec(dllexport)
LhaZeroGetAttribute(
		HARC	_harc
	);

}
#endif

void clear_arclist(void);


