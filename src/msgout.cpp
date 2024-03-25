//---------------------------------------------------------------------------

//#pragma hdrstop

//#include <stdarg.h>
#include <vcl.h>
#include <stdio.h>
#include <windows.h>
#include "Msg_u.h"
#include "msgout.h"
//---------------------------------------------------------------------------
//#pragma package(smart_init)

int mprintf(const char *fmt)
{
#ifdef _DEBUG
	LogSl->Add(String(fmt));
	LogSl->SaveToFile(DBGLOG);
#endif
	//MsgForm->MsgMemo->SelText = String(fmt);
	MsgForm->msg(String(fmt));
	//Application->ProcessMessages();
}

