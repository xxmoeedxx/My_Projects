#pragma once
#include<fstream>
#include<iostream>
using namespace std;
class HugeReal
{
	int base;
	long long size;
	short* Ds;
	long long dpi;
	bool isNeg;
	void Load(istream& rdr)
	{
		string a;
		rdr >> a;
		if (isDecimal(a))
			this->size = a.size();
		else
			this->size = a.size() + 1;
		(*this).dpi = 0;
		if (a[0] == '+')
		{
			this->isNeg = false;
			this->size--;
		}
		else if (a[0] == '-')
		{
			this->isNeg = true;
			this->size--;
		}
		this->Ds = new short[this->size]{};
		if (a[0] == '-' || a[0] == '+')
			for (int i = this->size - 1; i + 1 >= 0; i--)
			{
				if (a[i + 1] == '.')
				{
					dpi = this->size - 1 - i;
				}
				if (a[i + 1] < 'A' || a[i + 1] > 'Z')
					this->Ds[this->size - 1 - i] = a[i + 1] - 48;
				else
					this->Ds[this->size - 1 - i] = a[i + 1] - 'A' + 10;
			}
		else
			for (int i = this->size - 1; i >= 0; i--)
			{
				if (a[i] == '.')
				{
					dpi = this->size - 1 - i;
				}
				if (a[i] < 'A' || a[i] > 'Z')
					this->Ds[this->size - 1 - i] = a[i] - 48;
				else
					this->Ds[this->size - 1 - i] = a[i] - 'A' + 10;
			}
		if (!isDecimal(a))
			this->Ds[0] = -2;
		(*this).shrink();
	}
	void Deepcopy(const HugeReal& a)
	{
		this->base = a.base;
		this->isNeg = a.isNeg;
		this->size = a.size;
		this->dpi = a.dpi;
		this->Ds = new short[a.size];
		for (int i = 0; i < size; i++)
		{
			this->Ds[i] = a.Ds[i];
		}
	}
	void shrink()
	{
		while ((*this)[size - 1] == 0 && this->size > dpi + 2)
		{
			short* R;
			R = new short[(this->size - 1)];
			for (int i = 0; i < this->size - 1; i++)
			{
				R[i] = (*this)[i];
			}
			delete[] this->Ds;
			this->Ds = R;
			this->size--;
		}
		while (dpi > 0 && (*this)[0] == 0)
		{
			short* R;
			(*this).dpi--;
			R = new short[(this->size - 1)];
			for (int i = this->size - 1; i > 0; i--)
			{
				R[i - 1] = (*this)[i];
			}
			delete[] this->Ds;
			this->Ds = R;
			this->size--;
		}
	}
	bool isDecimal(string a)
	{
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] == '.')
				return true;
		}
		return false;
	}
	HugeReal AddQuantitywise(const HugeReal& a)const;
	HugeReal SubQuantitywise(const HugeReal& a)const;
	bool LessQuantitywise(const HugeReal& a)const;
	bool GreaterQuantitywise(const HugeReal& a)const;
	bool EqualQuantitywise(const HugeReal& a)const;
	HugeReal getWholePart()const
	{
		HugeReal R((*this).size - (*this).dpi - 1);
		for (int i = 0; i < R.size; i++)
		{
			R[R.size - 1 - i] = (*this)[size - 1 - i];
		}
		return R;
	}
	HugeReal getDecPart()const
	{
		HugeReal R(dpi);
		for (int i = 0; i < R.size; i++)
		{
			R[R.size - 1 - i] = (*this)[dpi - 1 - i];
		}
		return R;
	}
	void MoveDecimalPlacesBehind(const int& places)
	{
		if (places > size - 1 - dpi)
		{
			int x = 0;
			short* temp;
			temp = new short[size + places]{};
			int i;
			for (i = 0; i < size - 1; i++)
			{
				if (i == dpi)
					x++;
				temp[i] = (*this)[i + x];
			}
			delete[] this->Ds;
			(*this).Ds = temp;
			(*this).size += places;
		}
		else
		{
			for (int i = 0; i < places; i++)
			{
				(*this)[i] = (*this)[i + 1];
			}
		}
		this->dpi += places;
		(*this)[dpi] = -2;
	}
	void MoveDecimalPlacesAhead(const int& places)
	{
		for (int i = 0; i < places; i++)
		{
			Ds[dpi - i] = Ds[dpi - i - 1];
		}
		dpi -= places;
		Ds[dpi] = -2;
	}
	HugeReal wholeNumMultiply(const HugeReal& x)
	{
		HugeReal a(x);
		a[0] = -2; HugeReal z(1);
		a.isNeg = false;
		HugeReal a4(1);
		a4[1] = 1;
		HugeReal a2;
		HugeReal r2(z);
		while (a - a2 != z)
		{
			HugeReal r(*this);
			r.isNeg = false;
			a2 = a4;
			while (a2 + a2 <= a)
			{
				r += r;
				a2 += a2;
			}
			r2 += r;
			if (a == a2)
				break;
			a -= a2;

		}
		r2.isNeg = !(((*this).isNeg && x.isNeg) || (!(*this).isNeg && !x.isNeg));
		return r2;
	}
	HugeReal wholeNumDivide(const HugeReal& x)
	{
		HugeReal quotient;
		HugeReal X(x);
		HugeReal T(*this);
		X.isNeg = false;
		T.isNeg = false;
		HugeReal r2;
		HugeReal one(1), r;
		one[1] = 1;
		for (HugeReal j = T; j >= X; j -= r)
		{
			r = X;
			HugeReal i;
			for (i = one; r + r < j; i += i)
			{
				r += r;
				if (r >= j)
					break;
			}
			r2 += i;
		}
		r2.isNeg = !(((*this).isNeg && x.isNeg) || (!(*this).isNeg && !x.isNeg));
		return r2;
	}
public:
	static int gBase;
	void getBase(const int &b)
	{
		base = b;
	}
	int printBase()
	{
		return base;
	}
	HugeReal(const HugeReal& a);
	HugeReal(istream& rdr);
	short operator[ ](int i) const;
	short& operator[ ](int i);
	HugeReal(long long s = 1);
	friend ostream& operator<<(ostream& c, const HugeReal& a);
	friend istream& operator>>(istream& rdr, HugeReal& x);
	HugeReal operator=(const HugeReal& a)
	{
		this->isNeg = a.isNeg;
		this->base = a.base;
		this->size = a.size;
		this->dpi = a.dpi;
		this->Ds = new short[a.size];
		for (int i = 0; i < size; i++)
		{
			this->Ds[i] = a.Ds[i];
		}
		return *this;
	}
	HugeReal operator+(const HugeReal& a)const
	{
		HugeReal r;
		if (((*this).isNeg && a.isNeg) || (!(*this).isNeg && !a.isNeg))
		{
			r = (*this).AddQuantitywise(a);
		}
		else if ((*this).GreaterQuantitywise(a))
		{
			r = (*this).SubQuantitywise(a);
			r.isNeg = (*this).isNeg;
		}
		else if ((*this).LessQuantitywise(a))
		{
			r = a.SubQuantitywise(*this);
			r.isNeg = a.isNeg;
		}
		return r;
	}
	HugeReal operator+=(const HugeReal& a)
	{
		*this = *this + a;
		return *this;
	}
	const HugeReal& operator++()
	{
		HugeReal R(1);
		R[1] = 1;
		*this = *this + R;
		return *this;
	}
	const HugeReal& operator++(int)
	{
		HugeReal R(1);
		R[1] = 1;
		*this = *this + R;
		return *this;
	}
	HugeReal operator-(const HugeReal& a)const
	{
		HugeReal r(a);
		r.isNeg = !r.isNeg;
		return *this + r;
	}
	HugeReal operator-=(const HugeReal& a)
	{
		*this = *this - a;
		return *this;
	}
	const HugeReal& operator--()
	{
		HugeReal R(1);
		R[1] = 1;
		*this = *this - R;
		return *this;
	}
	const HugeReal& operator--(int)
	{
		HugeReal R(1);
		R[1] = 1;
		*this = *this - R;
		return *this;
	}
	const HugeReal& operator-()
	{
		(*this).isNeg = !(*this).isNeg;
		return *this;
	}
	bool operator<(const HugeReal& a)const
	{
		if (this->isNeg == true && a.isNeg == false)
			return true;
		if (this->isNeg == false && a.isNeg == true)
			return false;
		if (!this->isNeg && !a.isNeg)
			return (*this).LessQuantitywise(a);
		else
			return a.LessQuantitywise(*this);
	}
	bool operator<=(const HugeReal& a)const
	{
		return !((*this) > a);
	}
	bool operator>=(const HugeReal& a)const
	{
		return !((*this) < a);
	}
	bool operator>(const HugeReal& a)const
	{
		return (a < *this);
	}
	bool operator==(const HugeReal& a)const
	{
		return (!(*this < a) && !(*this > a));
	}
	bool operator!=(const HugeReal& a)const
	{
		return !(*this == a);
	}
	HugeReal operator*(const HugeReal& x)const
	{
		HugeReal p;
		p.base = x.base;
		HugeReal t1(*this), t2(x);
		t1.MoveDecimalPlacesAhead(dpi);
		t2.MoveDecimalPlacesAhead(x.dpi);
		p = t1.wholeNumMultiply(t2);
		p.MoveDecimalPlacesBehind(dpi + x.dpi);
		return p;
	}
	HugeReal operator*=(const HugeReal& a)
	{
		*this = *this * a;
		return *this;
	}
	HugeReal operator/(const HugeReal& x)const
	{
		long long factor = (*this).dpi + 2 * (x.dpi + 1);
		HugeReal Dividend(*this), Divisor(x);
		HugeReal TempMultiplier(factor);
		TempMultiplier[factor] = 1;
		Dividend *= TempMultiplier;
		Divisor.MoveDecimalPlacesAhead(x.dpi);
		Divisor.shrink();
		HugeReal Quotient = Dividend.wholeNumDivide(Divisor);
		Quotient.MoveDecimalPlacesBehind(factor - 1 - x.dpi);
		Quotient.shrink();
		return Quotient;
	}
	HugeReal operator/=(const HugeReal& a)
	{
		*this = *this / a;
		return *this;
	}
	~HugeReal()
	{
		delete[] this->Ds;
	}
};

