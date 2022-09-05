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
//Переменные для соединения вершин
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
	//Происходит обновление StringGrid при переходе из одного пункта меню в другой
	VertexCount = 3;
	StringGrid->RowCount = VertexCount;
	StringGrid->ColCount = VertexCount;
	//Включаем отображения для кнопок и StringGrid при работе с матрицей
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

	//Цикл заполнения в матрице номеров ячеек
	for(int i = 0; i < VertexCount; i++) {
		for(int j = 0; j < VertexCount; j++) {
			if(j == 0) StringGrid->Cells[i][j] = i;
			else if(i == 0) StringGrid->Cells[i][j] = j;
			else StringGrid->Cells[i][j] = 0;
		}
	}
	//Очищает память от всех массивов, если они были заполнены или просто созданы
	if(Create_Graph || StartP != 0) {
		if(nCount == 0) {
			ShowMessage("Memory is empty!");
		}
		else if(nCount == 20) {
			//Удаляется массив матрицы
			for(int i = 0; i < nCount; i++) { delete [] arr[i]; }
			delete [] arr;
			//Удаляется массив координат
			for(int i = 0; i <= nCount; i++) { delete [] arrCor[i]; }
			delete [] arrCor;
		}
		else if(nCount == 40) {
			//Удаляется массив матрицы
			for(int i = 0; i < nCount; i++) { delete [] arr[i]; }
			delete [] arr;
			//Удаляется массив координат
			for(int i = 0; i <= nCount; i++) { delete [] arrCor[i]; }
			delete [] arrCor;
		}
		Create_Graph = false;
		nCount = 0;
		StartP = 0;
	}
	//Очищает PaintBox
	PaintBox->Refresh();
	EditVertex->Text = "2";
}
//---------------------------------------------------------------------------
void __fastcall TFormGraphs::ButtonCreateMatrixClick(TObject *Sender)
{
	//Если пользователь ничего не ввёл в строку коливечества вершин
	if(EditVertex->Text == "") {
		ShowMessage("Enter counts of vertex!");
	}
	else {

		//Создаётся матрица с размером на 1 больше для отображения номеров строк и колонок
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
	//Увеличивается количество вершины на одну, и досоздается матрица с пустой строкой и колонкой
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
	//Возвращает матрицу к начальному виду
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
	//Очищает поле PaintBox
	PaintBox->Refresh();
	N = 0;
	//Если матрица была записана в массив, то очищаем от неё память тоже и удаляем массив координат
	if(!Create_Graph || StartP == 0) {
		if(nCount == 0) {
			ShowMessage("Memory is empty!");
		}
		else if(nCount == 20) {
			//Удаляется массив матрицы
			for(int i = 0; i < nCount; i++) { delete [] arr[i]; }
			delete [] arr;
			//Удаляется массив координат
			for(int i = 0; i <= nCount; i++) { delete [] arrCor[i]; }
			delete [] arrCor;
		}
		else if(nCount == 40) {
			//Удаляется массив матрицы
			for(int i = 0; i < nCount; i++) { delete [] arr[i]; }
			delete [] arr;
			//Удаляется массив координат
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



	//Если пользователь решил записать матрицу в массив,
	//но не очистил память от прошлого, то сначала очистить, потом записать новый
	if(Create_Graph || StartP != 0) {
		if(nCount == 0) {
			ShowMessage("Memory is empty!");
		}
		else if(nCount == 20) {
			//Удаляется массив матрицы
			for(int i = 0; i < nCount; i++) { delete [] arr[i]; }
			delete [] arr;
			//Удаляется массив координат
			for(int i = 0; i <= nCount; i++) { delete [] arrCor[i]; }
			delete [] arrCor;
		}
		else if(nCount == 40) {
			//Удаляется массив матрицы
			for(int i = 0; i < nCount; i++) { delete [] arr[i]; }
			delete [] arr;
			//Удаляется массив координат
			for(int i = 0; i <= nCount; i++) { delete [] arrCor[i]; }
			delete [] arrCor;
		}
		Create_Graph = false;
		IfStartPaint = false;
		StartP = 0;
		nCount = 0;
	}
	//Ещё раз проверяем нет ли созданного массива, если нет, то записываем матрицу в массив
	if((!Create_Graph) && (StartP == 0)) {
		//PanelDefault->Visible = false;
        PaintBox -> Refresh();
		Create_Graph = true;
		//Берем число из Edit, чтобы знать размер массива
		N = StrToIntDef(EditVertex->Text, 2);

		//Выделяем память под нужный нам массив с запасом для рисования графов
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

		//Заполняем массив числами из StringGrid
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

		//Создаем массив на количество вершин + 1 для хранения координат(+1 для удобства)
		//с запасом для рисования графов
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


		//Заполняем массив координат случайным расположением точек
		int tempX, tempY;
		//Первая координата пустая, чтобы номер координат соответствовал номеру вершины
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
					//рисует следующую вершину и соединяет с предыдущей
					PaintBox->Canvas->LineTo(arrCor[j+1][0], arrCor[j+1][1]);
					//Взвешенный граф
					xMat = (arrCor[j+1][0] + arrCor[i+1][0]) / 2;
					yMat = (arrCor[j+1][1] + arrCor[i+1][1]) / 2;
					PaintBox->Canvas->Font->Color = clRed;
					PaintBox->Canvas->TextOut(xMat, yMat, IntToStr(arr[j][i]));
					PaintBox->Canvas->Font->Color = clWhite;
				}

				//Дуга вокруг одной вершины
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
		//Алгоритм рисования вершин
		for(int i = 1; i <= N; i++) {
			PaintBox->Canvas->Brush->Color = clRed;
			//рисуем вершины
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
		//Если число вершин двухзначное, то номер в окружности вершины смещается ближе к центру
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

			//Проверка выбрал ли пользователь вершину или нет
			if(first_press && N >= 1) {
				for(int i = 1; i <= N; i++) {
					//Если да, то сохраняем номер вершины
					if((X > (arrCor[i][0] - radius)) && (X < (arrCor[i][0] + radius)) && (Y > (arrCor[i][1] - radius)) && (Y < (arrCor[i][1] + radius))) {
						tempI1 = i;
					}
				}
				//Если пользователь не попал в вершину, то считается, что клика не было
				if(tempI1 != 0) {
					first_press = !first_press;
				}
			}
			else if(tempI1 != 0){
				//Проверка на попадание пользователем во вторую вершину
				for(int i = 1; i <= N; i++) {
					//Если попал, то запоминаем её номер
					if((X > (arrCor[i][0] - radius)) && (X < (arrCor[i][0] + radius)) && (Y > (arrCor[i][1] - radius)) && (Y < (arrCor[i][1] + radius))) {
						tempI2 = i;
					}
				}
				//Если пользователь не попал, то считаем, что кликов вообще не было
				if(tempI2 != 0) {
					first_press = !first_press;
					if(tempI1 != tempI2) {
						//Процесс перерисовки данных вершин с соединяющей линией
						PaintBox->Canvas->Pen->Width = 2;
						PaintBox->Canvas->MoveTo(arrCor[tempI1][0], arrCor[tempI1][1]);
						//рисует следующую вершину и соединяет с предыдущей
						PaintBox->Canvas->LineTo(arrCor[tempI2][0], arrCor[tempI2][1]);
						PaintBox->Canvas->Brush->Color = clRed;
						PaintBox->Canvas->Pen->Width = 1;
						//рисуем вершины
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
						//рисуем вершины
						PaintBox->Canvas->Ellipse(arrCor[tempI2][0] - radius,
												  arrCor[tempI2][1] - radius,
												  arrCor[tempI2][0] + radius,
												  arrCor[tempI2][1] + radius );
						PaintBox->Canvas->Font->Color = clWhite;
						//Если число больше 9, то для лучшего отображения сдвигаем вывод текста левее
						if(tempI2 >= 10) {
							minusXcor = 6;
						}
						PaintBox->Canvas->TextOut(arrCor[tempI2][0]-minusXcor, arrCor[tempI2][1]-minusYcor, IntToStr(tempI2));
						minusXcor = 3;
						//Открываем вторую форму для ввода величины ребра
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
						//Дуга
						PaintBox->Canvas->Ellipse(arrCor[tempI1][0] - 2 * radius - 5,
											  arrCor[tempI1][1] - radius - 5,
											  arrCor[tempI1][0] + radius - 5,
											  arrCor[tempI1][1] + 2 * radius - 5);
						//Вершина
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


						//Открываем вторую форму для ввода величины ребра
						FormSizeVer->ShowModal();
						k = StrToInt(FormSizeVer->EditSizeVer->Text);
						PaintBox->Canvas->Brush->Color = clInactiveBorder;
						PaintBox->Canvas->Font->Color = clRed;
						PaintBox->Canvas->TextOut(arrCor[tempI1][0] - 2 * radius - 5, arrCor[tempI1][1] - radius - 5, IntToStr(k));
						PaintBox->Canvas->Font->Color = clWhite;
					}
					//Добавление единиц в матрицу, если соединились вершины
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
			//Проверка на клик по вершине, если найдена, то запоминаем номер и обнуляем координаты
			for(int i = 1; i <= N; i++) {
				if((X > (arrCor[i][0] - radius)) && (X < (arrCor[i][0] + radius)) && (Y > (arrCor[i][1] - radius)) && (Y < (arrCor[i][1] + radius))) {
					tempDel = i;
					arrCor[i][0] = -1;
					arrCor[i][1] = -1;

					//Перезаписываем координаты вершин, удалённую отправляем в конец
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
					//Создаём массив с матрицей на одну вершину меньше, чтобы записать туда массив после удаления
					tempArr = new int*[N-1];
					for(int i = 0; i < N-1; i++) {
						tempArr[i] = new int[N-1];
					}

					//Перезаписываем наш массив в новый временный массив
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
					//Обнуляем основной массив
					for(int i = 0; i < N; i++) {
						for(int j = 0; j < N; j++) {
							arr[i][j] = 0;
						}
					}
					//Записываем в обнулённый массив новую матрицу
					for(int i = 0; i < N-1; i++) {
						for(int j = 0; j < N-1; j++) {
							arr[i][j] = tempArr[i][j];
						}
					}
					for(int i = 0; i < N-1; i++) {
						delete [] tempArr[i];
					}
					delete [] tempArr;
					//Обнуляем все координаты после обновления массива кординат
					for(int i = N; i <= nCount; i++) {
						arrCor[i][0] = 0;
						arrCor[i][1] = 0;
					}
					//Уменьшаем количество вершин
					N -= 1;
					EditVertex->Text = N;
					//Полностью перерисовываем граф после удаления одной вершины, предварительно очистив PaintBox
					PaintBox->Refresh();
					PaintBox->Canvas->Pen->Width = 2;
					for(int i = 0; i < N; i++) {
						for(int j = 0; j < N; j++) {
							if(arr[j][i] > 0 && i != j) {
								PaintBox->Canvas->MoveTo(arrCor[i+1][0], arrCor[i+1][1]);
								//рисует следующую вершину и соединяет с предыдущей
								PaintBox->Canvas->LineTo(arrCor[j+1][0], arrCor[j+1][1]);
								//Взвешенный граф
								xMat = (arrCor[j+1][0] + arrCor[i+1][0]) / 2;
								yMat = (arrCor[j+1][1] + arrCor[i+1][1]) / 2;
								PaintBox->Canvas->Font->Color = clRed;
								PaintBox->Canvas->TextOut(xMat, yMat, IntToStr(arr[j][i]));
								PaintBox->Canvas->Font->Color = clWhite;
							}

							//Дуга вокруг одной вершины
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
					//Алгоритм рисования вершин
					for(int i = 1; i <= N; i++) {
						PaintBox->Canvas->Brush->Color = clRed;
						//рисуем вершины
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

//Добавление новой вершины
void __fastcall TFormGraphs::PaintAddVertexClick(TObject *Sender)
{
	ClickVertex = true;
	ClickLine = false;
	ClickDelVer = false;
	//Если перешли в рисование сразу или после создания массива,
	//то создаём массивы с координатами здесь
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
		//Заполняем массив нулями
		for(int i = 1; i < nCount; i++) {
			for(int j = 1; j < nCount; j++) {
				arr[i-1][j-1] = 0;
			}
		}

		//Создаем массив на количество вершин + 1 для хранения координат(+1 для удобства)
		//с запасом для рисования графов
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
		//Заполняем массив нулями
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

//Процесс записи матрицы графа в файл
void __fastcall TFormGraphs::ButtonInFileClick(TObject *Sender)
{
	ofstream inFile;
	inFile.open("Matrix.txt", ios::out);
	//Проверяем открыл ли файл, если да, то записываем в него матрицу графа
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
		//Закрываем файл после записи
		inFile.close();
	}
}
//---------------------------------------------------------------------------
//Процесс заполнения матрицы графа из файла
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


	//Указываем, что файл открывается для чтения
	ifstream outFile;
	outFile.open("Matrix.txt", ios::in);
	int n = 0;
	//Проверяем открыт ли файл, если да, то начинаем процесс переписи
	if(outFile.is_open()) {
		int countC = 0;
		int someT;
		//Пока не дойдёт до конца файла - считываем каждый новый элемент и считываем количество элементов
		while(!outFile.eof()) {
			outFile >> someT;
			countC += 1;
		}
		//Переходим в начало файла
		outFile.seekg(0, ios::beg);
		outFile.clear();

		//Так как у нас матрица n*n, то высчитываем количество строк
		int n = sqrt(countC);
		N = n;
		//Если массив в программе не создавался ранее, то создаем его
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
		//Заполняем его нулями
		for(int i = 0; i < nCount; i++) {
			for(int j = 0; j < nCount; j++) {
				arr[i][j] = 0;
			}
		}

		//Переходим в начало текстового файла и начинаем переписывать всё в массив
		outFile.seekg(0, ios::beg);
		outFile.clear();
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				outFile >> arr[i][j];
			}
		}

		//Потом из массива перекинем матрицу в StringGrid
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
		//Обновляем количесво вершин в Edit, чтобы потом правильно нарисовать граф
		EditVertex->Text = N;
		//Закрываем файл
		outFile.close();
	}
}

//---------------------------------------------------------------------------
//Матрица инцидентности
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

