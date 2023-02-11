#include "Rook.h"
#include"Piece.h"
#include"King.h"
#include<iostream>
using namespace std;
Rook::Rook(int r, int c, colors clr, Board* b) :Piece(r, c, clr)
{
}
Rook::Rook()
{

}
void Rook::draw()
{
	cout << ((C == BLACK) ? 'R' : 'r');
	if (Piece::promStatus)
		cout << 'x';
}
void Rook::write(ofstream& wtr)
{
	wtr << ((C == BLACK) ? 'R' : 'r');
	if (Piece::promStatus)
		wtr << 'x';
}
void Rook::Promote()
{
	promStatus = true;
}
void Rook::Demote()
{
	promStatus = false;
}
bool Rook::isLegalMove(int sri, int sci, int dri, int dci, Board* b)
{
	King King;
	if (!promStatus)
		return((Piece::isVertPathClear(sri, sci, dri, dci, b) && Piece::isVerticalMove(sri, sci, dri, dci)) ||
			(Piece::isHorizontalMove(sri, sci, dri, dci) && Piece::isHorPathClear(sri, sci, dri, dci, b)));
	else
		return(((Piece::isVertPathClear(sri, sci, dri, dci, b) && Piece::isVerticalMove(sri, sci, dri, dci)) ||
			(Piece::isHorizontalMove(sri, sci, dri, dci) && Piece::isHorPathClear(sri, sci, dri, dci, b))) || King.isLegalMove(sri,sci,dri,dci,b));
}