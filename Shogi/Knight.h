#pragma once
#include "Piece.h"
class Board;
class Knight :
    public Piece
{
public:
	Knight(int, int, colors, Board*);
	virtual void draw()override;
	virtual void write(ofstream& wtr)override;
	virtual void Promote()override;
	virtual void Demote()override;
	virtual bool isLegalMove(int sri, int sci, int dri, int dci, Board* b)override;
};

