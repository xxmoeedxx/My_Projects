#include<ctime>
#include<cstdlib>
#include<iostream>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<string>
using namespace std;

#define p1_up 72
#define p1_down 80
#define p1_left 75
#define p1_right 77
#define p2_up 119
#define p2_down 115
#define p2_left 97
#define p2_right 100

struct pos
{
	int row;
	int col;
};
struct snake
{
	string name;
	int size;
	pos* pos;
	char hsym;
	char sym;
	int score;
	char direction;
};

void SetClr(int tcl, int bcl)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
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
void PrintBox(int sr, int sc, int rdim, int cdim, char sym)
{
	for (int r = 0; r < rdim; r++)
	{
		for (int c = 0; c < cdim; c++)
		{
			gotoRowCol(sr + r, sc + c);
			cout << sym;
		}
	}
}
void PrintHBox(int sr, int sc, int rdim, int cdim, char sym)
{
	SetClr(8, 0);
	for (int r = 0; r < rdim; r++)
	{
		for (int c = 0; c < cdim; c++)
		{
			if (r == 0 || r == rdim - 1||c==0||c==cdim-1)
			{
				gotoRowCol(sr + r, sc + c);
				cout << sym;
			}
		}
	}
	SetClr(15, 0);
}
void displayTarget(const int& target)
{
	gotoRowCol(1, 3);
	cout << "Target: " << target;
}
void displayTwoButtons()
{
	SetClr(15, 0);
	PrintBox(15, 38, 5, 18, -37);
	gotoRowCol(17, 41); SetClr(0, 15);
	cout << "Single Player"; SetClr(15, 0);
	PrintBox(21, 38, 5, 18, -37); SetClr(0, 15); gotoRowCol(23, 42);
	cout << "Two Players"; SetClr(15, 0);
	gotoRowCol(30, 0);
}
void displayStartingMenu()
{
	cout << "\t\t\t\t*****              *                    \n";
	cout << "\t\t\t\t*                  *  *  ***             \n";
	cout << "\t\t\t\t***** *****  ****  * *  *   *             \n";
	cout << "\t\t\t\t    * *   * *   *  **   *****         \n";
	cout << "\t\t\t\t    * *   * *   *  * *  *                  \n";
	cout << "\t\t\t\t***** *   *  ***** *  *  ****            \n";
	cout << "\n\n\n\n\n\t\t\t\t       Select a mode:                       \n";
	displayTwoButtons();
}
void getUserResponse(int& N)
{
	int r, c;
	N = 0;
	do {
		getRowColbyLeftClick(r, c);
		if ((r >= 15 && r <= 20) && (c >= 38 && c <= 56))
			N = 1;
		else if ((r >= 21 && r <= 26) && (c >= 38 && c <= 56))
			N = 2;
	} while (N == 0);
}
void initp1(snake *a,char &fsym,pos* &fpos, const int N,int t[], int& target)
{
	for (int i = 0; i < 4; i++)
	{
		t[i] = 0;
	}
	srand(time(0));
	target = 20 + (rand() % 16);
	int r = 15;
	int nr = 3;
	fpos = new pos[N];
	for (int i = 0; i < N; i++)
	{
		gotoRowCol(nr, 30);
		cout << "Enter Player " << i + 1 << " Name: ";
		cin >> a[i].name;
		fsym = 157;
		a[i].direction = p1_right;
		a[i].hsym = 'O';
		a[i].sym = 254;
		a[i].score = 0;
		a[i].size = 4;
		a[i].pos = new pos[a[i].size];
		a[i].pos[0].row = r;
		a[i].pos[0].col = 20;
		fpos[i].row = 0;
		fpos[i].col = 0;
		for (int j = 1; j < a[i].size; j++)
		{
			a[i].pos[j].row = r;
			a[i].pos[j].col = 20 - j;
		}
		r += 9;
		nr += 2;
	}
}
void displayScore(snake x, int num)
{
	if (num == 0)
	{
		gotoRowCol(1, 65); cout << x.name <<"'s score: " << x.score;
	}
	else {
		gotoRowCol(1, 110);
		cout << x.name <<"'s score: "<< x.score;
	}
	gotoRowCol(50, 0);
}
void displaySnakeNScore(snake *x,const int N)
{
	int color = 11;
	for (int i = 0; i < N; i++)
	{
		SetClr(color, 0);
		for (int j = 1; j < x[i].size; j++)
		{
			gotoRowCol(x[i].pos[j].row, x[i].pos[j].col);
			cout << x[i].sym;
		}
		gotoRowCol(x[i].pos[0].row, x[i].pos[0].col);
		cout << x[i].hsym;
		displayScore(x[i], i);
		color++;
	}
	SetClr(15, 0);
	gotoRowCol(60, 0);
}
void shift(snake x)
{
	for (int i = x.size - 1; i > 0; i--)
	{
		x.pos[i] = x.pos[i - 1];
	}
}
void moveSnake(snake* x, pos Dim, const int N)
{
	for (int i = 0; i < N; i++)
	{
		switch (x[i].direction)
		{
			case p1_right:
			case p2_right:
			{
				shift(x[i]);
				x[i].pos[0].col++;
				
			}

			break;
			case p1_left:
			case p2_left:
			{
				shift(x[i]);
				x[i].pos[0].col--;
				
			}
			break;
			case p1_up:
			case p2_up:
			{
				shift(x[i]);
				x[i].pos[0].row--;
				
			}
			break;
			case p1_down:
			case p2_down:
			{
				shift(x[i]);
				x[i].pos[0].row++;
				
			}
			break;
		}

	}
}
void eraseSnake(snake *x,const int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < x[i].size; j++)
		{
			gotoRowCol(x[i].pos[j].row, x[i].pos[j].col);
			cout << " ";
		}
	}
	gotoRowCol(60, 0);
}
void changeDirection(snake *p,char &c)
{
	switch (c = _getch())
	{
	case p1_right:
		if (p[0].direction != p1_left)
			p[0].direction = p1_right;
		break;
	case p1_down:
		if (p[0].direction != p1_up)
			p[0].direction = p1_down;
		break;
	case p1_up:
		if (p[0].direction != p1_down)
			p[0].direction = p1_up;
		break;
	case p1_left:
		if (p[0].direction != p1_right)
			p[0].direction = p1_left;
		break;
	case p2_right:
		if (p[1].direction != p2_left)
			p[1].direction = p2_right;
		break;
	case p2_down:
		if (p[1].direction != p2_up)
			p[1].direction = p2_down;
		break;
	case p2_up:
		if (p[1].direction != p2_down)
			p[1].direction = p2_up;
		break;
	case p2_left:
		if (p[1].direction != p2_right)
			p[1].direction = p2_left;
		break;
	}
}
bool touchingSnakeTail(snake s, pos fpos)
{
	for (int i = 0; i < s.size; i++)
	{
		if (fpos.row == s.pos[i].row && fpos.col == s.pos[i].col)
			return true;
	}
	return false;
}
bool foodOnfood(pos* fpos, const int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i != j && fpos[i].row == fpos[j].row && fpos[i].col == fpos[j].col)
				return true;
		}
		return false;
	}
}
void getFood(pos Dim,snake *s,char fsym,pos *fpos, const int index, const int N)
{
	srand(time(0));
	SetClr(6, 0);
	for (int i = 0; i < N; i++)
	{
		do {
			fpos[index].row = 6 + (rand() % (Dim.row - 2));
			fpos[index].col = 2 + (rand() % (Dim.col - 2));
		} while (touchingSnakeTail(s[i],fpos[index]) || foodOnfood(fpos,N));
	}
	gotoRowCol(fpos[index].row, fpos[index].col);
	cout << fsym;
	SetClr(15, 0);
}
bool foodEaten(snake a,pos fpos)
{
	return(a.pos[0].row == fpos.row && a.pos[0].col==fpos.col);
}
void increaseSnakeSize(snake &s)
{
	snake temp=s;
	temp.size = s.size + 1;
	temp.pos = new pos[temp.size];
	for (int i = 0; i < temp.size-1; i++)
	{
		temp.pos[i] = s.pos[i];
	}
	switch (temp.direction)
	{
	case p1_down:
	case p2_down:
		temp.pos[temp.size - 1].row = temp.pos[s.size - 1].row - 1;
		temp.pos[temp.size - 1].col = temp.pos[s.size - 1].col;
		break;
	case p1_up:
	case p2_up:
		temp.pos[temp.size - 1].row = temp.pos[s.size - 1].row + 1;
		temp.pos[temp.size - 1].col = temp.pos[s.size - 1].col;
		break;
	case p1_right:
	case p2_right:
		temp.pos[temp.size - 1].row = temp.pos[s.size - 1].row;
		temp.pos[temp.size - 1].col = temp.pos[s.size - 1].col-1;
		break;
	case p1_left:
	case p2_left:
		temp.pos[temp.size - 1].row = temp.pos[s.size - 1].row;
		temp.pos[temp.size - 1].col = temp.pos[s.size - 1].col+1;
		break;
	}
	delete[]s.pos;
	s.pos = temp.pos;
	s.size++;
}
bool snakeTouchingItself(snake s)
{
	for (int i = 1; i < s.size; i++)
	{
		if (s.pos[0].row == s.pos[i].row && s.pos[0].col == s.pos[i].col)
			return true;
	}
	return false;
}
bool anySnakeTouchingItself(snake* s, const int N)
{
	for (int j = 0; j < N; j++)
	{
		for (int i = 1; i < s[j].size; i++)
		{
			if (s[j].pos[0].row == s[j].pos[i].row && s[j].pos[0].col == s[j].pos[i].col)
				return true;
		}
	}
	return false;
}
void showGameEndMsg1p()
{
	gotoRowCol(47, 30);
	cout << "GAME OVER!";
	gotoRowCol(57, 30);
}
void showGameEndMsg2p(string Name)
{
	gotoRowCol(47, 30);
	cout << Name << " WON!";
	gotoRowCol(57, 30);
}
bool boundaryTouch(snake x,pos Dim)
{
		return ((x.pos[0].row == 5) || (x.pos[0].row == Dim.row + 4)
			|| (x.pos[0].col == Dim.col) || (x.pos[0].col == 1));
}
void snakeToSnakeTouchPenalty(snake* a, const int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for(int k=0;k<a[j].size;k++)
			if (i != j && (a[i].pos[0].row == a[j].pos[k].row 
				&& a[i].pos[0].col == a[j].pos[k].col))
			{
				if(a[i].score - 5>=0)
				a[i].score -= 5;
				break;
			}
		}
	}
}
bool anyBoundaryTouch(snake *x, pos Dim,const int N)
{
	for (int i = 0; i < N; i++)
	{
		if (((x[i].pos[0].row == 5) || (x[i].pos[0].row == Dim.row + 4)
			|| (x[i].pos[0].col == Dim.col) || (x[i].pos[0].col == 1)))
			return true;
	}
	return false;
}
bool targetAchievedByAnySnake(snake *p,const int N, const int target)
{
	for (int i = 0; i < N; i++)
	{
		if (p[i].score == target)
			return true;
	}
	return false;
}
bool snakeAchieveTarget(snake p, const int target)
{
	return (p.score == target);
}
void showTime(clock_t &startingTime,int TIME[])
{
	TIME[3]= (clock() - startingTime) / 1000;
	if (TIME[3] > 9)
	{
		startingTime = clock();
		TIME[3] = (clock() - startingTime) / 1000;
		TIME[2]++;
	}
	if (TIME[2] > 5)
	{
		TIME[2] = TIME[2] % 6;
		TIME[1]++;
	}
	if (TIME[1] > 9)
	{
		TIME[1] = TIME[1] % 10;
		TIME[0]++;
	}
	
	gotoRowCol(1, 25);
	cout << TIME[0] << TIME[1] << ":" << TIME[2] << TIME[3];
	gotoRowCol(60, 0);
}
void speedControl(int t[])
{
	int s = 80;
	for (int i = 0; i < 5; i++)
	{
		if (t[1] == i)
		{
			Sleep(s - i * 12);
			break;
		}
		else if (t[1] > 4)
			Sleep(20);
	}
}

int main()
{
	displayStartingMenu();
	int numOfPlayers, target, TIME[4];
	getUserResponse(numOfPlayers);
	system("cls");
	pos Dim, *fpos;
	char fsym;
	Dim.row = 40;
	Dim.col = 60;
	snake *p=new snake[numOfPlayers];
	initp1(p, fsym, fpos, numOfPlayers,TIME,target);
	system("cls");
	PrintHBox(5, 1, Dim.row, Dim.col, -37);
	displaySnakeNScore(p, numOfPlayers);
	displayTarget(target);
	for (int i = 0; i < numOfPlayers; i++)
	{
			getFood(Dim, p, fsym, fpos,i, numOfPlayers);
	}
	char c = NULL;
	clock_t startingTime = clock();
	do
	{
		if (_kbhit())
		{
			changeDirection(p, c);
		}
		if (anyBoundaryTouch(p, Dim, numOfPlayers))
			break;
		eraseSnake(p,numOfPlayers);
		moveSnake(p, Dim,numOfPlayers);
		snakeToSnakeTouchPenalty(p, numOfPlayers);
		displaySnakeNScore(p, numOfPlayers);
		for (int i = 0; i < numOfPlayers; i++)
		{
			for (int j = 0; j < numOfPlayers; j++)
			{
				if (foodEaten(p[i], fpos[j]))
				{
					getFood(Dim, p, fsym, fpos,i, numOfPlayers);
					increaseSnakeSize(p[i]);
					p[i].score++;
					break;
				}
			}
		}
		showTime(startingTime, TIME);
		speedControl(TIME);
	} while (!anySnakeTouchingItself(p,numOfPlayers) && !targetAchievedByAnySnake(p,numOfPlayers,target));

	displaySnakeNScore(p, numOfPlayers);
	if (numOfPlayers == 1 && !snakeAchieveTarget(p[0],target))
	{
		if (snakeTouchingItself(p[0]) || boundaryTouch(p[0], Dim))
			showGameEndMsg1p();
	}
	else
	for (int i = 0; i < numOfPlayers; i++)
	{
		if (snakeTouchingItself(p[i]) || boundaryTouch(p[i], Dim))
			showGameEndMsg2p(p[(i + 1) % 2].name);
		else if (snakeAchieveTarget(p[i], target))
			showGameEndMsg2p(p[i].name);
	}
	return 0;
}