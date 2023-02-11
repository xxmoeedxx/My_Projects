#pragma once
#include<iostream>
#include<Windows.h>
#include<fstream>
#include"Color.h"
#include"Pawn.h"
#include"Bishop.h"
#include"Rook.h"
#include"King.h"
#include"Knight.h"
#include"SGeneral.h"
#include"GGeneral.h"
#include"Lance.h"
using namespace std;
class Piece;
class Board
{
public:
	void LoadFile(ifstream& rdr, int*& wPs, int*& bPs);
	void SetClr(int tcl, int bcl)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
	}
	void hlt(int sri, int sci, int rdim, int cdim, colors hclr);
	void hlt2(int sri, int sci, int rdim, int cdim, colors hclr);
	void uhlt(int sri, int sci, int rdim, int cdim);
	void uhlt2(int sri, int sci, int rdim, int cdim);
	void highlight(int sri, int sci, int rdim, int cdim);
	void unhighlight(int sri, int sci, int rdim, int cdim);
	void gotoRowCol(int rpos, int cpos)
	{
		COORD scrn;
		HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
		scrn.X = cpos;
		scrn.Y = rpos;
		SetConsoleCursorPosition(hOuput, scrn);
	}
	void drawFilledBox(int sri, int sci, int rdim, int cdim, char sym = -37)
	{
		for (int i = 0; i < rdim; i++)
		{
			for (int j = 0; j < cdim; j++)
			{
				gotoRowCol(sri + i, sci + j);
				if (!(i == 0 || j == 0 || j == cdim - 1 || i == rdim - 1))
				{
					cout << sym;
				}
			}
		}
	}
	void drawBox(int sri, int sci, int rdim, int cdim,char sym=-37)
	{
		for (int i = 0; i < rdim; i++)
		{
			for (int j = 0; j < cdim; j++)
			{
				gotoRowCol(sri+i, sci+j);
				if (i == 0 || j == 0 || j == cdim - 1 || i == rdim - 1)
				{
					cout << sym;
				}
			}
		}
	}
	void drawGrid(int R, int C, int rdim, int cdim)
	{
		int sri = 3, sci;
		for (int i = 0; i < R; i++)
		{
			sci = 3;
			for (int j = 0; j < C; j++)
			{
				drawBox(sri, sci, rdim, cdim);
				sci += cdim-1;
			}
			sri += rdim-1;
		}
	}
	Piece*** Ps;
	Board();
	void Draw();
	void Move(int sri,int sci,int dri,int dci);
	void Update(int sri, int sci, int dri, int dci);
	void Copy(Board*);
};
