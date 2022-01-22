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
}
//---------------------------------------------------------------------------
void __fastcall TMsgForm::FormCreate(TObject *Sender)
{
	int subver;

	subver  = VERSION % 100;
	Caption = Caption + "  " + IntToStr(VERSION / 100)+"."+IntToStr(subver / 10)+IntToStr(subver % 10);
}
//---------------------------------------------------------------------------

