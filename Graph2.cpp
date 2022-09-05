//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Graph2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSizeVer *FormSizeVer;
//---------------------------------------------------------------------------
__fastcall TFormSizeVer::TFormSizeVer(TComponent* Owner)
	: TForm(Owner)
{
	FormSizeVer->BorderStyle = bsDialog;
	checkOk = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormSizeVer::EditSizeVerKeyPress(TObject *Sender, System::WideChar &Key)

{
	if((Key < '0' || Key > '9') && Key != VK_BACK) {
		LabelNumSize->Visible = true;
		Key = 0;
	}
	else {
		LabelNumSize->Visible = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSizeVer::ButtonOkCloseClick(TObject *Sender)
{
	if(EditSizeVer->Text != "") {
		FormSizeVer->Close();
	}
	else {
		LabelNumSize->Visible = true;
	}
}
//---------------------------------------------------------------------------

