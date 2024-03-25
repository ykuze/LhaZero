//---------------------------------------------------------------------------

#include <vcl.h>
#include "LhaZeroMain.h"
#pragma hdrstop

#include "Msg_u.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMsgForm *MsgForm;
//---------------------------------------------------------------------------
__fastcall TMsgForm::TMsgForm(TComponent* Owner)
	: TForm(Owner)
{
	FCnt = 0;
	MsgOldLb->Caption = "";
	MsgLb->Caption = "";
}
//---------------------------------------------------------------------------
void __fastcall TMsgForm::FormCreate(TObject *Sender)
{
	int subver;

	subver  = VERSION % 100;
	Caption = Caption + "  " + IntToStr(VERSION / 100)+"."+IntToStr(subver / 10)+IntToStr(subver % 10);
}
//---------------------------------------------------------------------------
void TMsgForm::msg(String str)
{
	int i, st, len;
#ifdef _DEBUG
	LogSl->Add("---------------");
	LogSl->Add(str);
	LogSl->SaveToFile(DBGLOG);
#endif
	len = str.Length();
	// æ“ª‚Ì\rˆ—
	if ((len>0) && (str[1] == '\r'))  st = 2;
	else                              st = 1;

	// ––”ö‚Ì‰üsíœ
	if ((len+1-st >= 2) && (str[len-1] == '\r') && (str[len] == '\n')) {
		str = str.SubString(st, len+1-st-2);
		FCnt++;
	} else
		str = str.SubString(st, len+1-st);
#ifdef _DEBUG
	LogSl->Add("---------------");
	LogSl->Add(str);
	LogSl->SaveToFile(DBGLOG);
#endif

	if (st == 1)  MsgLb->Caption = MsgLb->Caption + str;
	else {
		if ((MsgLb->Caption != "") && (MsgLb->Caption[MsgLb->Caption.Length()] != '.'))
			MsgOldLb->Caption = MsgLb->Caption;
		MsgLb->Caption = str;             // \r‚ÅŽn‚Ü‚é‚Æ‚«
	}
	CntLb->Caption = "Count : " + IntToStr(FCnt);
#ifdef _DEBUG
	LogSl->Add(IntToStr(st));
	LogSl->Add(MsgLb->Caption);
	LogSl->Add(CntLb->Caption);
	LogSl->SaveToFile(DBGLOG);
#endif
	Application->ProcessMessages();
#ifdef _DEBUG
	LogSl->Add("ProcessMessages");
	LogSl->SaveToFile(DBGLOG);
#endif
}
//---------------------------------------------------------------------------


