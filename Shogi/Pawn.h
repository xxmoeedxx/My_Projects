#pragma once
#include "Piece.h"
class Board;
class Pawn :
	public Piece
{
public:
	Pawn(int, int, colors, Board*);
	virtual void write(ofstream& wtr)override;
	virtual void draw()override;
	virtual void Promote()override;
	virtual void Demote()override;
	virtual bool isLegalMove(int sri, int sci, int dri, int dci, Board* b)override;
};

