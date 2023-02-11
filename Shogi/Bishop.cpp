#include"King.h"
#include "Bishop.h"
#include<iostream>
using namespace std;
Bishop::Bishop(int r, int c, colors clr, Board* b) :Piece(r, c, clr)
{
}
Bishop::Bishop()
{

}
void Bishop::draw()
{
	cout << ((C == BLACK) ? 'B' : 'b');
	if (Piece::promStatus)
		cout << 'x';
}
void Bishop::write(ofstream& wtr)
{
	wtr << ((C == BLACK) ? 'B' : 'b');
	if (Piece::promStatus)
		wtr << 'x';
}
void Bishop::Promote()
{
	promStatus = true;
}
void Bishop::Demote()
{
	promStatus = false;
}
bool Bishop::isLegalMove(int sri, int sci, int dri, int dci, Board* b)
{
	King King;
	if (!promStatus)
		return(Piece::isDiagonalMove(sri, sci, dri, dci) &&
			Piece::DiagPathClear(sri, sci, dri, dci, b));
	else return((Piece::isDiagonalMove(sri, sci, dri, dci) &&
		Piece::DiagPathClear(sri, sci, dri, dci, b)) || King.isLegalMove(sri,sci,dri,dci,b));
}