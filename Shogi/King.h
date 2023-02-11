#pragma once
#include "Rook.h"
#include "Bishop.h"
#include "Piece.h"
class Board;
class King :
	public Rook , public Bishop,public Piece
{
public:
	King();
	King(int, int, colors, Board*);
	virtual void draw()override;
	virtual void write(ofstream& wtr)override;
	virtual void Promote()override;
	virtual void Demote()override;
	virtual bool isLegalMove(int sri, int sci, int dri, int dci, Board* b);
	friend bool Rook::isLegalMove(int sri, int sci, int dri, int dci, Board* b);
	virtual bool isKing()override
	{
		return true;
	}
};

