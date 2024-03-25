//---------------------------------------------------------------------------

#ifndef Msg_uH
#define Msg_uH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
#ifdef _DEBUG
  #define DBGLOG      "c:\\tmp\\dbg.log"
  extern TStringList *LogSl;
#endif

class TMsgForm : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TLabel *MsgOldLb;
	TLabel *MsgLb;
	TLabel *CntLb;
	void __fastcall FormCreate(TObject *Sender);
private:	// ユーザー宣言
    int FCnt;
public:		// ユーザー宣言
	__fastcall TMsgForm(TComponent* Owner);
	void msg(String str);
};
//---------------------------------------------------------------------------
extern PACKAGE TMsgForm *MsgForm;
//---------------------------------------------------------------------------
#endif
