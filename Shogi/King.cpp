#include "King.h"
#include<iostream>
using namespace std;
King::King(int r, int c, colors clr, Board* b) :Rook(r, c, clr,b),Bishop(r,c,clr,b),Piece(r,c,clr)
{
}
King::King()
{

}
void King::draw()
{
	cout << ((Piece::C == BLACK) ? 'K' : 'k');
}
void King::write(ofstream& wtr)
{
	wtr << ((Piece::C == BLACK) ? 'K' : 'k');
}
void King::Promote() {

}
void King::Demote() {

}
bool King::isLegalMove(int sri, int sci, int dri, int dci, Board* b)
{
	int Dr = abs(dri - sri);
	int Dc = abs(dci - sci);
	return((Rook::isLegalMove(sri, sci, dri, dci, b) || Bishop::isLegalMove(sri, sci, dri, dci, b))
		&& ((Dr <= 1 && Dc <= 1)));
}