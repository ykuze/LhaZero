//---------------------------------------------------------------------------

#ifndef Msg_uH
#define Msg_uH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
#ifdef _DEBUG
  #define DBGLOG      "c:\\tmp\\dbg.log"
  extern TStringList *LogSl;
#endif

class TMsgForm : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TMemo *MsgMemo;
	void __fastcall FormCreate(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
	__fastcall TMsgForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMsgForm *MsgForm;
//---------------------------------------------------------------------------
#endif
