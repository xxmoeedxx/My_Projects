#include "HugeReal.h"
short HugeReal::operator[ ](int i) const
{
	if (this->size > i && i >= 0)
		return this->Ds[i];
	else return 0;
}
short& HugeReal::operator[ ](int i)
{
	return this->Ds[i];
}
HugeReal::HugeReal(long long s)
{
	this->size = s + 1;
	this->base = gBase;
	Ds = new short[s + 1]{};
	this->dpi = 0;
	Ds[dpi] = -2;
	this->isNeg = false;
}
HugeReal::HugeReal(istream& rdr)
{
	Load(rdr);
}
HugeReal::HugeReal(const HugeReal& a)
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
ostream& operator<<(ostream& c, const HugeReal& a)
{
	HugeReal zero;
	if (a.dpi == a.size - 1)
		c << "0";
	if (a.isNeg)
		c << "-";
	for (int i = a.size - 1; i >= 0; i--)
	{
		if (i == a.dpi)
		{
			if (i != 0)
				c << '.';
			continue;
		}
		if (a.base == 10)
			c << a[i];
		else
		{
			if (a[i] > 9)
			{
				c << char('A' - 10 + a[i]);
			}
			else c << a[i];
		}
	}
	return c;
}
istream& operator>>(istream& rdr, HugeReal& x)
{
	HugeReal temp(rdr);
	x.Deepcopy(temp);
	return rdr;
}
HugeReal HugeReal::AddQuantitywise(const HugeReal& a)const
{
	HugeReal R(max(this->size, a.size) + 2);
	R.dpi = max((*this).dpi, a.dpi);
	R.base = a.base;
	int  diff = abs((*this).dpi - a.dpi);
	int carry = 0;
	if ((*this).dpi > a.dpi)
	{
		for (int i = 0; i < R.dpi; i++)
		{
			int s = (*this)[i] + a[i - diff] + carry;
			R[i] = s % base;
			carry = s / base;
		}
		for (int i = R.dpi + 1; i < R.size; i++)
		{
			int s = (*this)[i] + a[i - diff] + carry;
			R[i] = s % base;
			carry = s / base;
		}
	}
	else
	{
		for (int i = 0; i < R.dpi; i++)
		{
			int s = (*this)[i - diff] + a[i] + carry;
			R[i] = s % base;
			carry = s / base;
		}
		for (int i = R.dpi + 1; i < R.size; i++)
		{
			int s = (*this)[i - diff] + a[i] + carry;
			R[i] = s % base;
			carry = s / base;
		}
	}
	R.shrink();
	return R;
}
HugeReal HugeReal::SubQuantitywise(const HugeReal& a)const
{
	HugeReal R(max(this->size-dpi,a.size-dpi)+max(dpi,a.dpi));
	R.base = a.base;
	R.dpi = max((*this).dpi, a.dpi);
	int carry = 0;
	int  diff = abs((*this).dpi - a.dpi);
	if ((*this).dpi > a.dpi)
	{
		for (int i = 0; i < R.dpi; i++)
		{
			int s = (*this)[i] - a[i - diff] + carry;
			carry = 0;
			if (s < 0)
			{
				s += base;
				carry = -1;
			}
			R[i] = s;
		}
		for (int i = R.dpi + 1; i < R.size; i++)
		{
			int s = (*this)[i] - a[i - diff] + carry;
			carry = 0;
			if (s < 0)
			{
				s += base;
				carry = -1;
			}
			R[i] = s;
		}
	}
	else
	{
		for (int i = 0; i < R.dpi; i++)
		{
			int s = (*this)[i - diff] - a[i] + carry;
			carry = 0;
			if (s < 0)
			{
				s += base;
				carry = -1;
			}
			R[i] = s;
		}
		for (int i = R.dpi + 1; i < R.size; i++)
		{
			int s = (*this)[i - diff] - a[i] + carry;
			carry = 0;
			if (s < 0)
			{
				s += base;
				carry = -1;
			}
			R[i] = s;
		}
	}
	R.shrink();
	return R;
}
bool HugeReal::LessQuantitywise(const HugeReal& a)const
{
	int  diff = abs((*this).dpi - a.dpi);
	if (this->size - (*this).dpi < a.size - a.dpi)
		return true;
	if (this->size - (*this).dpi > a.size - a.dpi)
		return false;

	if ((*this).dpi > a.dpi)
	{
		for (int i = max(this->size, a.size) - 1; i >= 0; i--)
		{
			if ((*this)[i] < a[i - diff])
				return true;
			if ((*this)[i] > a[i - diff])
				return false;
		}
	}
	else
	{
		for (int i = max(this->size, a.size) - 1; i >= 0; i--)
		{
			if ((*this)[i - diff] < a[i])
				return true;
			if ((*this)[i - diff] > a[i])
				return false;
		}
	}
	return false;
}
bool HugeReal::GreaterQuantitywise(const HugeReal& a)const
{
	return a.LessQuantitywise(*this);
}
bool HugeReal::EqualQuantitywise(const HugeReal& a)const
{
	return (!(*this).LessQuantitywise(a) && !(*this).GreaterQuantitywise(a));
}
