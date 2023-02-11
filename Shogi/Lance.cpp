#include"GGeneral.h"
#include "Lance.h"
#include<iostream>
using namespace std;
Lance::Lance(int r, int c, colors clr, Board* b) :Piece(r, c, clr)
{
}
Lance::Lance()
{

}
void Lance::draw()
{
	cout << ((C == BLACK) ? 'L' : 'l');
	if (Piece::promStatus)
		cout << 'x';
}
void Lance::write(ofstream& wtr)
{
	wtr << ((C == BLACK) ? 'L' : 'l');
	if (Piece::promStatus)
		wtr << 'x';
}
void Lance::Promote() {
	promStatus = true;
}
void Lance::Demote() {
	promStatus = false;
}
bool Lance::isLegalMove(int sri, int sci, int dri, int dci, Board* b)
{
	GGeneral gg;
	int turn;
	if (Piece::C == WHITE)
		turn = 1;
	else turn = 0;
	bool ret = (Piece::isVerticalMove(sri, sci, dri, dci)
		&& Piece::isVertPathClear(sri, sci, dri, dci, b)
		&& Piece::notMovingBack(sri, dri, turn));
	if (!promStatus)
		return ret;
	else
	return(gg.isLegalMove(sri,sci,dri,dci,b));
}