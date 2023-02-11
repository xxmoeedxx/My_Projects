#include<conio.h>
#include<fstream>
#include<iostream>
#include<string.h>
#include<Windows.h>
using namespace std;
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
class ContinuousArray
{
	string* arr = new string[1];
	int count = 0, size = 1;
	void copy(string* arr1, string* arr2)
	{
		for (int i = 0; i < count; i++)
		{
			arr2[i] = arr1[i];
		}
	}
	void copy2(string*& arr1, const string* arr2, const int si, const int ei)
	{
		for (int i = si, j = 0; i <= ei; i++, j++)
		{
			arr1[j] = arr2[i];
		}
	}
	void MergeMagic(int a1startInd, int a1endInd, int a2startInd, int a2endInd)
	{
		string* a1 = new string[a1endInd - a1startInd + 1];
		string* a2 = new string[a2endInd - a2startInd + 1];
		copy2(a1, arr, a1startInd, a1endInd);
		copy2(a2, arr, a2startInd, a2endInd);
		int a1enti = 0, a2enti = 0;
		for (int i = a1startInd; i <= a2endInd; i++)
		{
			if (a2enti == a2endInd - a2startInd + 1 || a1enti != a1endInd - a1startInd + 1 && a1[a1enti] <= a2[a2enti])
			{
				if (arr[i] != a1[a1enti])
					arr[i] = a1[a1enti];
				a1enti++;
			}
			else
			{
				if (arr[i] != a2[a2enti])
					arr[i] = a2[a2enti];
				a2enti++;
			}
		}
	}
	void shiftL(int index)
	{
		for (int i = 0; index + i + 1 < count; i++)
		{
			arr[index + i] = arr[index + i + 1];
		}
	}
public:
	int returnSize()
	{
		return count;
	}
	void Enter(string x)
	{
		if (count >= size)
		{
			string* temp = new string[size * 2]{};
			copy(arr, temp);
			delete[]arr;
			arr = temp;
			size *= 2;
		}
		arr[count] = x;
		count++;
	}
	void printMsg(int index)
	{
		cout << "The Required No. is at index: " << index << endl;
	}
	ContinuousArray() {}
	void Print()
	{
		for (int i = 0; i < count; i++)
		{
			cout << i+1<<".\t" << arr[i] << '\n';
		}
		cout << endl;
	}
	void hiddenPrint()
	{
		for (int i = 0; i < count; i++)
		{
			cout << i + 1 << ".\t";
			for (int j = 0; j < arr[i].length(); j++)
				cout << '*';
			cout << '\n';
		}
		cout << endl;
	}
	void Print2(int i)
	{
		cout << arr[i];
	}
	int Search(string num)
	{
		int leftLim = 0;
		int  rightLim = count - 1;
		int midnum = -1;
		if (arr[leftLim] == num)
		{
			return leftLim;
		}
		else
			if (arr[rightLim] == num)
			{
				return rightLim;
			}
			else
				if (arr[leftLim]<num && arr[rightLim]>num)
				{
					while (midnum != 0)
					{
						midnum = (leftLim + rightLim) / 2;
						if (midnum == leftLim)
							return -99;
						if (arr[midnum] > num)
						{
							rightLim = midnum;
						}
						else
							if (arr[midnum] < num)
							{
								leftLim = midnum;
							}
							else
								if (arr[midnum] == num)
								{
									return (midnum);
								}
					}
				}
		return -99;
	}
	void Delete(int index)
	{
		if (index > count)
		{
			return;
		}
		shiftL(index);
		count--;
	}
	
	void MergeSort(int firstInd, int lastInd)
	{
		if (lastInd - firstInd <= 0)
			return;
		int midInd = (firstInd + lastInd) / 2;
		MergeSort(firstInd, midInd);
		MergeSort(midInd + 1, lastInd);
		MergeMagic(firstInd, midInd, midInd + 1, lastInd);
	}
	void show()
	{
		int opt = -999;
		while (opt != 6)
		{
			string x;int i = 0;
			string temp;
			system("cls");
			cout << "1. Enter a new number\n";
			cout << "2. Delete an existing number\n";
			cout << "3. Search an existing number\n";
			cout << "4. Print the Array\n";
			cout << "5. Sort the Array\n";
			cout << "6. Exit\n";
			cin >> opt;
			switch (opt)
			{
			case 1:
				cout << "Enter the number: \n";
				cin >> temp;
				Enter(temp);
				break;
			case 2:
				cout << "Enter index of the number: \n";
				cin >> x;
				if (i >= count)
				{
					cout << "Invalid Entry!\n";
					system("pause");
					break;
				}
				Delete(i);
				break;
			case 3:
				cout << "Enter the number: \n";
				cin >> x;
				i = Search(x);
				if (i != 99)
					printMsg(i);
				else cout << "Not Found!\n";
				system("pause");
				break;
			case 4:
				Print();
				system("pause");
				break;
			case 5:
				MergeSort(0, count - 1);
				break;
			case 6:
				break;
			default:
				cout << "Invalid Entry!\n";
				break;
			}
		}
	}
	string* return_uniqueStrings(int& usize)
	{
		int idSt = 0, Uind = 0; bool isUnq;
		for (int i = 0; i + 1 < count; i++)
			if (!strcmp(arr[i].c_str(), arr[i + 1].c_str()))
				idSt++;
		string* Unique = new string[count - idSt];
		for (int i = 0; Uind < count - idSt && i < count; i++)
		{
			isUnq = true;
			for (int j = i + 1; j < count; j++)
			{
				if (!strcmp(arr[i].c_str(), arr[j].c_str()))
				{
					isUnq = false;
					break;
				}
			}
			if (isUnq)
			{
				Unique[Uind] = arr[i];
				Uind++;
			}
		}
		usize = Uind;
		return Unique;
	}
	void  allPossibleStrings(string str, string res) {


		this->Enter(res);
		//the base case will be when the string will consist of only one character
		//so the loop will run only once
		for (int i = 0; i < str.length(); i++)
			allPossibleStrings(string(str).erase(i, 1), res + str[i]);
	}
	ContinuousArray returnIntersection(string* a, int size)
	{
		ContinuousArray R;
		for (int i = 0; i < size; i++)
		{
			int j=Search(a[i]);
			if (j != -99)
				R.Enter(a[i]);
		}
		return R;
	}
	void LoadFile(ifstream& rdr)
	{
		string a;
		while (!rdr.eof())
		{
			rdr >> a;
			Enter(a);
		}
	}
	bool tallyAnswer(string ans)
	{
		for (int i = 0; i < count; i++)
		{
			if (arr[i] == ans)
			{
				gotoRowCol(3 + i, 8);
				cout << ans;
				return true;
			}
		}
		return false;
	}
};

void print(string* all, const int size)
{
	for (int i = 0; i < size; i++)
		cout <<i+1<<".\t"<< all[i] << endl;
}

int main() {
	string str;
	char g = 'y';
	int score = 0;
	do {
		system("cls");
		gotoRowCol(3, 37);
		cout << "Score: " << score;
		gotoRowCol(0, 0);
		cout << "Enter a string:\t";
		cin >> str;
		ContinuousArray all;
		string* unique = nullptr; int usize = 0;
		all.allPossibleStrings(str, "");
		all.MergeSort(0, all.returnSize() - 1);
		unique = all.return_uniqueStrings(usize);
		ContinuousArray dictionary;
		ifstream rdr("dictionary.txt");
		dictionary.LoadFile(rdr);
		cout << "\nPossible meaningful words:\n";
		ContinuousArray result = (dictionary.returnIntersection(unique, usize));
		result.hiddenPrint();
		cout << "\tQuit (Get cursor here and press Enter)";
		string guess;
		gotoRowCol(2, 75);
		cout << "Enter Guess:";
		gotoRowCol(2, 30);
		cout << "(Press Esc to advance to next round)";
		gotoRowCol(3, 75);
		int cr = 3, cc = 75;
		char nextRound=' ';
		while (1) {
			char c;
			if (_kbhit())
			{
				c = _getch();
				if (c == 27) //Esc key
				{
					nextRound = c;
					break;
				}
				if (c == 13) //Enter Key
				{
					if (cr == result.returnSize() + 4)
						break;
					else
					{
						gotoRowCol(cr, cc);
						result.Print2(cr - 3);
						continue;
					}

				}
				if (c == -32)
					c = _getch();
				if (c == 72)//up arrow
				{
					if (cr - 1 >= 3)
						gotoRowCol(--cr, cc);
					else 
					{
						cr = result.returnSize() + 3;
						gotoRowCol(--cr, cc);
					}
					continue;
				}
				else if (c == 80)//down arrow
				{
					cc = 8;
					if (cr  > 3 + result.returnSize())
						cr = 2;
					gotoRowCol(++cr, cc);
					continue;
				}
				else if (c == 77)//right arrow
				{
					if (cc != 75)
					{
						cc = 75;
						cr = 3;
						gotoRowCol(cr, cc);
					}
					else
					{
						cc = 8;
						gotoRowCol(cr, cc);
					}
					continue;
				}
				else if (c == 75)//left arrow
				{
					if (cc == 75)
					{
						cc = 8;
						gotoRowCol(cr, cc);
					}
					continue;
				}
				if (((cr == 3) && (cc = 75)) || (c != 75 && c != 80 && c != 72 && c != 77))
				{
					gotoRowCol(3, 75);
					if ((c != 75 && c != 80 && c != 72 && c != 77))
						cout << c;
					cin >> guess;
					guess.insert(guess.begin(), c);
					gotoRowCol(3, 75);
					cout << "                      ";
					if (result.tallyAnswer(guess))
					{
						score++;
						gotoRowCol(3, 44);
						cout  << score;
					}
					
					else
					{
					 gotoRowCol(5, 75);
					 cout << "Wrong guess!";
					 gotoRowCol(7, 75);
					 system("pause");
					 gotoRowCol(5, 75);
					 cout << "             ";
					 gotoRowCol(7, 75);
					 cout << "                              ";
					}
					if (score == result.returnSize())
						break;
					gotoRowCol(3, 75);
				}

			}
		}
		if(nextRound!=27)
		{
			gotoRowCol(3, 0);
			result.Print();
			cout << "Do you want to play next round?(y/n):          \t";
			cin >> g;
		}
	} while (g=='y');
	return 0;
}
