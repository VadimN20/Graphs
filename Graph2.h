//---------------------------------------------------------------------------

#ifndef Graph2H
#define Graph2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TFormSizeVer : public TForm
{
__published:	// IDE-managed Components
	TLabel *LabelEnterSize;
	TEdit *EditSizeVer;
	TButton *ButtonOkClose;
	TLabel *LabelNumSize;
	void __fastcall EditSizeVerKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ButtonOkCloseClick(TObject *Sender);

private:	// User declarations
    bool checkOk;
public:		// User declarations
	__fastcall TFormSizeVer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSizeVer *FormSizeVer;
//---------------------------------------------------------------------------
#endif
