//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Graph.h"
#include "Graph2.h"
#include <time.h>
#include <fstream>
#include <iostream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormGraphs *FormGraphs;
//---------------------------------------------------------------------------
int N = 0;
int vertexPaintCt = 10;
int **arr;
int **arrCor;
int **tempArr;
int nCount = 0;
//���������� ��� ���������� ������
int tempI1 = 0, tempI2 = 0, tempDel;

const unsigned radius = 15;
bool ClickVertex = false;
bool ClickLine = false;
bool ClickDelVer = false;


__fastcall TFormGraphs::TFormGraphs(TComponent* Owner)
	: TForm(Owner)
{
	VertexCount = 3;
	k = 0;
	xMat = 0;
	yMat = 0;
	Create_Graph = false;
	Create_Matrix = false;
	Create_PaintGraph = false;
	IfStartPaint = false;
	minusXcor = 3;
	minusYcor = 8;
	StartP = 0;
	srand(time(NULL));
	FormGraphs->BorderStyle = bsSingle;
}
//---------------------------------------------------------------------------


void __fastcall TFormGraphs::ButtonAdjacencyClick(TObject *Sender)
{
	//���������� ���������� StringGrid ��� �������� �� ������ ������ ���� � ������
	VertexCount = 3;
	StringGrid->RowCount = VertexCount;
	StringGrid->ColCount = VertexCount;
	//�������� ����������� ��� ������ � StringGrid ��� ������ � ��������
	StringGrid->Visible = true;
	LabelCountVertex->Visible = true;
	EditVertex->Visible = true;
	ButtonCreateMatrix->Visible = true;
	ButtonCreateGraph->Visible = true;
	ButtonAddVertex->Visible = true;
	ButtonBack->Visible = true;


	PaintAddVertex->Visible = false;
	PaintConnectVertices->Visible = false;
	PaintDelVertex->Visible = false;

	//���� ���������� � ������� ������� �����
	for(int i = 0; i < VertexCount; i++) {
		for(int j = 0; j < VertexCount; j++) {
			if(j == 0) StringGrid->Cells[i][j] = i;
			else if(i == 0) StringGrid->Cells[i][j] = j;
			else StringGrid->Cells[i][j] = 0;
		}
	}
	//������� ������ �� ���� ��������, ���� ��� ���� ��������� ��� ������ �������
	if(Create_Graph || StartP != 0) {
		if(nCount == 0) {
			ShowMessage("Memory is empty!");
		}
		else if(nCount == 20) {
			//��������� ������ �������
			for(int i = 0; i < nCount; i++) { delete [] arr[i]; }
			delete [] arr;
			//��������� ������ ���������
			for(int i = 0; i <= nCount; i++) { delete [] arrCor[i]; }
			delete [] arrCor;
		}
		else if(nCount == 40) {
			//��������� ������ �������
			for(int i = 0; i < nCount; i++) { delete [] arr[i]; }
			delete [] arr;
			//��������� ������ ���������
			for(int i = 0; i <= nCount; i++) { delete [] arrCor[i]; }
			delete [] arrCor;
		}
		Create_Graph = false;
		nCount = 0;
		StartP = 0;
	}
	//������� PaintBox
	PaintBox->Refresh();
	EditVertex->Text = "2";
}
//---------------------------------------------------------------------------
void __fastcall TFormGraphs::ButtonCreateMatrixClick(TObject *Sender)
{
	//���� ������������ ������ �� ��� � ������ ������������ ������
	if(EditVertex->Text == "") {
		ShowMessage("Enter counts of vertex!");
	}
	else {

		//�������� ������� � �������� �� 1 ������ ��� ����������� ������� ����� � �������
		VertexCount = StrToInt(EditVertex->Text) + 1;
		Create_Matrix = true;
		StringGrid->RowCount = VertexCount;
		StringGrid->ColCount = VertexCount;
		for(int i = 0; i < VertexCount; i++) {
			for(int j = 0; j < VertexCount; j++) {
				if(j == 0) StringGrid->Cells[i][j] = i;
				else if(i == 0) StringGrid->Cells[i][j] = j;
				else StringGrid->Cells[i][j] = "0";
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormGraphs::ButtonAddVertexClick(TObject *Sender)
{
	//������������� ���������� ������� �� ����, � ����������� ������� � ������ ������� � ��������
	EditVertex->Text = IntToStr(StrToInt(EditVertex->Text) + 1);
	VertexCount = StrToInt(EditVertex->Text) + 1;
	StringGrid->RowCount = VertexCount;
	StringGrid->ColCount = VertexCount;
	for(int i = 0; i < VertexCount; i++) {
		for(int j = 0; j < VertexCount; j++) {
			if(i == 0) StringGrid->Cells[i][j] = j;
			else if(j == 0) StringGrid->Cells[i][j] = i;
			else if(i == VertexCount-1 || j == VertexCount-1) StringGrid->Cells[i][j] = 0;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormGraphs::ButtonClearClick(TObject *Sender)
{
	//���������� ������� � ���������� ����
	VertexCount = 3;
	EditVertex->Text = IntToStr(VertexCount - 1);

	StringGrid->RowCount = VertexCount;
	StringGrid->ColCount = VertexCount;
	for(int i = 0; i < VertexCount; i++) {
		for(int j = 0; j < VertexCount; j++) {
			if(i == 0) StringGrid->Cells[i][j] = j;
			else if(j == 0) StringGrid->Cells[i][j] = i;
			else StringGrid->Cells[i][j] = 0;
		}
	}
	//������� ���� PaintBox
	PaintBox->Refresh();
	N = 0;
	//���� ������� ���� �������� � ������, �� ������� �� �� ������ ���� � ������� ������ ���������
	if(!Create_Graph || StartP == 0) {
		if(nCount == 0) {
			ShowMessage("Memory is empty!");
		}
		else if(nCount == 20) {
			//��������� ������ �������
			for(int i = 0; i < nCount; i++) { delete [] arr[i]; }
			delete [] arr;
			//��������� ������ ���������
			for(int i = 0; i <= nCount; i++) { delete [] arrCor[i]; }
			delete [] arrCor;
		}
		else if(nCount == 40) {
			//��������� ������ �������
			for(int i = 0; i < nCount; i++) { delete [] arr[i]; }
			delete [] arr;
			//��������� ������ ���������
			for(int i = 0; i <= nCount; i++) { delete [] arrCor[i]; }
			delete [] arrCor;
		}
		Create_Graph = false;
		nCount = 0;
		StartP = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormGraphs::ButtonCreateGraphClick(TObject *Sender)
{
	StringGrid->Visible = false;
	LabelCountVertex->Visible = false;
	EditVertex->Visible = false;
	ButtonCreateMatrix->Visible = false;
	ButtonCreateGraph->Visible = false;
	ButtonAddVertex->Visible = false;
	ButtonBack->Visible = false;


	PaintAddVertex->Visible = true;
	PaintConnectVertices->Visible = true;
	PaintDelVertex->Visible = true;



	//���� ������������ ����� �������� ������� � ������,
	//�� �� ������� ������ �� ��������, �� ������� ��������, ����� �������� �����
	if(Create_Graph || StartP != 0) {
		if(nCount == 0) {
			ShowMessage("Memory is empty!");
		}
		else if(nCount == 20) {
			//��������� ������ �������
			for(int i = 0; i < nCount; i++) { delete [] arr[i]; }
			delete [] arr;
			//��������� ������ ���������
			for(int i = 0; i <= nCount; i++) { delete [] arrCor[i]; }
			delete [] arrCor;
		}
		else if(nCount == 40) {
			//��������� ������ �������
			for(int i = 0; i < nCount; i++) { delete [] arr[i]; }
			delete [] arr;
			//��������� ������ ���������
			for(int i = 0; i <= nCount; i++) { delete [] arrCor[i]; }
			delete [] arrCor;
		}
		Create_Graph = false;
		IfStartPaint = false;
		StartP = 0;
		nCount = 0;
	}
	//��� ��� ��������� ��� �� ���������� �������, ���� ���, �� ���������� ������� � ������
	if((!Create_Graph) && (StartP == 0)) {
		//PanelDefault->Visible = false;
        PaintBox -> Refresh();
		Create_Graph = true;
		//����� ����� �� Edit, ����� ����� ������ �������
		N = StrToIntDef(EditVertex->Text, 2);

		//�������� ������ ��� ������ ��� ������ � ������� ��� ��������� ������
		if(N <= 15) {
			nCount = 20;
			arr = new int*[nCount];
			for(int i = 0; i < nCount; i++) {
				arr[i] = new int[nCount];
			}
		}
		else if(N > 15 && N <= 30) {
			nCount = 40;
			arr = new int*[nCount];
			for(int i = 0; i < nCount; i++) {
				arr[i] = new int[nCount];
			}
		}

		//��������� ������ ������� �� StringGrid
		for(int i = 1; i < nCount; i++) {
			for(int j = 1; j < nCount; j++) {
				if(i <= N && j <= N) {
					arr[i-1][j-1] = StrToInt(StringGrid->Cells[i][j]);
				}
				else {
					arr[i-1][j-1] = 0;
				}
			}
		}

		//������� ������ �� ���������� ������ + 1 ��� �������� ���������(+1 ��� ��������)
		//� ������� ��� ��������� ������
		if(N <= 15) {
			nCount = 20;
			arrCor = new int*[nCount+1];
			for(int i = 0; i <= nCount; i++) {
				arrCor[i] = new int[2];
			}
		}
		else if(N > 15 && N <= 30) {
			nCount = 40;
			arrCor = new int*[nCount+1];
			for(int i = 0; i <= nCount; i++) {
				arrCor[i] = new int[2];
			}
		}


		//��������� ������ ��������� ��������� ������������� �����
		int tempX, tempY;
		//������ ���������� ������, ����� ����� ��������� �������������� ������ �������
		arrCor[0][0] = 0;
		arrCor[0][1] = 0;
		for(int i = 1; i <= N; i++) {
			tempX = (rand() % 700) + 20;
			tempY = (rand() % 500) + 20;
			arrCor[i][0] = tempX;
			arrCor[i][1] = tempY;
		}

		PaintBox->Canvas->Pen->Width = 2;
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				if(arr[j][i] > 0 && i != j) {
					PaintBox->Canvas->MoveTo(arrCor[i+1][0], arrCor[i+1][1]);
					//������ ��������� ������� � ��������� � ����������
					PaintBox->Canvas->LineTo(arrCor[j+1][0], arrCor[j+1][1]);
					//���������� ����
					xMat = (arrCor[j+1][0] + arrCor[i+1][0]) / 2;
					yMat = (arrCor[j+1][1] + arrCor[i+1][1]) / 2;
					PaintBox->Canvas->Font->Color = clRed;
					PaintBox->Canvas->TextOut(xMat, yMat, IntToStr(arr[j][i]));
					PaintBox->Canvas->Font->Color = clWhite;
				}

				//���� ������ ����� �������
				else if(arr[j][i] > 0 && i == j) {
					PaintBox->Canvas->Brush->Color = clInactiveBorder;
					PaintBox->Canvas->Ellipse(arrCor[i+1][0] - 2 * radius - 5,
											  arrCor[i+1][1] - radius - 5,
											  arrCor[i+1][0] + radius - 5,
											  arrCor[i+1][1] + 2 * radius - 5);
					PaintBox->Canvas->Font->Color = clRed;
					PaintBox->Canvas->TextOut(arrCor[i+1][0] - 2 * radius - 5, arrCor[i+1][1] - radius - 5, IntToStr(arr[j][i]));
					PaintBox->Canvas->Font->Color = clWhite;
				}
			}
		}
		PaintBox->Canvas->Pen->Width = 1;
		//�������� ��������� ������
		for(int i = 1; i <= N; i++) {
			PaintBox->Canvas->Brush->Color = clRed;
			//������ �������
			PaintBox->Canvas->Ellipse(arrCor[i][0] - radius,
									  arrCor[i][1] - radius,
									  arrCor[i][0] + radius,
									  arrCor[i][1] + radius );
			PaintBox->Canvas->Font->Color = clWhite;
			if(i >= 10) {
				minusXcor = 6;
			}
			PaintBox->Canvas->TextOut(arrCor[i][0]-minusXcor, arrCor[i][1]-minusYcor, IntToStr(i));
			minusXcor = 3;

		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TFormGraphs::PaintBoxMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if(ClickVertex) {
		if(IfStartPaint && StartP == 0) {
			StartP++;
			N = 0;
			IfStartPaint = false;
		}
		N += 1;
		EditVertex->Text = N;

		PaintBox->Canvas->Brush->Color = clRed;
		PaintBox->Canvas->Ellipse( X - radius,
								   Y - radius,
								   X + radius,
								   Y + radius );
		arrCor[N][0] = X;
		arrCor[N][1] = Y;
		PaintBox->Canvas->Font->Color = clWhite;
		//���� ����� ������ �����������, �� ����� � ���������� ������� ��������� ����� � ������
		if(N >= 10) {
			minusXcor = 6;
		}
		PaintBox->Canvas->TextOut(X - minusXcor, Y - minusYcor, N);
	}

	else if(ClickLine) {
		if(N == 0) {
			ShowMessage("Count vertex = 0");
		}
		else {
			static bool first_press = true;

			//�������� ������ �� ������������ ������� ��� ���
			if(first_press && N >= 1) {
				for(int i = 1; i <= N; i++) {
					//���� ��, �� ��������� ����� �������
					if((X > (arrCor[i][0] - radius)) && (X < (arrCor[i][0] + radius)) && (Y > (arrCor[i][1] - radius)) && (Y < (arrCor[i][1] + radius))) {
						tempI1 = i;
					}
				}
				//���� ������������ �� ����� � �������, �� ���������, ��� ����� �� ����
				if(tempI1 != 0) {
					first_press = !first_press;
				}
			}
			else if(tempI1 != 0){
				//�������� �� ��������� ������������� �� ������ �������
				for(int i = 1; i <= N; i++) {
					//���� �����, �� ���������� � �����
					if((X > (arrCor[i][0] - radius)) && (X < (arrCor[i][0] + radius)) && (Y > (arrCor[i][1] - radius)) && (Y < (arrCor[i][1] + radius))) {
						tempI2 = i;
					}
				}
				//���� ������������ �� �����, �� �������, ��� ������ ������ �� ����
				if(tempI2 != 0) {
					first_press = !first_press;
					if(tempI1 != tempI2) {
						//������� ����������� ������ ������ � ����������� ������
						PaintBox->Canvas->Pen->Width = 2;
						PaintBox->Canvas->MoveTo(arrCor[tempI1][0], arrCor[tempI1][1]);
						//������ ��������� ������� � ��������� � ����������
						PaintBox->Canvas->LineTo(arrCor[tempI2][0], arrCor[tempI2][1]);
						PaintBox->Canvas->Brush->Color = clRed;
						PaintBox->Canvas->Pen->Width = 1;
						//������ �������
						PaintBox->Canvas->Ellipse(arrCor[tempI1][0] - radius,
												  arrCor[tempI1][1] - radius,
												  arrCor[tempI1][0] + radius,
												  arrCor[tempI1][1] + radius );
						PaintBox->Canvas->Font->Color = clWhite;
						if(tempI1 >= 10) {
							minusXcor = 6;
						}
						PaintBox->Canvas->TextOut(arrCor[tempI1][0] - minusXcor, arrCor[tempI1][1] - minusYcor, IntToStr(tempI1));
						minusXcor = 3;
						PaintBox->Canvas->Brush->Color = clRed;
						//������ �������
						PaintBox->Canvas->Ellipse(arrCor[tempI2][0] - radius,
												  arrCor[tempI2][1] - radius,
												  arrCor[tempI2][0] + radius,
												  arrCor[tempI2][1] + radius );
						PaintBox->Canvas->Font->Color = clWhite;
						//���� ����� ������ 9, �� ��� ������� ����������� �������� ����� ������ �����
						if(tempI2 >= 10) {
							minusXcor = 6;
						}
						PaintBox->Canvas->TextOut(arrCor[tempI2][0]-minusXcor, arrCor[tempI2][1]-minusYcor, IntToStr(tempI2));
						minusXcor = 3;
						//��������� ������ ����� ��� ����� �������� �����
						FormSizeVer->ShowModal();
						k = StrToInt(FormSizeVer->EditSizeVer->Text);


						PaintBox->Canvas->Brush->Color = clInactiveBorder;
						xMat = (arrCor[tempI2][0] + arrCor[tempI1][0]) / 2;
						yMat = (arrCor[tempI2][1] + arrCor[tempI1][1]) / 2;
						PaintBox->Canvas->Font->Color = clRed;
						PaintBox->Canvas->TextOut(xMat, yMat, IntToStr(k));
						PaintBox->Canvas->Font->Color = clWhite;
					}
					else if(tempI1 == tempI2){
						PaintBox->Canvas->Pen->Width = 2;
						PaintBox->Canvas->Brush->Color = clInactiveBorder;
						//����
						PaintBox->Canvas->Ellipse(arrCor[tempI1][0] - 2 * radius - 5,
											  arrCor[tempI1][1] - radius - 5,
											  arrCor[tempI1][0] + radius - 5,
											  arrCor[tempI1][1] + 2 * radius - 5);
						//�������
						PaintBox->Canvas->Pen->Width = 1;
						PaintBox->Canvas->Brush->Color = clRed;
						PaintBox->Canvas->Ellipse(arrCor[tempI1][0] - radius,
												  arrCor[tempI1][1] - radius,
												  arrCor[tempI1][0] + radius,
												  arrCor[tempI1][1] + radius );
						PaintBox->Canvas->Font->Color = clWhite;
						if(tempI1 >= 10) {
							minusXcor = 6;
						}
						PaintBox->Canvas->TextOut(arrCor[tempI1][0] - minusXcor, arrCor[tempI1][1] - minusYcor, IntToStr(tempI1));
						minusXcor = 3;


						//��������� ������ ����� ��� ����� �������� �����
						FormSizeVer->ShowModal();
						k = StrToInt(FormSizeVer->EditSizeVer->Text);
						PaintBox->Canvas->Brush->Color = clInactiveBorder;
						PaintBox->Canvas->Font->Color = clRed;
						PaintBox->Canvas->TextOut(arrCor[tempI1][0] - 2 * radius - 5, arrCor[tempI1][1] - radius - 5, IntToStr(k));
						PaintBox->Canvas->Font->Color = clWhite;
					}
					//���������� ������ � �������, ���� ����������� �������
					arr[tempI1-1][tempI2-1] = k;
					arr[tempI2-1][tempI1-1] = k;
					FormSizeVer->EditSizeVer->Text = "1";
					tempI1 = 0;
					tempI2 = 0;
				}
			}
		}
	}

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//DELETE VERTEX
	else if(ClickDelVer) {
		if(N == 0) {
			ShowMessage("Counts vertex = 0");
		}
		else {
			//�������� �� ���� �� �������, ���� �������, �� ���������� ����� � �������� ����������
			for(int i = 1; i <= N; i++) {
				if((X > (arrCor[i][0] - radius)) && (X < (arrCor[i][0] + radius)) && (Y > (arrCor[i][1] - radius)) && (Y < (arrCor[i][1] + radius))) {
					tempDel = i;
					arrCor[i][0] = -1;
					arrCor[i][1] = -1;

					//�������������� ���������� ������, �������� ���������� � �����
					int k0, k1;
					for(int i = 1; i < N; i++) {
						if(arrCor[i][0] == -1) {
							k0 = arrCor[i][0];
							k1 = arrCor[i][1];
							arrCor[i][0] = arrCor[i+1][0];
							arrCor[i][1] = arrCor[i+1][1];
							arrCor[i+1][0] = k0;
							arrCor[i+1][1] = k1;
						}
					}
					//������ ������ � �������� �� ���� ������� ������, ����� �������� ���� ������ ����� ��������
					tempArr = new int*[N-1];
					for(int i = 0; i < N-1; i++) {
						tempArr[i] = new int[N-1];
					}

					//�������������� ��� ������ � ����� ��������� ������
					for(int i = 0; i < N-1; i++) {
						for(int j = 0; j < N-1; j++) {
							if(tempDel == 1) {
								tempArr[i][j] = arr[i+1][j+1];
							}
							else if(i == tempDel-1 && j == tempDel-1 && tempDel != 1) {
								tempArr[i][j] = arr[i+1][j+1];
							}
							else if(i == tempDel-1 && tempDel != 1) {
								tempArr[i][j] = arr[i+1][j];
							}
							else if(j == tempDel-1 && tempDel != 1) {
								tempArr[i][j] = arr[i][j+1];
							}
							else if(tempDel != 1){
								tempArr[i][j] = arr[i][j];
							}
						}
					}
					//�������� �������� ������
					for(int i = 0; i < N; i++) {
						for(int j = 0; j < N; j++) {
							arr[i][j] = 0;
						}
					}
					//���������� � ��������� ������ ����� �������
					for(int i = 0; i < N-1; i++) {
						for(int j = 0; j < N-1; j++) {
							arr[i][j] = tempArr[i][j];
						}
					}
					for(int i = 0; i < N-1; i++) {
						delete [] tempArr[i];
					}
					delete [] tempArr;
					//�������� ��� ���������� ����� ���������� ������� ��������
					for(int i = N; i <= nCount; i++) {
						arrCor[i][0] = 0;
						arrCor[i][1] = 0;
					}
					//��������� ���������� ������
					N -= 1;
					EditVertex->Text = N;
					//��������� �������������� ���� ����� �������� ����� �������, �������������� ������� PaintBox
					PaintBox->Refresh();
					PaintBox->Canvas->Pen->Width = 2;
					for(int i = 0; i < N; i++) {
						for(int j = 0; j < N; j++) {
							if(arr[j][i] > 0 && i != j) {
								PaintBox->Canvas->MoveTo(arrCor[i+1][0], arrCor[i+1][1]);
								//������ ��������� ������� � ��������� � ����������
								PaintBox->Canvas->LineTo(arrCor[j+1][0], arrCor[j+1][1]);
								//���������� ����
								xMat = (arrCor[j+1][0] + arrCor[i+1][0]) / 2;
								yMat = (arrCor[j+1][1] + arrCor[i+1][1]) / 2;
								PaintBox->Canvas->Font->Color = clRed;
								PaintBox->Canvas->TextOut(xMat, yMat, IntToStr(arr[j][i]));
								PaintBox->Canvas->Font->Color = clWhite;
							}

							//���� ������ ����� �������
							else if(arr[j][i] > 0 && i == j) {
								PaintBox->Canvas->Brush->Color = clInactiveBorder;
								PaintBox->Canvas->Ellipse(arrCor[i+1][0] - 2 * radius - 5,
														  arrCor[i+1][1] - radius - 5,
														  arrCor[i+1][0] + radius - 5,
														  arrCor[i+1][1] + 2 * radius - 5);
								PaintBox->Canvas->Font->Color = clRed;
								PaintBox->Canvas->TextOut(arrCor[i+1][0] - 2 * radius - 5, arrCor[i+1][1] - radius - 5, IntToStr(arr[j][i]));
								PaintBox->Canvas->Font->Color = clWhite;
							}
						}
					}
					PaintBox->Canvas->Pen->Width = 1;
					//�������� ��������� ������
					for(int i = 1; i <= N; i++) {
						PaintBox->Canvas->Brush->Color = clRed;
						//������ �������
						PaintBox->Canvas->Ellipse(arrCor[i][0] - radius,
												  arrCor[i][1] - radius,
												  arrCor[i][0] + radius,
												  arrCor[i][1] + radius );
						PaintBox->Canvas->Font->Color = clWhite;
						if(i >= 10) {
							minusXcor = 6;
						}
						PaintBox->Canvas->TextOut(arrCor[i][0]-minusXcor, arrCor[i][1]-minusYcor, IntToStr(i));
						minusXcor = 3;
					}
				}
			}

		}
	}
}

//---------------------------------------------------------------------------

//���������� ����� �������
void __fastcall TFormGraphs::PaintAddVertexClick(TObject *Sender)
{
	ClickVertex = true;
	ClickLine = false;
	ClickDelVer = false;
	//���� ������� � ��������� ����� ��� ����� �������� �������,
	//�� ������ ������� � ������������ �����
	if((!Create_Graph) && (StartP == 0)) {
		IfStartPaint = true;
		N = 15;
		if(N <= 15) {
			nCount = 20;
			arr = new int*[nCount];
			for(int i = 0; i < nCount; i++) {
				arr[i] = new int[nCount];
			}
			N = 0;
		}
		else if(N > 15 && N <= 30) {
			nCount = 40;
			arr = new int*[nCount];
			for(int i = 0; i < nCount; i++) {
				arr[i] = new int[nCount];
			}
			N = 0;
		}
		//��������� ������ ������
		for(int i = 1; i < nCount; i++) {
			for(int j = 1; j < nCount; j++) {
				arr[i-1][j-1] = 0;
			}
		}

		//������� ������ �� ���������� ������ + 1 ��� �������� ���������(+1 ��� ��������)
		//� ������� ��� ��������� ������
		if(N <= 15) {
			nCount = 20;
			arrCor = new int*[nCount+1];
			for(int i = 0; i <= nCount; i++) {
				arrCor[i] = new int[2];
			}
		}
		else if(N > 15 && N <= 30) {
			nCount = 40;
			arrCor = new int*[nCount+1];
			for(int i = 0; i <= nCount; i++) {
				arrCor[i] = new int[2];
			}
		}
		//��������� ������ ������
		for(int i = 0; i <= nCount; i++) {
			arrCor[i][0] = 0;
			arrCor[i][1] = 0;
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TFormGraphs::PaintConnectVerticesClick(TObject *Sender)
{
	ClickLine = true;
	ClickVertex = false;
	ClickDelVer = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphs::PaintDelVertexClick(TObject *Sender)
{
	ClickLine = false;
	ClickVertex = false;
	ClickDelVer = true;
}
//---------------------------------------------------------------------------

//������� ������ ������� ����� � ����
void __fastcall TFormGraphs::ButtonInFileClick(TObject *Sender)
{
	ofstream inFile;
	inFile.open("Matrix.txt", ios::out);
	//��������� ������ �� ����, ���� ��, �� ���������� � ���� ������� �����
	N = StrToInt(EditVertex->Text);
	if(inFile) {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				inFile << arr[j][i] << " ";
			}
			if(i != N-1) {
				inFile << "\n";
			}
		}
		//��������� ���� ����� ������
		inFile.close();
	}
}
//---------------------------------------------------------------------------
//������� ���������� ������� ����� �� �����
void __fastcall TFormGraphs::ButtonOutFileClick(TObject *Sender)
{
	StringGrid->Visible = true;
	LabelCountVertex->Visible = true;
	EditVertex->Visible = true;
	ButtonCreateMatrix->Visible = true;
	ButtonCreateGraph->Visible = true;
	ButtonAddVertex->Visible = true;
	ButtonBack->Visible = true;

	PaintAddVertex->Visible = false;
	PaintConnectVertices->Visible = false;
	PaintDelVertex->Visible = false;

	N = 0;
	PaintBox->Refresh();
    StartP = 0;


	//���������, ��� ���� ����������� ��� ������
	ifstream outFile;
	outFile.open("Matrix.txt", ios::in);
	int n = 0;
	//��������� ������ �� ����, ���� ��, �� �������� ������� ��������
	if(outFile.is_open()) {
		int countC = 0;
		int someT;
		//���� �� ����� �� ����� ����� - ��������� ������ ����� ������� � ��������� ���������� ���������
		while(!outFile.eof()) {
			outFile >> someT;
			countC += 1;
		}
		//��������� � ������ �����
		outFile.seekg(0, ios::beg);
		outFile.clear();

		//��� ��� � ��� ������� n*n, �� ����������� ���������� �����
		int n = sqrt(countC);
		N = n;
		//���� ������ � ��������� �� ���������� �����, �� ������� ���
		if((!Create_Graph) && (StartP == 0)) {
			if(N <= 15) {
			nCount = 20;
			arr = new int*[nCount];
			for(int i = 0; i < nCount; i++) {
				arr[i] = new int[nCount];
			}
			}
			else if(N > 15 && N <= 30) {
				nCount = 40;
				arr = new int*[nCount];
				for(int i = 0; i < nCount; i++) {
					arr[i] = new int[nCount];
				}
			}
		}
		//��������� ��� ������
		for(int i = 0; i < nCount; i++) {
			for(int j = 0; j < nCount; j++) {
				arr[i][j] = 0;
			}
		}

		//��������� � ������ ���������� ����� � �������� ������������ �� � ������
		outFile.seekg(0, ios::beg);
		outFile.clear();
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				outFile >> arr[i][j];
			}
		}

		//����� �� ������� ��������� ������� � StringGrid
		StringGrid->RowCount = n + 1;
		StringGrid->ColCount = n + 1;
		for(int i = 0; i <= N; i++) {
			for(int j = 0; j <= N; j++) {
				if(i == 0) {
					StringGrid->Cells[i][j] = j;
				}
				else if(j == 0) {
					StringGrid->Cells[i][j] = i;
				}
				else {
					StringGrid->Cells[j][i] = arr[i-1][j-1];
				}
			}
		}
		//��������� ��������� ������ � Edit, ����� ����� ��������� ���������� ����
		EditVertex->Text = N;
		//��������� ����
		outFile.close();
	}
}

//---------------------------------------------------------------------------
//������� �������������
/*								if(i == tempDel-1 && j == tempDel-1) {
									tempArr[i][j] = arr[i+1][j+1];
								}
								else if(i == tempDel-1) {

								}*/
void __fastcall TFormGraphs::ButtonBackClick(TObject *Sender)
{
	StringGrid->Visible = false;
	LabelCountVertex->Visible = false;
	EditVertex->Visible = false;
	ButtonCreateMatrix->Visible = false;
	ButtonCreateGraph->Visible = false;
	ButtonAddVertex->Visible = false;
    ButtonBack->Visible = false;

	PaintAddVertex->Visible = true;
	PaintConnectVertices->Visible = true;
	PaintDelVertex->Visible = true;
}
//---------------------------------------------------------------------------

