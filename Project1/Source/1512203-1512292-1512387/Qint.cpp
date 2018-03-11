#include "Qint.hpp"
#include "StringNumber.hpp"
#include <algorithm>

int size = 8 * sizeof(long long);

void Qint::setBit(long long bit, int i){
	long long k = 1;
	if (bit == 1)
		arrayBits[i / 64] = arrayBits[i / 64] | (k << (63 - i % 64));
	else
		arrayBits[i / 64] = arrayBits[i / 64] & ~(k << (63 - i % 64));
}

Qint Qint::left()const
{
	Qint result = (*this);
	long long x = 1;
	result.arrayBits[0] <<= 1;
	if (arrayBits[1] < 0)
		result.arrayBits[0] |= 1;
	result.arrayBits[1] <<= 1;
	return result;
}

Qint Qint::right()const
{
	Qint result = (*this);
	long long x = 1;
	result.arrayBits[1] >>= 1;
	if (arrayBits[0] & 1 != 0)
		result.arrayBits[1] |= (x << 63);
	else result.arrayBits[1] &= ~(x << 63);
	result.arrayBits[0] >>= 1;
	return result;
}


Qint::Qint(long long x, long long y)
{
	arrayBits[0] = x;
	arrayBits[1] = y;
}

Qint::Qint()
{
	arrayBits[0] = arrayBits[1] = 0;
}

Qint::Qint(const string&t)
{
	string s = mem_dec_to_bin_int(t);
	arrayBits[0] = arrayBits[1] = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '1')
			setBit(1, i);
		else setBit(0, i);
	}
}

Qint::Qint(const string&s, const string&type)
{
	if (type == "10")
	{
		(*this) = Qint(s);
	}
	if (type == "2")
	{
		string s1 = s;
		while (s1.size() != 128)
		{
			s1 = "0" + s1;
		}
		arrayBits[0] = arrayBits[1] = 0;
		for (int i = 0; i < s1.size(); i++)
		{
			if (s1[i] == '1')
				setBit(1, i);
			else setBit(0, i);
		}
	}
	if (type == "16")
	{
		string s1 = hex_to_bin_int(s);
		(*this) = Qint(s1, "2");
	}
}

Qint::Qint(const Qint&a)
{
	arrayBits[0] = a.arrayBits[0];
	arrayBits[1] = a.arrayBits[1];
}

Qint::Qint(const vector<bool>&v)
{
	arrayBits[0] = arrayBits[1] = 0;
	string s = "";
	for (int i = 0; i < v.size(); i++)
	if (v[i]) s += "1";
	else s += "0";
	(*this) = Qint(s, "2");
}

Qint::~Qint()
{

}

Qint& Qint::operator = (const Qint&a)
{
	arrayBits[0] = a.arrayBits[0];
	arrayBits[1] = a.arrayBits[1];
	return(*this);
}

string Qint::decToBin() const
{
	string s = "";
	for (int i = 63; i >= 0; i--)
	if ((arrayBits[0] >> i) & 1)
		s += "1";
	else s += "0";
	for (int i = 63; i >= 0; i--)
	if ((arrayBits[1] >> i) & 1)
		s += "1";
	else s += "0";
	return s;
}

vector<bool> Qint::DecToBin() const
{
	string temp = decToBin();
	vector<bool> res;
	for (auto i : temp) res.push_back(i - '0');
	return res;
}

string Qint::write(const string&type) const
{
	string s = decToBin();
	if (type == "10")
	{
		return mem_bin_to_dec_int(s);
	}
	while (s[0] == '0')
	{
		s.erase(s.begin());
	}
	if (type == "2")
	{
		return s;
	}
	if (type == "16")
	{
		while (s.size() % 4)
			s.insert(s.begin(), '0');
		return bin_to_hex_int(s);
	}
	return "";
}

Qint Qint::operator << (unsigned int t)const
{
	Qint result = (*this);
	for (int i = 0; i < t; i++)
		result = result.left();
	return result;
}

Qint Qint::operator >> (unsigned int t)const
{
	Qint result = (*this);
	for (int i = 0; i < t; i++)
		result = result.right();
	return result;
}

Qint Qint::operator & (const Qint&a) const
{
	Qint result(arrayBits[0] & a.arrayBits[0], arrayBits[1] & a.arrayBits[1]);
	return result;
}

Qint Qint::operator | (const Qint&a) const
{
	Qint result(arrayBits[0] | a.arrayBits[0], arrayBits[1] | a.arrayBits[1]);
	return result;
}

Qint Qint::operator ^ (const Qint&a) const
{
	Qint result(arrayBits[0] ^ a.arrayBits[0], arrayBits[1] ^ a.arrayBits[1]);
	return result;
}

Qint operator ~ (const Qint&t)
{
	Qint result(~t.arrayBits[0], ~t.arrayBits[1]);
	return result;
}

Qint operator - (const Qint&t)
{
	Qint one(0, 1);
	return ~t + one;
}

Qint Qint::operator + (const Qint&a) const
{
	Qint res;
	long long rem = 0;
	res.arrayBits[1] = arrayBits[1] + a.arrayBits[1];
	if (arrayBits[1] < 0 && a.arrayBits[1] < 0)
	rem = 1;
	if (arrayBits[1] < 0 && a.arrayBits[1] >= 0 && res.arrayBits[1] >= 0)
	rem = 1;
	if (a.arrayBits[1] < 0 && arrayBits[1] >= 0 && res.arrayBits[1] >= 0)
	rem = 1;
	res.arrayBits[0] = arrayBits[0] + a.arrayBits[0];
	res.arrayBits[0] += rem;
	return res;
}

Qint Qint::operator - (const Qint&a) const
{
	return (*this) + (-a);
}

Qint Qint::operator * (const Qint&a) const
{
	Qint A;
	Qint Q = *this;
	long long q = 0;
	long long p = 1;
	p <<= 63;
	for (int i = 0; i < 2 * size; i++)
	{
	if ((Q.arrayBits[1] & 1) != q)
	{
	if (q == 1)
	A = A + a;
	else A = A - a;
	}
	q = Q.arrayBits[1] & 1;
	long long x = A.arrayBits[1] & 1;
	Q = Q.right();
	A = A.right();
	if (x == 0)
	Q.arrayBits[0] &= ~p;
	else Q.arrayBits[0] |= p;
	}
	return Q;
}

Qint Qint::nhan(const Qint&a) const
{
	Qint A;
	Qint Q = *this;
	long long q = 0;
	long long p = 1;
	p <<= 63;
	for (int i = 0; i < 2 * size; i++)
	{
		if ((Q.arrayBits[1] & 1) != q)
		{
			if (q == 1)
				A = A + a;
			else A = A - a;
		}
		q = Q.arrayBits[1] & 1;
		long long x = A.arrayBits[1] & 1;
		Q = Q.right();
		A = A.right();
		if (x == 0)
			Q.arrayBits[0] &= ~p;
		else Q.arrayBits[0] |= p;
	}
	return A;
}

Qint Qint::operator / (const Qint&M) const
{
	Qint A(0, 0);
	Qint temp;
	Qint Q = (*this);
	if (arrayBits[0] == 0 && arrayBits[1] == 0) return A;
	if (arrayBits[0] < 0 && M.arrayBits[0] < 0) return (-(*this) / (-M));
	if (M.arrayBits[0] < 0 && arrayBits[0] >= 0) return -((*this) / (-M));
	if (arrayBits[0] < 0 && M.arrayBits[0] >= 0) return -(-(*this) / M);
	for (int i = 0; i < 2 * size; i++)
	{
		A = A.left();
		if (Q.arrayBits[0] < 0)
			A.arrayBits[1] |= 1;
		Q = Q.left();
		temp = A - M;
		if (temp.arrayBits[0] >= 0)
		{
			A = temp;
			Q.arrayBits[1] |= 1;
		}
	}
	return Q;
}

Qint Qint::operator % (const Qint&M) const
{
	Qint A(0, 0);
	Qint temp;
	Qint Q = (*this);
	if (arrayBits[0] == 0 && arrayBits[1] == 0) return A;
	if (arrayBits[0] < 0 && M.arrayBits[0] < 0) return -(-(*this) % (-M));
	if (M.arrayBits[0] < 0 && arrayBits[0] >= 0) return ((*this) % (-M));
	if (arrayBits[0] < 0 && M.arrayBits[0] >= 0) return -(-(*this) % M);
	for (int i = 0; i < 2 * size; i++)
	{
		A = A.left();
		if (Q.arrayBits[0] < 0)
			A.arrayBits[1] |= 1;
		Q = Q.left();
		temp = A - M;
		if (temp.arrayBits[0] >= 0)
		{
			A = temp;
			Q.arrayBits[1] |= 1;
		}
	}
	return A;
}

Qint Qint::ror(unsigned int n) const
{
	long long t = 1;
	t <<= 63;
	Qint res = (*this);
	for (int i = 0; i < n % 128; i++)
	{
		if (res.arrayBits[0] < 0 && res.arrayBits[1] % 2 == 0)
		{
			res = res >> 1;
			res.arrayBits[0] &= ~t;
		}
		else
		if (res.arrayBits[0] >= 0 && res.arrayBits[1] % 2 != 0)
		{
			res = res >> 1;
			res.arrayBits[0] |= t;
		}
		else res = res >> 1;
	}
	return res;
}

Qint Qint::rol(unsigned int n) const
{
	return this->ror(128 - n % 128);
}