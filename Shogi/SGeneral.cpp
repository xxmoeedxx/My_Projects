#include"GGeneral.h"
#include "SGeneral.h"
#include<iostream>
using namespace std;
SGeneral::SGeneral(int r, int c, colors clr, Board* b) :King(r, c, clr,b),Piece(r,c,clr)
{
}
void SGeneral::draw()
{
	cout << ((Piece::C == BLACK) ? 'S' : 's');
	if (Piece::promStatus)
		cout << 'x';
}
void SGeneral::write(ofstream& wtr)
{
	wtr << ((Piece::C == BLACK) ? 'S' : 's');
	if (Piece::promStatus)
		wtr << 'x';
}
void SGeneral::Promote() {
	Piece::promStatus = true;
}
void SGeneral::Demote() {
	Piece::promStatus = false;
}
bool SGeneral::isLegalMove(int sri, int sci, int dri, int dci, Board* b)
{
	GGeneral gg;
	bool movingBackwards;
	if(Piece::C==WHITE)
	movingBackwards = (dri - sri > 0 && dci-sci ==0);
	else
		movingBackwards = (dri - sri < 0 && dci - sci == 0);
	bool ret = (King::isLegalMove(sri, sci, dri, dci, b) &&
		!King::Rook::isHorizontalMove(sri, sci, dri, dci)
		&& !movingBackwards);
	if (!Piece::promStatus)
		return ret;
	else
		return(gg.isLegalMove(sri, sci, dri, dci, b));
}