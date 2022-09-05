//---------------------------------------------------------------------------

#ifndef GraphH
#define GraphH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.FileCtrl.hpp>

#include <vector>
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
class TFormGraphs : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *ButtonAdjacency;
	TPanel *PanelDefault;
	TEdit *EditVertex;
	TLabel *LabelCountVertex;
	TButton *ButtonCreateMatrix;
	TButton *ButtonAddVertex;
	TButton *ButtonClear;
	TStringGrid *StringGrid;
	TButton *ButtonCreateGraph;
	TPaintBox *PaintBox;
	TMenuItem *ButtonFile;
	TMenuItem *ButtonInFile;
	TMenuItem *ButtonOutFile;
	TButton *PaintAddVertex;
	TButton *PaintConnectVertices;
	TButton *PaintDelVertex;
	TButton *ButtonBack;
	void __fastcall ButtonAdjacencyClick(TObject *Sender);
	void __fastcall ButtonCreateMatrixClick(TObject *Sender);
	void __fastcall ButtonAddVertexClick(TObject *Sender);
	void __fastcall ButtonClearClick(TObject *Sender);
	void __fastcall ButtonCreateGraphClick(TObject *Sender);
	void __fastcall PaintBoxMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall ButtonInFileClick(TObject *Sender);
	void __fastcall ButtonOutFileClick(TObject *Sender);
	//ƒобавление, соединение и удаление вершин
	void __fastcall PaintAddVertexClick(TObject *Sender);
	void __fastcall PaintConnectVerticesClick(TObject *Sender);
	void __fastcall PaintDelVertexClick(TObject *Sender);
	void __fastcall ButtonBackClick(TObject *Sender);

private:	// User declarations
	int VertexCount;
	bool Create_Graph;
	bool Create_Matrix;
	bool Create_PaintGraph;
	bool IfStartPaint;
	int k;
	int xMat, yMat;
	int StartP;

public:		// User declarations
	int minusXcor;
	int minusYcor;
	__fastcall TFormGraphs(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormGraphs *FormGraphs;
//---------------------------------------------------------------------------
#endif
