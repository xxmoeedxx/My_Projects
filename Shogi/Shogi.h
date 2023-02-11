#pragma once
#include<iostream>
#include<ctime>
#include<vector>
#include"Board.h"
#include"Player.h"
#include"Piece.h"
class Shogi
{
	bool noPawnsVertically(int dci)
	{
		for (int i = 0; i < 9; i++)
		{
			if (b->Ps[i][dci] != nullptr)
			{
				Pawn* p = dynamic_cast<Pawn*>(b->Ps[i][dci]);
				if (p != nullptr)
				{
					if ((p->C == BLACK && turn == 0)|| (p->C == WHITE && turn == 1))
						return false;
				}
			}
		}
		return true;
	}
	int turn;
	vector <Piece*> p1Cap{};
	vector <Piece*> p2Cap{};
	void gotoRowCol2(int rpos, int cpos)
	{
		COORD scrn;
		HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
		scrn.X = cpos;
		scrn.Y = rpos;
		SetConsoleCursorPosition(hOuput, scrn);
	}
	Board *b;
	Player p1, p2;
	void DisplayLoad()
	{
		b->drawFilledBox(20, 100, 7, 17);
		gotoRowCol2(23, 104);
		b->SetClr(BLACK, WHITE);
		cout << "LOAD GAME";
		b->SetClr(WHITE, BLACK);
	}
	void DisplaySave()
	{
		b->drawFilledBox(10, 100, 7, 17);
		gotoRowCol2(13, 104);
		b->SetClr(BLACK, WHITE);
		cout << "SAVE GAME";
		b->SetClr(WHITE, BLACK);
	}
	void DisplayWithdraw()
	{
		b->drawFilledBox(61, 100, 7, 17);
		gotoRowCol2(64, 104);
		b->SetClr(BLACK, WHITE);
		cout << "WITHDRAW";
		b->SetClr(WHITE, BLACK);
	}
	bool ClickOnNewGame(int sr,int sc)
	{
		return (sr >= 30 && sr <= 37 && sc >= 55 && sc <= 72);
	}
	bool ClickOnLoadGame(int sr, int sc)
	{
		return (sr >= 20 && sr <= 37 && sc >= 100 && sc <= 117);
	}
	bool ClickOnSaveGame(int sr, int sc)
	{
		return (sr >= 10 && sr <= 27 && sc >= 100 && sc <= 117);
	}
	bool ClickOnWithdraw(int sr, int sc)
	{
		return (sr >= 61 && sr <= 78 && sc >= 100 && sc <= 117);
	}
	bool ClickOnResume(int sr, int sc)
	{
		return (sr >= 40 && sr <= 47 && sc >= 55 && sc <= 72);
	}
	bool ClickOnLoad(int sr, int sc)
	{
		return (sr >= 50 && sr <= 57 && sc >= 55 && sc <= 72);
	}
	void turnChange()
	{
		turn = (turn + 1) % 2;
	}
	void LoadOldGame(ifstream& rdr);
	void SaveGame(ofstream& rdr);
	void NewGame();
public:
	Shogi();
	Shogi(int);
	void play();
	void getRowColbyLeftClick(int& rpos, int& cpos)
	{
		HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
		DWORD Events;
		INPUT_RECORD InputRecord;
		SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
		do
		{
			ReadConsoleInput(hInput, &InputRecord, 1, &Events);
			if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
				rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
				break;
			}
		} while (true);
	}
	void CoordSelc(int &x, int &y)
	{
		getRowColbyLeftClick(x, y);
		if (ClickOnLoadGame(x, y)|| ClickOnSaveGame(x, y) || ClickOnWithdraw(x, y))
		{
			return;
		}
		else {
			x -= 3;
			x /= 8;
			y -= 3;
			y /= 8;
		}
	}
	bool isCapturedPiece(int sri,int sci)
	{
		if (turn == 1)
		{
			if (p1Cap.size() == 0)
				return false;
			return(sci<9 && sri > 8 && sri - 9 <= p1Cap.size() / 9 && sri/9 -1 <= p1Cap.size()/9
				&& sci+9*(sri%9)< p1Cap.size());
		}
		else 
		{
			if (p2Cap.size() == 0)
				return false;
			return(sri < 9 && sci>8 && sci-9<=p2Cap.size()/9 && sci/9-1<=p2Cap.size()/9
				&& sri + 9 * (sci % 9) < p2Cap.size());
		}
	}
	void UnhighlightCaptured(int sr,int sc,int dri,int dci)
	{
		int ans = 1;
		if (turn == 0)
		{
			for (int dri = 0; dri < 9; dri++)
				for (int dci = 0; dci < 9; dci++)
					if (p2Cap[sc - 9 + sr]->CapturedLegalMove(ans, sr, sc, dri, dci, turn, b)) {
						{
							{
								if (b->Ps[dri][dci] == nullptr)
									b->uhlt(dri, dci, 9, 9);
							}
						}
					}
		}
		else
		{
			for (int dri = 0; dri < 9; dri++)
				for (int dci = 0; dci < 9; dci++)
					if (p1Cap[sr - 9]->CapturedLegalMove(ans, sr, sc, dri, dci, turn, b)) {
						{
							{
								if (b->Ps[dri][dci] == nullptr)
									b->uhlt(dri, dci, 9, 9);
							}
						}
					}
		}
	}
	bool pawnDoesNotCauseCheck(int sr, int sc, int dr, int dc,Board *b)
	{
		Pawn* p;
		if(turn==1)
		p = dynamic_cast<Pawn*>(p1Cap[9 * (sr - 9) + sc]);
		else
			p = dynamic_cast<Pawn*>(p2Cap[9 * (sc - 9) + sr]);
		if (p != nullptr)
		{
			Board* u = new Board;
			u->Copy(b);
			King* k = dynamic_cast <King*> (u->Ps[dr][dc]);
			CapturedPieceMove(sr, sc, dr, dc, u);
			return (k == nullptr && !check(u, turn));
		}
		else return true;
	}
	void HighlightForCaptured(int sr,int sc,int dr,int dc)
	{
		int ans = 1;
		if (turn == 0)
		{
			for (int dri = 0; dri < 9; dri++)
				for (int dci = 0; dci < 9; dci++) {
					if (p2Cap[sc - 9 +sr]->CapturedLegalMove(ans, sr, sc, dri, dci, turn, b)
						&& pawnDoesNotCauseCheck(sr, sc, dri, dci, b) &&isValidDestForCap(sr,sc,dri,dci)
						&& !selfCheck(b, turn, sr, sc, dri, dci)) {
							{
								{
									if (b->Ps[dri][dci] == nullptr)
										b->hlt(dri, dci, 9, 9, CYAN);
								}
							}
					}
				}
		}
		else {
			for (int dri = 0; dri < 9; dri++)
				for (int dci = 0; dci < 9; dci++)
					if (p1Cap[sr - 9]->CapturedLegalMove(ans, sr, sc, dri, dci, turn, b)
						&& pawnDoesNotCauseCheck(sr, sc, dri, dci, b)
						&& !selfCheck(b, turn, sr, sc, dri, dci)
						&& isValidDestForCap(sr, sc, dri, dci)) {
							{
								if (b->Ps[dri][dci] == nullptr)
									b->hlt(dri, dci, 9, 9, CYAN);
							}
						}
					
		}
	}
	void CboardUpdate(int sri,int sci,int dri,int dci)
	{
		if (turn == 1)
		{
			int i;
			for (i = 0; sci + i + (sri - 9) * 9 < p1Cap.size(); i++)
			{
				gotoRowCol2((sri + (sci + i) / 9) * 8 + 3 + 4.5, (sci + i) % 9 * 8 + 3 + 4.5);
				p1Cap[sci + (sri - 9) * 9 + i]->draw();
			}
			gotoRowCol2((sri + (sci + i) / 9) * 8 + 3 + 4.5, (sci + i) % 9 * 8 + 3 + 4.5);
			cout << "  ";
		}
		else
		{
			int i;
			for (i = 0; sri + i + (sci - 9) * 9 < p2Cap.size(); i++)
			{
				gotoRowCol2((sri+i)%9 * 8 + 3 + 4.5, (sci+(sri+i)/9) * 8 + 3 + 4.5);
				p2Cap[sri + (sci-9)*9 + i]->draw();
			}
			gotoRowCol2((sri + i) % 9 * 8 + 3 + 4.5, (sci + (sri + i) / 9) * 8 + 3 + 4.5);
			cout << "  ";
		}
		gotoRowCol2(dri * 8 + 3 + 4.5, dci * 8 + 3 + 4.5);
		b->Ps[dri][dci]->draw();
	}
	void CapturedPieceMove(int sri,int sci,int dri,int dci,Board *b)
	{
		if (turn == 1)
		{
			b->Ps[dri][dci] = p1Cap[9 * (sri - 9) + sci];
			
		}
		else
		{
			b->Ps[dri][dci] = p2Cap[9 * (sci - 9) + sri];
		}
	}
	void turnMsg(string n)
	{
		cout << n << "'s turn\n";
	}
	void eraseMsg()
	{
		cout << "                                       ";
	}
	void selSourceMsg()
	{
		cout << "Pick any piece: \n";
	}
	void selDestMsg()
	{
		cout << "Now, drop the piece: \n";
	}
	void findKing(int& kr, int& kc, Board *b, int t)
	{

		for (int r = 0; r < 9; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				if(b->Ps[r][c]!=nullptr)
				if ((b->Ps[r][c]->isKing() && t == 0 && b->Ps[r][c]->C==BLACK) || t == 1 && b->Ps[r][c]->isKing() && b->Ps[r][c]->C == WHITE)
				{
					kr = r; kc = c;
					return;
				}
			}
		}
	}
	bool check(Board *b, int t)
	{
		int kr, kc;
		t=(t + 1) % 2;
		findKing(kr, kc, b, t);
		t = (t + 1) % 2;

		for (int sri = 0; sri < 9; sri++)
		{
			for (int sci = 0; sci < 9; sci++)
			{
				if (b->Ps[sri][sci] != nullptr)
				if (b->Ps[sri][sci]->isLegalMove(sri, sci, kr, kc, b) && b->Ps[sri][sci]->isValidSource(sri, sci, t, b) && b->Ps[sri][sci]->isValidDest(kr, kc, t, b))
				{
					return true;
				}
			}
		}
		return false;
	}
	void checkMsg(int t)
	{
		string Ns;
		t = (t + 1) % 2;
		gotoRowCol2(50, 100);
		if (t == 0)
			Ns = p2.Name;
		else
			Ns = p1.Name;
		cout << Ns << " is under check";
	}
	void PromotePiece(int dri,int dci,Board *b)
	{
			b->Ps[dri][dci]->Promote();
	}
	void OfferPromotion(int dri, int dci, Board* b)
	{
		if ((turn == 0 && dri >= 6 && dri < 8) || (turn == 1 && dri <= 2 && dri > 0))
		{
			gotoRowCol2(50, 100);
			cout << "Do you want to promote?";
			b->drawBox(52, 100, 5, 5);
			gotoRowCol2(54, 102);
			cout << char(251);
			b->drawBox(52, 115, 5, 5);
			gotoRowCol2(54, 117);
			cout << 'X';
			gotoRowCol2(50, 125);

			int respX, respY;
			do {
				getRowColbyLeftClick(respX, respY);
				if (respX >= 52 && respX <= 57)
				{
					if (respY >= 100 && respY <= 105)
					{
						PromotePiece(dri, dci, b);
						break;
					}
					if (respY >= 115 && respY <= 120)
					{
						break;
					}
				}
			} while (true);


			gotoRowCol2(50, 100);
			eraseMsg();
			b->SetClr(BLACK, BLACK);
			b->drawBox(52, 100, 5, 5);
			gotoRowCol2(54, 102);
			cout << ' ';
			b->drawBox(52, 115, 5, 5);
			gotoRowCol2(54, 117);
			cout << ' ';
			b->SetClr(WHITE, BLACK);
		}
		if ((turn == 0 && dri == 8) || (turn == 1 && dri == 0))
		{
			PromotePiece(dri, dci, b);
		}
	}
	bool selfCheck(Board *b, int t, int sri, int sci, int dri, int dci)
	{
		Board* u=new Board;
		u->Copy(b);
		if (isCapturedPiece(sri,sci))
			CapturedPieceMove(sri, sci, dri, dci,u);
		else
		u->Move(sri, sci, dri, dci);
		t = (t + 1) % 2;
		bool ret= check(u, t);
		t = (t + 1) % 2;
		return ret;
	}
	bool isValidDestForCap(int sr, int sc, int dr, int dc)
	{
		if (turn == 1) {
			Knight* k = dynamic_cast<Knight*>(p1Cap[sc + (sr - 9) * 9]);
			Pawn* p = dynamic_cast<Pawn*>(p1Cap[sc + (sr - 9) * 9]);
			Lance* l = dynamic_cast<Lance*>(p1Cap[sc + (sr - 9) * 9]);
			bool ret = p1Cap[sc + (sr - 9) * 9]->CapturedLegalMove(isCapturedPiece(sr, sc), sr, sc, dr, dc, turn, b)
				&& pawnDoesNotCauseCheck(sr, sc, dr, dc, b);
			if (k == nullptr && p == nullptr && l == nullptr)
				return ret;
			else if (p != nullptr)
			{
				return (dr > 0 && ret && noPawnsVertically(dc));
			}
			else if(l!=nullptr)
				return (dr > 0 && ret);
			else return(dr > 1 && ret);
		}
		if (turn == 0) {
			Knight* k = dynamic_cast<Knight*>(p2Cap[sr + (sc - 9) * 9]);
			Pawn* p = dynamic_cast<Pawn*>(p2Cap[sr + (sc - 9) * 9]);
			Lance* l = dynamic_cast<Lance*>(p2Cap[sr + (sc - 9) * 9]);
			bool ret = (p2Cap[sr + (sc - 9) * 9]->CapturedLegalMove(isCapturedPiece(sr, sc), sr, sc, dr, dc, turn, b)
				&& pawnDoesNotCauseCheck(sr, sc, dr, dc, b));
			if (k == nullptr && p == nullptr && l == nullptr)
				return ret;
			else if (p != nullptr)
			{
				return (dr < 8 && ret && noPawnsVertically(dc));
			}
			else if (l != nullptr)
				return (dr < 8 && ret);
			else return(dr < 7 && ret);
		}
		return false;
	}
	bool canIMove(Board *b, int t)
	{
		Board *u=new Board;
		u->Copy(b);
		for (int r = 0; r < 9; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				for (int dr = 0; dr < 9; dr++)
				{
					for (int dc = 0; dc < 9; dc++)
					{
						if (u->Ps[r][c] != nullptr)
						if (u->Ps[r][c]->isValidSource(r, c, t, b) && u->Ps[r][c]->isValidDest(dr, dc, t, b) && u->Ps[r][c]->isLegalMove(r, c, dr, dc, b) && !selfCheck(b, t, r, c, dr, dc))
							return true;
					}
				}
			}
		}
		for (int r = 9; r < 11; r++)
		{
			for (int c = 9; c < 11; c++)
			{
				for (int dr = 0; dr < 9; dr++)
				{
					for (int dc = 0; dc < 9; dc++)
					{
						if (isCapturedPiece(r, c)) {
							if (isValidDestForCap(r,c,dr,dc)  && !selfCheck(b, t, r, c, dr, dc))
								return true;
						}
					}
				}
			}
		}
		return false;
	}
	bool checkmate(Board* b, int t)
	{
		t = (t + 1) % 2;
		bool ret = (!canIMove(b, t) && check(b, (t+1)%2));
		t = (t + 1) % 2;
		return ret;
	}
	void LossMsg(int t)
	{
		gotoRowCol2(50, 100);
		if (t == 0)
			cout <<  p2.Name << " lost!";
		else
			cout <<  p1.Name << " lost!";
		gotoRowCol2(100, 0);
	}
	void checkmateMsg(int t)
	{
			gotoRowCol2(50, 100);
			if(t==0)
			cout << "Checkmate!" << p2.Name << " won!";
			else
				cout << "Checkmate!" << p1.Name << " won!";
			gotoRowCol2(100, 0);
	}
	bool stalemate(Board *b, int t)
	{
		t = (t + 1) % 2;;
		bool ret = (!canIMove(b, t) && !check(b, t));
		t = (t + 1) % 2;;
		return ret;
	}
	void stalemateMsg(Board *b, int t)
	{
			gotoRowCol2(50, 100);
			t = (t + 1) % 2;
			if(t==1)
			cout << p1.Name << " is out of legal moves!Game Drawn";
			else
				cout << p2.Name << " is out of legal moves!Game Drawn";
	}

	~Shogi()
	{
		delete[]b;
	}
};

