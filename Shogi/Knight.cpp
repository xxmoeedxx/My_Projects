#include "Knight.h"
#include "GGeneral.h"
#include<iostream>
using namespace std;
Knight::Knight(int r, int c, colors clr, Board* b) :Piece(r, c, clr)
{
}
void Knight::draw()
{
	cout << ((C == BLACK) ? 'H' : 'h');
	if (Piece::promStatus)
		cout << 'x';
}
void Knight::write(ofstream& wtr)
{
	wtr << ((C == BLACK) ? 'H' : 'h');
	if (Piece::promStatus)
		wtr << 'x';
}
void Knight::Promote() {
	promStatus = true;
}
void Knight::Demote() {
	promStatus = false;
}
bool Knight::isLegalMove(int sri, int sci, int dri, int dci, Board* b)
{
	GGeneral gg;
	int Dr = abs(dri - sri), Dc = abs(dci - sci);
	bool notForward;
	if (Piece::C == WHITE)
		notForward = (dri - sri >= 0);
	else
		notForward = (dri - sri <= 0);
	if (!promStatus)
		return((Dr == 2 && Dc == 1) && !notForward);
	else
		return(gg.isLegalMove(sri,sci,dri,dci,b));
}