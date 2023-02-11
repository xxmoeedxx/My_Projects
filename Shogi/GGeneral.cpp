#include "GGeneral.h"
#include<iostream>
using namespace std;
GGeneral::GGeneral(int r, int c, colors clr, Board* b) :King(r, c, clr,b),Piece(r,c,clr)
{
}
GGeneral::GGeneral()
{

}
void GGeneral::draw()
{
	cout << ((Piece::C == BLACK) ? 'G' : 'g');
}
void GGeneral::Promote() {

}
void GGeneral::Demote() {

}
void GGeneral::write(ofstream& wtr)
{
	wtr << ((Piece::C == BLACK) ? 'G' : 'g');
}
bool GGeneral::isLegalMove(int sri, int sci, int dri, int dci, Board* b)
{
	bool backRightDiag, backLeftDiag;
	if (Piece::C == WHITE) {
		backRightDiag = (dri - sri > 0 && dci - sci > 0);
		backLeftDiag = (dri - sri > 0 && dci - sci < 0);
	}
	else{
		backRightDiag = (dri - sri < 0 && dci - sci > 0);
	backLeftDiag = (dri - sri < 0 && dci - sci < 0);
	}
	return(King::isLegalMove(sri, sci, dri, dci, b) && !backLeftDiag && !backRightDiag);
}