#pragma once
#include "Piece.h"
class Board;
class Lance :
    public Piece
{
public:
	Lance();
	Lance(int, int, colors, Board*);
	virtual void draw()override;
	virtual void write(ofstream& wtr)override;
	virtual void Promote()override;
	virtual void Demote()override;
	virtual bool isLegalMove(int sri, int sci, int dri, int dci, Board* b)override;
};	

