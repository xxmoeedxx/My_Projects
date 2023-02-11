#include"GGeneral.h"
#include "Pawn.h"
#include"Board.h"
#include<iostream>
using namespace std;
Pawn::Pawn(int r, int c, colors clr, Board* b) :Piece(r, c, clr)
{
}
void Pawn::draw()
{
	cout << ((C == BLACK) ? 'P' : 'p');
	if (Piece::promStatus)
		cout << 'x';
}
void Pawn::write(ofstream& wtr)
{
	wtr << ((C == BLACK) ? 'P' : 'p');
	if (Piece::promStatus)
		wtr << 'x';
}
void Pawn::Promote() {
	promStatus = true;
}
void Pawn::Demote() {
	promStatus = false;
}
bool Pawn::isLegalMove(int sri, int sci, int dri, int dci, Board* b)
{
	GGeneral gg;
	int x, Dr = abs(dri - sri), Dc = abs(dci - sci);
	x = 1;
	int turn;
	if (C == WHITE)
		turn = 1;
	else
		turn = 0;
	bool ret= (Piece::isVerticalMove(sri, sci, dri, dci) && Dr <= x && Piece::notMovingBack(sri, dri, turn) &&
		Piece::isVertPathClear(sri, sci, dri, dci, b));
	if (!promStatus)
		return ret;
	else return(gg.isLegalMove(sri, sci, dri, dci, b));
}