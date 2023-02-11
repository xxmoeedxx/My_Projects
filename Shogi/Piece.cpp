#include "Piece.h"
#include"Board.h"
Piece::Piece(int _r, int _c, colors clr)
{
	this->r = _r;
	this->c = _c;
	C = clr;
}
Piece::Piece()
{

}
void Piece::Promote() {

}
void Piece::Demote() {

}
bool isBlack(int r, int c, Board *board)
{
	if (board->Ps[r][c] != nullptr)
		return(board->Ps[r][c]->C == BLACK);
	else return false;
}
bool isWhite(int r, int c, Board *board)
{
	if (board->Ps[r][c] != nullptr)
	return(board->Ps[r][c]->C == WHITE);
	else return false;
}
bool Piece::isValidSource(int sri, int sci, int turn, Board* b)
{
	if (sri >= 0 && sri <= 8
		&& sci >= 0 && sci <= 8)
	{
		if (turn == 0)
		{
			return isBlack(sri, sci, b);
		}
		if (turn == 1)
		{
			return isWhite(sri, sci, b);
		}

	}
	else return false;
}
bool Piece::isValidDest(int sri, int sci, int turn, Board* b)
{
	return((sri >= 0 && sri <= 8
		&& sci >= 0 && sci <= 8) && !(isValidSource(sri, sci, turn, b)));
}
bool Piece::CapturedLegalMove(int ans,int sri,int sci,int dri,int dci,int turn,Board *b)
{
	if (ans == 0)
	{
		return false;	
	}
	else
	{
		return((dri >= 0 && dri <= 8
			&& dci >= 0 && dci <= 8) && !(isValidSource(dri, dci, turn, b)));
	}
}
void Piece::move(int sri, int sci, int dri, int dci, Board* b)
{
	b->Ps[dri][dci] = b->Ps[sri][sci];
	b->Ps[sri][sci] = nullptr;
}
bool Piece::isHorizontalMove(int sri, int sci, int dri, int dci)
{
	return abs(sri) == abs(dri);
}
bool Piece::isVerticalMove(int sri, int sci, int dri, int dci)
{
	return abs(sci) == abs(dci);
}
bool Piece::isDiagonalMove(int sri, int sci, int dri, int dci)
{
	return abs(sri - dri) == abs(sci - dci);
}
bool Piece::isHorPathClear(int sri, int sci, int dri, int dci, Board* b)
{
	int cs = 0, ce = 0;
	if (dci > sci)
	{
		cs = sci + 1;
		ce = dci - 1;
	}
	if (dci < sci)
	{
		cs = dci + 1;
		ce = sci - 1;
	}
	for (int i = cs; i <= ce; i++)
	{
		if (b->Ps[sri][i] != nullptr)
			return false;
	}
	return true;
}
bool Piece::isVertPathClear(int sri, int sci, int dri, int dci, Board* b)
{
	int rs = 0, re = 0;
	if (dri > sri)
	{
		rs = sri + 1;
		re = dri - 1;
	}
	if (dri < sri)
	{
		rs = dri + 1;
		re = sri - 1;
	}
	for (int i = rs; i <= re; i++)
	{
		if (b->Ps[i][sci] != nullptr)
			return false;
	}
	return true;
}
bool Piece::DiagPathClear(int sri, int sci, int dri, int dci, Board* b)
{
	int Dr = dri - sri, Dc = dci - sci;
	int t = abs(dri - sri);
	if (Dr > 0 && Dc > 0)
	{
		for (int i = 1; i < t; i++)
		{
			if (b->Ps[sri + i][sci + i] != nullptr)
				return false;
		}
	}
	if (Dr > 0 && Dc < 0)
	{
		for (int i = 1; i < t; i++)
		{
			if (b->Ps[sri + i][sci - i] != nullptr)
				return false;
		}
	}
	if (Dr < 0 && Dc < 0)
	{
		for (int i = 1; i < t; i++)
		{
			if (b->Ps[sri - i][sci - i] != nullptr)
				return false;
		}
	}
	if (Dr < 0 && Dc > 0)
	{
		for (int i = 1; i < t; i++)
		{
			if (b->Ps[sri - i][sci + i] != nullptr)
				return false;
		}
	}
	return true;
}
