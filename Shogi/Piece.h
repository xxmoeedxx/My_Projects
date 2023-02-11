#pragma once
#include<fstream>
#include"Color.h"
#include<cmath>
class Board;
class Piece
{
protected:
	int r, c; 
public:
	bool promStatus = 0;
	Piece();
	virtual void Promote();
	virtual void Demote();
	colors C;
	Piece(int, int, colors);	
	bool notMovingBack(int sri, int dri, int turn)
{
	int t = dri - sri;
	return ((turn == 1 && t < 0) || (turn == 0 && t > 0));
}
	virtual bool isKing()
	{
		return false;
	}
	virtual bool isLegalMove(int sri, int sci, int dri, int dci, Board* b)=0;
	bool CapturedLegalMove(int ans,int sri,int sci,int dri,int dci,int turn,Board *b);
	bool isValidSource(int sri, int sci, int turn,Board *b);
	bool isValidDest(int sri, int sci, int turn, Board* b);
	void move(int sri, int sci, int dri, int dci, Board* b);
	bool isHorizontalMove(int sri, int sci, int dri, int dci);
	bool isVerticalMove(int sri, int sci, int dri, int dci);
	bool isDiagonalMove(int sri, int sci, int dri, int dci);
	bool DiagPathClear(int sri, int sci, int dri, int dci, Board* b);
	bool isHorPathClear(int sri, int sci, int dri, int dci, Board* b);
	bool isVertPathClear(int sri, int sci, int dri, int dci, Board* b);
	virtual void draw() = 0;
	virtual void write(ofstream& wtr)=0;
};

