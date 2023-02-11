#pragma once
#include "King.h"
#include "Piece.h"
class Board;
class SGeneral :
    public King,public Piece
{
public:
	SGeneral(int, int, colors, Board*);
	virtual void draw()override;
	virtual void write(ofstream& wtr)override;
	virtual void Promote()override;
	virtual void Demote()override;
	virtual bool isLegalMove(int sri, int sci, int dri, int dci, Board* b)override;
};

