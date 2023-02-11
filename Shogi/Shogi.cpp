#include "Shogi.h"
Shogi::Shogi(int a)
{

}
Shogi::Shogi()
{
	b->SetClr(WHITE, BLACK);
	b->drawFilledBox(30, 55, 7, 16);
	gotoRowCol2(33, 59);
	b->SetClr(BLACK, WHITE);
	cout << "NEW GAME";
	b->SetClr(WHITE, WHITE);
	b->drawFilledBox(40, 55, 7, 16);
	gotoRowCol2(43, 60);
	b->SetClr(BLACK, WHITE);
	cout << "RESUME";
	b->SetClr(WHITE, BLACK);
	b->drawFilledBox(50, 55, 7, 16);
	gotoRowCol2(53, 59);
	b->SetClr(BLACK, WHITE);
	cout << "LOAD GAME";
	b->SetClr(WHITE, BLACK);
	gotoRowCol2(0, 0);
	p1.c = WHITE;
	p2.c = BLACK;
	b = new Board();
}
void Shogi::NewGame()
{
	cout << "Enter Player 1(White) Name: ";
	char p1n[20],p2n[20];
	cin.getline(p1n, 20,'\n');
	p1.Name.assign(p1n);
	cout << endl;
	cout << "Enter Player 2(Black) Name: ";
	cin.getline(p2n, 20, '\n');
	p2.Name.assign(p2n);
	cout << endl;
	srand(time(0));			
	turn = rand() % 2;
	system("cls");
}
void Shogi::LoadOldGame(ifstream &rdr)
{
	p1Cap.clear();
	p2Cap.clear();
	ifstream pinfo("pinfo.txt");
	pinfo >> turn;
	pinfo.ignore();
	char p1n[20], p2n[20];
	pinfo.getline(p1n, 20, '.');
	pinfo.ignore();
	pinfo.getline(p2n, 20, '.');
	p1.Name.assign(p1n);
	p2.Name.assign(p2n);
	int* wPs, * bPs;
	b->LoadFile(rdr, wPs, bPs);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < wPs[i]; j++)
		{
			switch (i) {
			case 0:
				p2Cap.push_back(new Pawn(0, 0, BLACK, b));
				gotoRowCol2(3 + 4.5 + 8 * ((p2Cap.size() - 1) % 9), 3 + 4.5 + (p2Cap.size() / 10) * 8 + 9 * 8);
				p2Cap[p2Cap.size() - 1]->draw();
				break;
			case 1:
				p2Cap.push_back(new Bishop(0, 0, BLACK, b));
				gotoRowCol2(3 + 4.5 + 8 * ((p2Cap.size() - 1) % 9), 3 + 4.5 + (p2Cap.size() / 10) * 8 + 9 * 8);
				p2Cap[p2Cap.size() - 1]->draw();
				break;
			case 2:
				p2Cap.push_back(new Rook(0, 0, BLACK, b));
				gotoRowCol2(3 + 4.5 + 8 * ((p2Cap.size() - 1) % 9), 3 + 4.5 + (p2Cap.size() / 10) * 8 + 9 * 8);
				p2Cap[p2Cap.size() - 1]->draw();
				break;
			case 3:
				p2Cap.push_back(new Lance(0, 0, BLACK, b));
				gotoRowCol2(3 + 4.5 + 8 * ((p2Cap.size() - 1) % 9), 3 + 4.5 + (p2Cap.size() / 10) * 8 + 9 * 8);
				p2Cap[p2Cap.size() - 1]->draw();
				break;
			case 4:
				p2Cap.push_back(new Knight(0, 0, BLACK, b));
				gotoRowCol2(3 + 4.5 + 8 * ((p2Cap.size() - 1) % 9), 3 + 4.5 + (p2Cap.size() / 10) * 8 + 9 * 8);
				p2Cap[p2Cap.size() - 1]->draw();
				break;
			case 5:
				p2Cap.push_back(new SGeneral(0, 0, BLACK, b));
				gotoRowCol2(3 + 4.5 + 8 * ((p2Cap.size() - 1) % 9), 3 + 4.5 + (p2Cap.size() / 10) * 8 + 9 * 8);
				p2Cap[p2Cap.size() - 1]->draw();
				break;
			case 6:
				p2Cap.push_back(new GGeneral(0, 0, BLACK, b));
				gotoRowCol2(3 + 4.5 + 8 * ((p2Cap.size() - 1) % 9), 3 + 4.5 + (p2Cap.size() / 10) * 8 + 9 * 8);
				p2Cap[p2Cap.size() - 1]->draw();
				break;
			case 7:
				p2Cap.push_back(new King(0, 0, BLACK, b));
				gotoRowCol2(3 + 4.5 + 8 * ((p2Cap.size() - 1) % 9), 3 + 4.5 + (p2Cap.size() / 10) * 8 + 9 * 8);
				p2Cap[p2Cap.size() - 1]->draw();
				break;
			}
		}
		for (int j = 0; j < bPs[i]; j++)
		{
			switch (i) {
			case 0:
				p1Cap.push_back(new Pawn(0, 0, WHITE, b));
				gotoRowCol2(3 + 4.5 + ((p1Cap.size() / 10) * 8) + 9 * 8, 3 + 4.5 + 8 * ((p1Cap.size() - 1) % 9));
				p1Cap[p1Cap.size() - 1]->draw();
				break;
			case 1:
				p1Cap.push_back(new Bishop(0, 0, WHITE, b));
				gotoRowCol2(3 + 4.5 + ((p1Cap.size() / 10) * 8) + 9 * 8, 3 + 4.5 + 8 * ((p1Cap.size() - 1) % 9));
				p1Cap[p1Cap.size() - 1]->draw();
				break;
			case 2:
				p1Cap.push_back(new Rook(0, 0, WHITE, b));
				gotoRowCol2(3 + 4.5 + ((p1Cap.size() / 10) * 8) + 9 * 8, 3 + 4.5 + 8 * ((p1Cap.size() - 1) % 9));
				p1Cap[p1Cap.size() - 1]->draw();
				break;
			case 3:
				p1Cap.push_back(new Lance(0, 0, WHITE, b));
				gotoRowCol2(3 + 4.5 + ((p1Cap.size() / 10) * 8) + 9 * 8, 3 + 4.5 + 8 * ((p1Cap.size() - 1) % 9));
				p1Cap[p1Cap.size() - 1]->draw();
				break;
			case 4:
				p1Cap.push_back(new Knight(0, 0, WHITE, b));
				gotoRowCol2(3 + 4.5 + ((p1Cap.size() / 10) * 8) + 9 * 8, 3 + 4.5 + 8 * ((p1Cap.size() - 1) % 9));
				p1Cap[p1Cap.size() - 1]->draw();
				break;
			case 5:
				p1Cap.push_back(new SGeneral(0, 0, WHITE, b));
				gotoRowCol2(3 + 4.5 + ((p1Cap.size() / 10) * 8) + 9 * 8, 3 + 4.5 + 8 * ((p1Cap.size() - 1) % 9));
				p1Cap[p1Cap.size() - 1]->draw();
				break;
			case 6:
				p1Cap.push_back(new GGeneral(0, 0, WHITE, b));
				gotoRowCol2(3 + 4.5 + ((p1Cap.size() / 10) * 8) + 9 * 8, 3 + 4.5 + 8 * ((p1Cap.size() - 1) % 9));
				p1Cap[p1Cap.size() - 1]->draw();
				break;
			case 7:
				p1Cap.push_back(new King(0, 0, WHITE, b));
				gotoRowCol2(3 + 4.5 + ((p1Cap.size() / 10) * 8) + 9 * 8, 3 + 4.5 + 8 * ((p1Cap.size() - 1) % 9));
				p1Cap[p1Cap.size() - 1]->draw();
				break;
			}
		}
	}
	rdr.close();
}
void Shogi::SaveGame(ofstream& wtr)
{
	ofstream pinfo("pinfo.txt");
	pinfo << turn << endl;
	pinfo << p1.Name << '.'<< endl;
	pinfo << p2.Name << '.' << endl;
	for (int ri = 0; ri < 9; ri++)
	{
		for (int ci = 0; ci < 9; ci++)
		{
			if (b->Ps[ri][ci] != nullptr)
				b->Ps[ri][ci]->write(wtr);
			else
				wtr << '-';
		}
		wtr << endl;
	}
}
void Shogi::play()
{
	int cr, cc;
	while (true)
	{
		getRowColbyLeftClick(cr, cc);
		if (ClickOnNewGame(cr, cc) || ClickOnResume(cr, cc)|| ClickOnLoad(cr, cc))
		{
			break;
		}
	}
	system("cls");
	if (ClickOnNewGame(cr, cc))
	{
		NewGame();
	}
	if (ClickOnLoad(cr, cc))
	{
		ifstream rdr("LastGame.txt");
		LoadOldGame(rdr);
		if (check(b, turn))
		{
				checkMsg(turn);
		}
	}
	if (ClickOnResume(cr, cc))
	{
		ifstream rdr("Autosave.txt");
		LoadOldGame(rdr);
	}
	b->Draw();
	DisplayLoad();
	DisplaySave();
	DisplayWithdraw();
	gotoRowCol2(3, 100);
	cout << '(';
	cout << p2.Name;
	cout << ')';
	gotoRowCol2(75, 100);
	cout << '(';
	cout << p1.Name;
	cout << ')';
	
	
	do
	{
		ofstream wtr2("Autosave.txt");
		SaveGame(wtr2);
		gotoRowCol2(46, 100);
		selSourceMsg();
		gotoRowCol2(43, 100);
		eraseMsg();
		gotoRowCol2(43, 100);
		if (turn == 0)
			turnMsg(p2.Name);
		else
			turnMsg(p1.Name);
		int sr=0, sc=0, dr=0, dc=0;
		do {
			gotoRowCol2(47, 100);
			CoordSelc(sr, sc);
			if (ClickOnWithdraw(sr, sc))
			{
				break;
			}
			if (ClickOnLoadGame(sr, sc))
			{
				system("cls");
				ifstream rdr("LastGame.txt");
				LoadOldGame(rdr);
				b->Draw();
				DisplayLoad();
				DisplaySave();
				gotoRowCol2(3, 100);
				cout << '(';
				cout << p2.Name;
				cout << ')';
				gotoRowCol2(75, 100);
				cout << '(';
				cout << p1.Name;
				cout << ')';
				break;
			}
			if (ClickOnSaveGame(sr, sc))
			{
				ofstream wtr("LastGame.txt");
				SaveGame(wtr);
				gotoRowCol2(30, 100);
				cout << "Game Saved";
				Sleep(2000);
				gotoRowCol2(30, 100);
				eraseMsg();
			}
			if (isCapturedPiece(sr, sc))
				break;
		} while (sr>8||sc>8||!b->Ps[sr][sc]->isValidSource(sr, sc, turn, b));
		if (ClickOnLoadGame(sr, sc))
		{
			continue;
		}
		if (ClickOnWithdraw(sr, sc))
		{
			LossMsg(turn);
				break;
		}
		gotoRowCol2(46, 100);
		eraseMsg();
		if (isCapturedPiece(sr, sc))
		{
			HighlightForCaptured(sr, sc, dr, dc);
		}	
		else
		b->highlight(sr, sc, 9, 9);
			gotoRowCol2(46, 100);
		selDestMsg();
		do {
			gotoRowCol2(47, 100);
			CoordSelc(dr, dc);
			if (ClickOnWithdraw(dr, dc))
			{
				break;
			}
			if (ClickOnLoadGame(dr, dc))
			{
				system("cls");
				ifstream rdr("LastGame.txt");
				LoadOldGame(rdr);
				b->Draw();
				DisplayLoad();
				DisplaySave();
				gotoRowCol2(3, 100);
				cout << '(';
				cout << p2.Name;
				cout << ')';
				gotoRowCol2(75, 100);
				cout << '(';
				cout << p1.Name;
				cout << ')';
				break;
			}
			if (ClickOnSaveGame(dr, dc))
			{
				ofstream wtr("LastGame.txt");
				SaveGame(wtr);
				gotoRowCol2(30, 100);
				cout << "Game Saved";
				Sleep(2000);
				gotoRowCol2(30, 100);
				eraseMsg();
			}
			if (isCapturedPiece(dr, dc) || (dr<9 && dc<9 && b->Ps[dr][dc]->isValidSource(dr, dc, turn, b)))
			{
				if (!isCapturedPiece(sr, sc))
					b->unhighlight(sr, sc, 9, 9);
				else
					UnhighlightCaptured(sr, sc, dr, dc);
				sr = dr, sc = dc;
				if (!isCapturedPiece(sr, sc))
				b->highlight(sr, sc, 9, 9);
				else
					HighlightForCaptured(sr, sc, dr, dc);
			}
			if (isCapturedPiece(dr, dc))
			{
				if(isValidDestForCap(sr, sc, dr, dc))
					break;
			}
		} while (isCapturedPiece(sr, sc)||!b->Ps[dr][dc]->isValidDest(dr, dc, turn, b) || !b->Ps[sr][sc]->isLegalMove(sr,sc,dr,dc,b)||selfCheck(b, turn, sr, sc, dr, dc));
		if (ClickOnLoadGame(dr, dc))
		{
			continue;
		}
		if (ClickOnWithdraw(dr, dc))
		{
			LossMsg(turn);
			break;
		}
		gotoRowCol2(46, 100);
		eraseMsg();
		if (isCapturedPiece(sr, sc))
		{
			UnhighlightCaptured(sr, sc, dr, dc);
		} 
		else {
			b->unhighlight(sr, sc, 9, 9);
		}
		if (b->Ps[dr][dc] != nullptr)
		{
			if (turn == 0)
			{
				b->Ps[dr][dc]->C = BLACK;
				p2Cap.push_back(b->Ps[dr][dc]);
				gotoRowCol2(3 + 4.5 + 8 * ((p2Cap.size() - 1) % 9), 3 + 4.5 + (p2Cap.size()/9)*8 + 9 * 8);
			}
			else {
				b->Ps[dr][dc]->C = WHITE;
				p1Cap.push_back(b->Ps[dr][dc]);
				gotoRowCol2(3 + 4.5 + ((p1Cap.size() / 9) * 8) + 9 * 8, 3 + 4.5 + 8 * ((p1Cap.size() - 1)%9));
			}
			b->Ps[dr][dc]->Demote();
			b->Ps[dr][dc]->draw();
			cout << ' ';
		} //Capture
		if (isCapturedPiece(sr, sc)) {
			CapturedPieceMove(sr, sc, dr, dc,b);
			if(turn==1)
			p1Cap.erase(p1Cap.begin() + 9 * (sr - 9) + sc);
			else
			p2Cap.erase(p2Cap.begin() + 9 * (sc - 9) + sr);
			CboardUpdate(sr, sc, dr, dc);
		}
		else {
			b->Move(sr, sc, dr, dc);
			if (!b->Ps[dr][dc]->promStatus)
				OfferPromotion(dr, dc, b);
			b->Update(sr, sc, dr, dc);
		}
		gotoRowCol2(50, 100);
		eraseMsg();
		if (check(b, turn))
		{
			if (checkmate(b, turn))
			{
				checkmateMsg(turn);
				break;
			}
			else
				checkMsg(turn);
		}
		if (stalemate(b, turn))
		{
			stalemateMsg(b, turn);
			break;
		}
		turnChange();
	} while (true);
}