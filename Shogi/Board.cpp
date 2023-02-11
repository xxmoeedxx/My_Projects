#include"Shogi.h"
#include "Board.h"
Board::Board()
{
	Ps = new  Piece * *[9];
	for (int ri = 0; ri < 9; ri++)
	{
		Ps[ri] = new  Piece * [9];
		for (int ci = 0; ci < 9; ci++)
		{
			Ps[ri][ci] = nullptr;
			if (ri == 2)
				Ps[ri][ci] = new Pawn(ri, ci, BLACK, this);
			if (ri == 1 && (ci == 1))
				Ps[ri][ci] = new Rook(ri, ci, BLACK, this);
			if (ri == 1 && (ci == 7))
				Ps[ri][ci] = new Bishop(ri, ci, BLACK, this);
			if (ri == 0 && (ci == 8||ci==0))
				Ps[ri][ci] = new Lance(ri, ci, BLACK, this);
			if (ri == 0 && (ci == 1 || ci == 7))
				Ps[ri][ci] = new Knight(ri, ci, BLACK, this);
			if (ri == 0 && (ci == 6 || ci == 2))
				Ps[ri][ci] = new SGeneral(ri, ci, BLACK, this);
			if (ri == 0 && (ci == 5 || ci == 3))
				Ps[ri][ci] = new GGeneral(ri, ci, BLACK, this);
			if (ri == 0 && (ci == 4))
				Ps[ri][ci] = new King(ri, ci, BLACK, this);
			if (ri == 6)
				Ps[ri][ci] = new Pawn(ri, ci, WHITE, this);
			if (ri == 7 && (ci == 7))
				Ps[ri][ci] = new Rook(ri, ci, WHITE, this);
			if (ri == 7 && (ci == 1))
				Ps[ri][ci] = new Bishop(ri, ci, WHITE, this);
			if (ri == 8 && (ci == 8 || ci == 0))
				Ps[ri][ci] = new Lance(ri, ci, WHITE, this);
			if (ri == 8 && (ci == 1 || ci == 7))
				Ps[ri][ci] = new Knight(ri, ci, WHITE, this);
			if (ri == 8 && (ci == 6 || ci == 2))
				Ps[ri][ci] = new SGeneral(ri, ci, WHITE, this);
			if (ri == 8 && (ci == 5 || ci == 3))
				Ps[ri][ci] = new GGeneral(ri, ci, WHITE, this);
			if (ri == 8 && (ci == 4))
				Ps[ri][ci] = new King(ri, ci, WHITE, this);
		}
	}
}
void Board::LoadFile(ifstream& rdr,int *&wPs,int *&bPs)
{
	wPs = new int[8],bPs=new int[8];
	char r;
	int wTpawns =9, wTbishops=1, wTrooks=1, wTlances=2, wTknights=2, wTSgenerals = 2, wTGgeneral = 2, wTkings=1;
	int bTpawns = 9, bTbishops = 1, bTrooks = 1, bTlances = 2, bTknights = 2, bTSgenerals = 2, bTGgeneral = 2, bTkings = 1;
	for (int ri = 0; ri < 9; ri++)
	{
		for (int ci = 0; ci < 9; ci++)
		{
			rdr >> r;
			switch (r) {
			case 'x': Ps[ri][--ci]->Promote();
				break;
			case '-': Ps[ri][ci] = nullptr;
				break;
			case'P':Ps[ri][ci] = new Pawn(ri, ci, BLACK, this);
				bTpawns--;
				break;
			case'R':Ps[ri][ci] = new Rook(ri, ci, BLACK, this);
				bTrooks--;
				break;
			case'B':Ps[ri][ci] = new Bishop(ri, ci, BLACK, this);
				bTbishops--;
				break;
			case'L':Ps[ri][ci] = new Lance(ri, ci, BLACK, this);
				bTlances--;
				break;
			case'H':Ps[ri][ci] = new Knight(ri, ci, BLACK, this);
				bTknights--;
				break;
			case'S':Ps[ri][ci] = new SGeneral(ri, ci, BLACK, this);
				bTSgenerals--;
				break;
			case'G':Ps[ri][ci] = new GGeneral(ri, ci, BLACK, this);
				bTGgeneral--;
				break;
			case'K':Ps[ri][ci] = new King(ri, ci, BLACK, this);
				bTkings--;
				break;
			case'p':Ps[ri][ci] = new Pawn(ri, ci, WHITE, this);
				wTpawns--;
				break;
			case'r':Ps[ri][ci] = new Rook(ri, ci, WHITE, this);
				wTrooks--;
				break;
			case'b':Ps[ri][ci] = new Bishop(ri, ci, WHITE, this);
				wTbishops--;
				break;
			case'l':Ps[ri][ci] = new Lance(ri, ci, WHITE, this);
				wTlances--;
				break;
			case'h':Ps[ri][ci] = new Knight(ri, ci, WHITE, this);
				wTknights--;
				break;
			case's':Ps[ri][ci] = new SGeneral(ri, ci, WHITE, this);
				wTSgenerals--;
				break;
			case'g':Ps[ri][ci] = new GGeneral(ri, ci, WHITE, this);
				wTGgeneral--;
				break;
			case'k':Ps[ri][ci] = new King(ri, ci, WHITE, this);
				wTkings--;
				break;
			}
		}
	}
	bPs[0] = bTpawns;
	bPs[1] = bTbishops;
	bPs[2] = bTrooks;
	bPs[3] = bTlances;
	bPs[4] = bTknights;
	bPs[5] = bTSgenerals;
	bPs[6] = bTGgeneral;
	bPs[7] = bTkings;

	wPs[0] = wTpawns;
	wPs[1] = wTbishops;
	wPs[2] = wTrooks;
	wPs[3] = wTlances;
	wPs[4] = wTknights;
	wPs[5] = wTSgenerals;
	wPs[6] = wTGgeneral;
	wPs[7] = wTkings;
}
void Board::Draw()
{
	drawGrid(9, 9, 9, 9);
	for (int ri = 0; ri < 9; ri++)
	{
		gotoRowCol(1, 3 + 4.5 + ri * 8);
		cout << ri + 1 << " ";
		gotoRowCol(3 + 4.5 + ri*8, 1);
		cout << char('A' + ri)<<" ";
		for (int ci = 0; ci < 9; ci++)
		{
			gotoRowCol(3+4.5 + ri * 8,3 + 4.5+ ci * 8);
			if (Ps[ri][ci] == nullptr) {
				cout << '-';
			}
			else {
				Ps[ri][ci]->draw();
			}
			cout << " ";
		}
	}
}
void Board::Copy(Board* b2)
{
	for (int ri = 0; ri < 9; ri++)
	{
		for (int ci = 0; ci < 9; ci++)
		{
			this->Ps[ri][ci] = b2->Ps[ri][ci];
		}
	}
}
void Board::Move(int sri, int sci, int dri, int dci)
{
	Ps[sri][sci]->move(sri, sci, dri, dci, this);
}
void Board::Update(int sri, int sci, int dri, int dci)
{
	gotoRowCol(sri * 8 + 3 + 4.5, (8 * sci) + 3 + 4.5);
	cout << "- ";
	gotoRowCol(dri * 8 + 3 + 4.5, (8 * dci) + 3 + 4.5);
	Ps[dri][dci]->draw();
	cout << " ";
	gotoRowCol(10, 10);
}
void Board::hlt(int sri, int sci, int rdim, int cdim, colors hclr)
{
	sri = 3 + sri * (rdim-1);
	sci = 3 + sci * (cdim-1);
	gotoRowCol(sri, sci);
	SetClr(hclr, BLACK);
	drawFilledBox(sri, sci, rdim, cdim);
	SetClr(WHITE, BLACK);
}
void Board::hlt2(int sri, int sci, int rdim, int cdim, colors hclr)
{
	sri = 3 + sri * (rdim - 1);
	sci = 3 + sci * (cdim - 1);
	gotoRowCol(sri, sci);
	SetClr(hclr, BLACK);
	drawBox(sri, sci, rdim, cdim);
	SetClr(WHITE, BLACK);
}
void Board::uhlt(int sri, int sci, int rdim, int cdim)
{
	sri = 3 + sri * (rdim - 1);
	sci = 3 + sci * (cdim - 1);
	gotoRowCol(sri, sci);
	SetClr(BLACK, BLACK);
	drawFilledBox(sri, sci, rdim, cdim);
	SetClr(WHITE, BLACK);
	sri += 4.5;
	sci += 4.5;
	gotoRowCol(sri, sci);
	cout << '-';
}
void Board::uhlt2(int sri, int sci, int rdim, int cdim)
{
	sri = 3 + sri * (rdim - 1);
	sci = 3 + sci * (cdim - 1);
	gotoRowCol(sri, sci);
	SetClr(WHITE, BLACK);
	drawBox(sri, sci, rdim, cdim);
	SetClr(WHITE, BLACK);
}
void Board::highlight(int sri, int sci, int rdim, int cdim)
{
	Shogi s(0);
	int turn,ans=0;
	if (this->Ps[sri][sci]->C == WHITE)
		turn = 1;
	else turn = 0;
	
		for (int dri = 0; dri < 9; dri++)
		{
			for (int dci = 0; dci < 9; dci++)
			{
				if ((this->Ps[sri][sci]->isLegalMove(sri, sci, dri, dci, this) && this->Ps[sri][sci]->isValidDest(dri, dci, turn, this))
					&& (!s.selfCheck(this, turn, sri, sci, dri, dci)))
				{

					{
						if (this->Ps[dri][dci] == nullptr)
							hlt(dri, dci, rdim, cdim, CYAN);
						else
							hlt2(dri, dci, rdim, cdim, RED);
					}
				}
			}
		}
}
void Board::unhighlight(int sri, int sci, int rdim, int cdim)
{
	Shogi s(0);
	int turn;
	if (this->Ps[sri][sci]->C == WHITE)
		turn = 1;
	else turn = 0;
	for (int dri = 0; dri < 9; dri++)
	{
		for (int dci = 0; dci < 9; dci++)
		{
			if (this->Ps[sri][sci]->isLegalMove(sri, sci, dri, dci, this) && this->Ps[sri][sci]->isValidDest(dri, dci, turn, this)
				&& (!s.selfCheck(this, turn, sri, sci, dri, dci)))
			{

				{if (this->Ps[dri][dci] == nullptr)
					uhlt(dri, dci, rdim, cdim);
				else
					uhlt2(dri, dci, rdim, cdim);
				}
			}
		}
	}
}