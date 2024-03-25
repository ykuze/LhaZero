//   DLL �Ń����^�C�� ���C�u�����̐ÓI�o�[�W�������g�p����ꍇ��
//   DLL �������Ǘ��Ɋւ���d�v�ȃ���:
//
//   �p�����[�^�܂��͊֐����ʂƂ��� String �I�u�W�F�N�g (�܂��̓l�X�g����
//   String ���܂܂�Ă���\���̂�N���X) ��n���֐��� DLL �ŃG�N�X�|�[�g����
//   �ꍇ�́ADLL �v���W�F�N�g�ɂ����� DLL ���g�p���鑼�̂�����v���W�F�N�g�ɂ�
//   ���C�u���� MEMMGR.LIB ��ǉ�����K�v������܂��B�܂��A���� DLL ���g�p����
//   ���̃v���W�F�N�g�ŁADLL ����G�N�X�|�[�g����� TObject �h���łȂ��C�ӂ�
//   �N���X�ɑ΂��� new ���Z�܂��� delete ���Z�����s����ꍇ���AMEMMGR.LIB ��
//   �g�p����K�v������܂��B�v���W�F�N�g�� MEMMGR.LIB ��ǉ�����ƁADLL �Ƃ���
//   �Ăяo������ EXE �������� �}�l�[�W���Ƃ��� BORLNDMM.DLL ���g�p����悤��
//   �Ȃ�܂��B�����̏ꍇ�ABORLNDMM.DLL �t�@�C�����쐬�Ώۂ� DLL �ƈꏏ�ɔz�u
//   ���Ȃ���΂Ȃ�܂���B
//
//   BORLNDMM.DLL ���g�p���Ȃ��悤�ɂ���ɂ́A"char *" �^�܂��� 
//   ShortString �^�̃p�����[�^���g���ĕ��������n���܂��B
//
//   DLL �� RTL �̓��I�o�[�W�������g�p����ꍇ�AMEMMGR.LIB �͈Öق�
//   �ǉ�����邽�߁A�����I�ɒǉ�����K�v�͂���܂���B

#include <vcl.h>
#include <windows.h>
#include <libloaderapi.h>
#include <Vcl.Themes.hpp>
//#include <winuser.h>
#include <Classes.hpp>
#include <System.SysUtils.hpp>
#include <string.h>
#include <winbase.h>
#include "LhaZeroMain.h"
#include "Msg_u.h"
#include "lha.h"

#pragma hdrstop
#pragma argsused

#ifdef _DEBUG
TStringList *LogSl;
#endif
HWND OwnerHandle;
HARC FHarc;
char _MprintBuf[BUFSIZ];
static Int64    packed_size_total;
static Int64    original_size_total;
static int      list_files;
TList *arc_list;
static int      arc_count;
static char fname_bak[FILENAME_LENGTH];
static LzHeader hdr;

//-----------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	int i;
	TStyleManager::TStyleServicesHandle  VclH;

	// Perform actions based on the reason for calling.
	switch( reason )
	{
	  case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.

		//DLL�̃v���Z�X�������̏���
#ifdef _DEBUG
		LogSl     = new TStringList;
		LogSl->Add("DLL_PROCESS_ATTACH");
		LogSl->SaveToFile(DBGLOG);
#endif
		//Wild      = NULL;
		arc_list = new TList();
		FHarc    = 0;

		//----------------------------------------------------

#if 0
		//���\�[�X����VCL�X�^�C���̏����擾���ăZ�b�g
		if (FindResourceW(HInstance, L"CharcoalDark", L"VCLSTYLE") != 0) {
#ifdef _DEBUG
			LogSl->Add("FindResourceW(HInstance, L\"CharcoalDark\", L\"VCLSTYLE\") != 0");
			LogSl->SaveToFile(DBGLOG);
#endif
			if (TStyleManager::TryLoadFromResource((NativeUInt)HInstance, (WideChar*)L"CharcoalDark", (WideChar*)L"VCLSTYLE", VclH)) {  // ��肭�����Ȃ�
#ifdef _DEBUG
			  LogSl->Add("  TStyleManager::TryLoadFromResource((NativeUInt)HInstance, L\"CharcoalDark\", L\"VCLSTYLE\", VclH)");
			  LogSl->SaveToFile(DBGLOG);
#endif
			  if (VclH != NULL) {
#ifdef _DEBUG
				LogSl->Add("    TStyleManager::SetStyle(VclH);");
				LogSl->SaveToFile(DBGLOG);
#endif
				TStyleManager::SetStyle(VclH);
			  }
			}
		}
/*
#ifdef _DEBUG
		LogSl->SaveToFile(DBGLOG);
#endif
*/
#endif

		break;

	  case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
/*
#ifdef _DEBUG
		LogSl->Add("DLL_PROCESS_DETACH");
		LogSl->SaveToFile(DBGLOG);
#endif
*/
		//ZipMaster->Free;
		Application->Handle = 0;
/*
#ifdef _DEBUG
		LogSl->Free;
#endif
*/
		break;

	  case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;

	  case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		clear_arclist();
		delete arc_list;
		break;
	}
	return 1;   // Successful DLL_PROCESS_ATTACH.
}

void clear_arclist(void)
{
	int i;

	for(i=0; i<arc_list->Count; i++) {
		delete (LPINDIVIDUALINFOA)(arc_list->Items[i]);
	}
}

void TimetToFileTime(time_t t, LPFILETIME pft)
{
    ULARGE_INTEGER time_value;
    time_value.QuadPart = (t * 10000000LL) + 116444736000000000LL;
    pft->dwLowDateTime = time_value.LowPart;
    pft->dwHighDateTime = time_value.HighPart;
}

/*
void TimetToFileTime(time_t t, LPFILETIME pft)
{
	LONGLONG time_value = Int32x32To64(t, 10000000) + 116444736000000000;
	pft->dwLowDateTime = (DWORD) time_value;
	pft->dwHighDateTime = time_value >> 32;
}
*/

//-----------------------------------------------------------------
/*
  �Ή��R�}���h

  LHA.DLL �݊� API
	(LhaZero)�R�}���h���C��
	GetVersion
  SetOwnerWindow() �n API �̐���
	SetOwnerWindow
	ClearOwnerWindow
  OpenArchive �n API
	FOpenArchiveA     : TPkOpenArchiveW;
	FCloseArchive     : TPkCloseArchive;
	FFindFirstA       : TPkFindFirstW;
	FFindNextA        : TPkFindNextW;
	FGetFileNameA     : TPkGetFileNameW;
	FGetWriteTimeEx   : TPkGetWriteTimeEx;
	FGetAttribute     : TPkGetAttribute;
*/

// CmdLine
//     [<command>] [[-<switch>[+|-|0|1|2]]...] <archive_file_name>[.LZH]
//	[[<base_directory_name>\] [<path_name>|<wild_name>]...]]...
int WINAPI LhaZero(
		HWND		_hwnd,
		LPCSTR		_szCmdLine,
		LPSTR		_szOutput,
		const DWORD	_dwSize
	)
{
	int i, j, k;
	char *p;        /* ����U��ꂽ�̈�̃A�h���X���i�[���邽�߂̃|�C���^p��錾 */
	char** arg;
	AnsiString AStr;
	TStringList *Sl;
	RECT  ARect;
	AnsiString ResFName = "";

#ifdef _DEBUG
	LogSl->Add((AnsiString)"LhaZero(" +_szCmdLine+")");
	LogSl->SaveToFile(DBGLOG);
#endif
	MsgForm = new TMsgForm(Application);
	Sl      = new TStringList();
	try {
		GetWindowRect(Application->Handle, &ARect);
		MsgForm->Left = (ARect.left+ARect.right- MsgForm->Width) / 2;
		if (MsgForm->Left<0)  MsgForm->Left = 0;
		MsgForm->Top  = ARect.top;
		MsgForm->FormStyle = fsStayOnTop;
		MsgForm->Show();
		Sl->Delimiter = ' ';
		Sl->QuoteChar = '"';
		Sl->DelimitedText = _szCmdLine;
		Sl->Insert(0, (AnsiString)"LhaZero");
#ifdef _DEBUG
		for(i=0; i<Sl->Count; i++) {
			LogSl->Add((AnsiString)"  "+Sl->Strings[i]);
		}
		LogSl->SaveToFile(DBGLOG);
#endif
		if (Sl->Count<2)  return(-1);
		arg = (char **)malloc( sizeof(char*)*Sl->Count );
		for(i = 0, j = 0; i < Sl->Count; i++) {
			AStr = Sl->Strings[i];
			p = (char*)malloc(AStr.Length() +1);  /* �������̈�̊m�� */
			strcpy(p, AStr.c_str());
			if ((i>2) && (base_directory==NULL) && (AStr[AStr.Length()]=='\\')) {
#ifdef _DEBUG
				LogSl->Add((AnsiString)"  AStr=" +AStr+", AStr["+IntToStr(AStr.Length())+"]="+AStr[AStr.Length()]);
				LogSl->SaveToFile(DBGLOG);
#endif
				base_directory = p;
			} else if ((i>2) && (ResFName=="") && (AStr[1]=='@')) {
				ResFName = AStr.SubString(2, AStr.Length());
#ifdef _DEBUG
				LogSl->Add((AnsiString)"  ResFName=" +ResFName);
				LogSl->SaveToFile(DBGLOG);
#endif
			} else {
				arg[j] = p;
				j++;
			}
		}
#ifdef _DEBUG
		LogSl->Add((AnsiString)"  base_directory = "+AnsiString(base_directory));
#endif
		if (ResFName!="") {
			Sl->Clear();
			Sl->QuoteChar = '"';
			Sl->LoadFromFile(ResFName);
			for(k=0; k<Sl->Count; k++) {
				AStr = (AnsiString)(Sl->Strings[k]);
				if (AStr[1]=='"') AStr = AStr.SubString(2, AStr.Length()-2);
				arg[j] = AStr.c_str();
#ifdef _DEBUG
				LogSl->Add("");
				for(i=0; i<j+1; i++) {
					LogSl->Add((AnsiString)"  "+AnsiString(arg[i]));
				}
				LogSl->SaveToFile(DBGLOG);
#endif
				main(j+1, arg);
			}
		} else {
#ifdef _DEBUG
			LogSl->Add("");
			for(i=0; i<j; i++) {
				LogSl->Add((AnsiString)"  "+AnsiString(arg[i]));
			}
			LogSl->SaveToFile(DBGLOG);
#endif
			main(j, arg);
		}
	}
	__finally {
#ifdef _DEBUG
		LogSl->Add("  __finally");
		LogSl->SaveToFile(DBGLOG);
#endif
		for(i = 0; i < j; i++)
			free(arg[i]);
		free(arg);
		Sl->Free();
		MsgForm->Free();
		if (base_directory!=NULL) {
			free(base_directory);
			base_directory = NULL;
		}
	}

	return(0);
}

WORD WINAPI LhaZeroGetVersion( VOID )
{
  return(VERSION);
}

//-----------------------------------------------------------------
/*
�@�\
	.DLL �̃��b�Z�[�W�̑��M��E�B���h�E��ݒ肵�܂��B
  .DLL �͂����Ŏw�肳�ꂽ�E�B���h�E�Ƀ��b�Z�[�W�𑗐M���܂��B
*/
BOOL WINAPI LhaZeroSetOwnerWindow(const HWND _hwnd)
{
#ifdef _DEBUG
	LogSl->Add((AnsiString)"LhaZeroSetOwnerWindow("+IntToStr((int)_hwnd)+")");
	LogSl->SaveToFile(DBGLOG);
#endif
	Application->Handle = _hwnd;
	OwnerHandle = _hwnd;
	return(true);
}

BOOL WINAPI LhaZeroClearOwnerWindow()
{
#ifdef _DEBUG
	LogSl->Add("LhaZeroClearOwnerWindow()");
	LogSl->SaveToFile(DBGLOG);
#endif
	OwnerHandle = 0;
	return(true);
}

//-----------------------------------------------------------------
/*
  dwMode: ��Ή�
*/
HARC WINAPI LhaZeroOpenArchive(	HWND _hwnd, LPCSTR _szFileName, const DWORD	_dwMode)
{
	FILE            *afp;

#ifdef _DEBUG
	LogSl->Add((AnsiString)"LhaZeroOpenArchive("+_szFileName+", "+IntToHex((Int8)_dwMode)+")");
	LogSl->SaveToFile(DBGLOG);
#endif
	Application->Handle = _hwnd;

	//if (_harc!=FHarc)  return ERROR_HARC_ISNOT_OPENED;

	/* open archive file */
	strcpy(fname_bak, _szFileName);
	archive_name = fname_bak;
	if ((afp = open_old_archive()) == NULL) {
		error(archive_name, (char*)"");
		FHarc = 0;
		return FHarc;
	}
	if (archive_is_msdos_sfx1(archive_name))
		skip_msdos_sfx1_code(afp);
	OwnerHandle = _hwnd;
	arc_count = -1;

	FHarc  = (HARC)afp;
#ifdef _DEBUG
	LogSl->Add((AnsiString)"  FHarc"+IntToStr((int)FHarc));
	LogSl->SaveToFile(DBGLOG);
#endif
	return FHarc;
}

int WINAPI LhaZeroCloseArchive(HARC	_harc)
{
	FILE            *afp;

#ifdef _DEBUG
	LogSl->Add("LhaZeroCloseArchive()");
	LogSl->SaveToFile(DBGLOG);
#endif
	/* close archive file */
	afp   = (FILE*)_harc;
	FHarc = 0;
	return fclose(afp);
}

// ���Farc_count�X�V�����
int WINAPI GetIvInfo(HARC _harc, PINDIVIDUALINFO _lpSubInfo)
{
	FILE            *afp;
	time_t          tm;
	FILETIME        ftime;

#ifdef _DEBUG
	LogSl->Add("  GetIvInfo("+IntToStr((int)_harc)+")");
	LogSl->SaveToFile(DBGLOG);
#endif
	afp = (FILE*)_harc;

	/* get each file information */
	if (get_header(afp, &hdr)) {
		_lpSubInfo->dwOriginalSize   = hdr.original_size;
		_lpSubInfo->dwCompressedSize = hdr.packed_size;
		_lpSubInfo->dwCRC            = hdr.crc;
		_lpSubInfo->uFlag            = hdr.has_crc;
		_lpSubInfo->uOSType          = hdr.extend_type;
		if (hdr.original_size>0)
			_lpSubInfo->wRatio       = hdr.packed_size * 1000 / hdr.original_size;
		else
			_lpSubInfo->wRatio       = 0;
		TimetToFileTime(hdr.unix_last_modified_stamp, &ftime);
		FileTimeToDosDateTime(&ftime, &_lpSubInfo->wDate, &_lpSubInfo->wTime);
		strcpy(_lpSubInfo->szFileName, hdr.name);
		if (hdr.attribute & FA_RDONLY) _lpSubInfo->szAttribute[0] = 'R';  else _lpSubInfo->szAttribute[0] = '-';
		if (hdr.attribute & FA_HIDDEN) _lpSubInfo->szAttribute[1] = 'H';  else _lpSubInfo->szAttribute[1] = '-';
		if (hdr.attribute & FA_SYSTEM) _lpSubInfo->szAttribute[2] = 'S';  else _lpSubInfo->szAttribute[2] = '-';
		if (hdr.attribute & FA_ARCH)   _lpSubInfo->szAttribute[3] = 'A';  else _lpSubInfo->szAttribute[3] = '-';
		if (hdr.attribute & FA_LABEL)  _lpSubInfo->szAttribute[4] = 'L';  else _lpSubInfo->szAttribute[4] = '-';
		if (hdr.unix_mode & UNIX_FILE_DIRECTORY)  hdr.attribute |= FA_DIREC;                  // �X�V
		if (hdr.attribute & FA_DIREC)  _lpSubInfo->szAttribute[5] = 'D';  else _lpSubInfo->szAttribute[5] = '-';
		_lpSubInfo->szAttribute[6] = '\0';
		_lpSubInfo->szAttribute[7] = '\0';
		strcpy(_lpSubInfo->szMode, hdr.method);
		packed_size_total += hdr.packed_size;
		original_size_total += hdr.original_size;
		arc_count++;
		fseek(afp, hdr.packed_size, SEEK_CUR);
#ifdef _DEBUG
		LogSl->Add("    name=" + String(hdr.name) + ", size=" + IntToStr((int)_lpSubInfo->dwOriginalSize) + ", attr=" + String(_lpSubInfo->szAttribute));
		LogSl->Add("    arc_count=" + IntToStr(arc_count));
		LogSl->SaveToFile(DBGLOG);
#endif
	} else {
		return -1;
	}
	return arc_count;
}

int WINAPI LhaZeroFindFirst(HARC _harc, LPCSTR _szWildName, INDIVIDUALINFOA *_lpSubInfo)
{
#ifdef _DEBUG
	LogSl->Add((AnsiString)"LhaZeroFindFirst("+_szWildName+")");
	LogSl->SaveToFile(DBGLOG);
#endif

	if (_harc!=FHarc)  return ERROR_HARC_ISNOT_OPENED;

	/* initialize total count */
	packed_size_total = 0L;
	original_size_total = 0L;
	list_files = 0;

	arc_count = 0;
	if (GetIvInfo(_harc, _lpSubInfo)>=0)  return 0;
	else                                  return -1;
}

int WINAPI LhaZeroFindNext(HARC _harc, INDIVIDUALINFOA	*_lpSubInfo)
{
#ifdef _DEBUG
	LogSl->Add("LhaZeroFindNext()");
	LogSl->SaveToFile(DBGLOG);
#endif

	if (_harc!=FHarc)  return ERROR_HARC_ISNOT_OPENED;

	if (GetIvInfo(_harc, _lpSubInfo)>=0)  return 0;
	else                                  return -1;
}

int WINAPI LhaZeroGetFileName(HARC _harc, LPSTR _lpBuffer, const int	_nSize)
{
	AnsiString S;

#ifdef _DEBUG
	LogSl->Add((AnsiString)"LhaZeroGetFileName("+IntToStr(_nSize)+")");
	LogSl->SaveToFile(DBGLOG);
#endif
	if (_harc!=FHarc)  return ERROR_HARC_ISNOT_OPENED;

	S = ExcludeTrailingPathDelimiter(String(hdr.name));
#ifdef _DEBUG
	LogSl->Add((AnsiString)"  FileName="+S);
	LogSl->SaveToFile(DBGLOG);
#endif
	strncpy(_lpBuffer, S.c_str(), _nSize);

	return 0;
}

BOOL WINAPI LhaZeroGetWriteTimeEx(HARC _harc, FILETIME *_lpftLastWriteTime)
{
	FILETIME LocalFileTime;

#ifdef _DEBUG
	LogSl->Add("LhaZeroGetWriteTimeEx()");
	LogSl->SaveToFile(DBGLOG);
#endif
	if (_harc!=FHarc)  return ERROR_HARC_ISNOT_OPENED;

	TimetToFileTime(hdr.unix_last_modified_stamp, _lpftLastWriteTime);
#ifdef _DEBUG
	LogSl->Add("  last_modified_stamp  ="+IntToHex((Int8)hdr.last_modified_stamp, 4));
	LogSl->Add("  unix_last_modified_stamp  ="+IntToHex((Int8)hdr.unix_last_modified_stamp, 8));
	LogSl->Add("  DTtoFDate  ="+IntToHex(*(Int8*)_lpftLastWriteTime, 8));
	LogSl->SaveToFile(DBGLOG);
#endif

	return TRUE;
}

int WINAPI LhaZeroGetAttribute(HARC	_harc)
{
#ifdef _DEBUG
	LogSl->Add("LhaZeroGetAttribute()");
	LogSl->SaveToFile(DBGLOG);
#endif
	if (_harc!=FHarc)  return ERROR_HARC_ISNOT_OPENED;

#ifdef _DEBUG
	LogSl->Add("  attribute="+IntToHex(hdr.attribute, 8));
	LogSl->SaveToFile(DBGLOG);
#endif

	return hdr.attribute;
}


