#include<iostream>
#include"HugeReal.h"
using namespace std;
void Expand(HugeReal**& HI, int& noh, HugeReal x)
{
	HugeReal** temp;
	temp = new HugeReal * [noh + 1];
	for (int i = 0; i < noh; i++)
	{
		temp[i] = new HugeReal;
		*temp[i] = *HI[i];
	}
	temp[noh] = new HugeReal;
	*temp[noh] = x;
	noh++;
	delete[]HI;
	HI = temp;
	ofstream wtr("nums.txt");
	wtr << noh << endl;
	wtr << HI[0][0].gBase << endl;

	for (int i = 0; i < noh; i++)
	{
		wtr << *HI[i] << endl;
	}
	wtr.close();
}
int HugeReal::gBase = 10;
void Update(HugeReal** HI, const int& noh, ofstream& wtr)
{
	wtr << noh << endl;
	wtr << HI[0][0].gBase << endl;
	for (int i = 0; i < noh; i++)
	{
		wtr << *HI[i] << endl;
	}
}
void Load(ifstream& rdr, HugeReal**& HI, int& noh)
{
	rdr >> noh;
	int b;
	rdr >> b;
	rdr.ignore();
	HI = new HugeReal * [noh];
	for (int i = 0; i < noh; i++)
	{
		HI[i] = new HugeReal;
		rdr >> *HI[i];
		HI[i][0].getBase(b);
		HI[i][0].gBase = b;
	}
}
void Display(HugeReal** HI, const int& noh)
{
	for (int i = 0; i < noh; i++)
	{
		cout << i + 1 << ". " << *HI[i] << endl;
	}
}
int main()
{
	HugeReal temp;
	HugeReal** HI; char ans = 'y';
	int noh;
	do {
		ifstream rdr("nums.txt");
		Load(rdr, HI, noh);
		Display(HI, noh);
		int n1, n2, opt;
		HugeReal R;
		cout << "What operation to perform?\n";
		cout << "0. Enter new number\n1. +\t2. -\t3. *\t4. /\n5. +=\t6. -=\t7. *=\t8. /=\n9. >\t10. <\t11. >=\t12. <=\t13. ==\t14. !=\n";
		cin >> opt;
		if (opt == 0)
		{
			cout << "Enter the number\n";
			cin >> temp;
			Expand(HI, noh, temp);
			system("cls");
			continue;
		}
		cout << "Choose 1st num\n";
		cin >> n1;
		cout << "Choose 2nd num\n";
		cin >> n2;
		switch (opt)
		{
		case 1:
			R = *HI[n1 - 1] + *HI[n2 - 1];
			break;
		case 2:
			R = *HI[n1 - 1] - *HI[n2 - 1];
			break;
		case 3:
			R = *HI[n1 - 1] * *HI[n2 - 1];
			break;
		case 4:
			R = *HI[n1 - 1] / *HI[n2 - 1];
			break;
		case 5:
			*HI[n1 - 1] += *HI[n2 - 1];
			break;
		case 6:
			*HI[n1 - 1] -= *HI[n2 - 1];
			break;
		case 7:
			*HI[n1 - 1] *= *HI[n2 - 1];
			break;
		case 8:
			*HI[n1 - 1] /= *HI[n2 - 1];
			break;
		case 9:
			cout << ((*HI[n1 - 1] > *HI[n2 - 1]) ? "true" : "false");
			break;
		case 10:
			cout << ((*HI[n1 - 1] < *HI[n2 - 1]) ? "true" : "false");
			break;
		case 11:
			cout << ((*HI[n1 - 1] >= *HI[n2 - 1]) ? "true" : "false");
			break;
		case 12:
			cout << ((*HI[n1 - 1] <= *HI[n2 - 1]) ? "true" : "false");
			break;
		case 13:
			cout << ((*HI[n1 - 1] == *HI[n2 - 1]) ? "true" : "false");
			break;
		case 14:
			cout << ((*HI[n1 - 1] != *HI[n2 - 1]) ? "true" : "false");
			break;
		default: cout << "Wrong Option!Choose again\n";
			break;
		}
		if (opt < 5 && opt != 0)
			cout << endl << "R = " << R << endl;
		cout << "\nDo you want to continue?(y/n)\t";
		cin >> ans;
		ofstream wtr("nums.txt");
		Update(HI, noh, wtr);
		for (int i = 0; i < 130; i++)
			cout << "-";
		cout << endl;
	} while (ans == 'y' || ans == 'Y');
	return 0;
}
