#include "Qfloat.hpp"
#include "Qint.hpp"
#include "StringNumber.hpp"
#include <cmath>
#include <stdlib.h>
#include <cstring>
#include <algorithm>

const int maxExpVal = (1 << 14) - 1;
const int minExpVal = - (1 << 14) + 2;
const int speExpVal = - (1 << 14) + 1;

Qfloat::Qfloat()
{
    arrayBits[0] = arrayBits[1] = 0;
}

Qfloat::Qfloat(const vector<bool>& p)
{
    arrayBits[0] = arrayBits[1] = 0;
    for (int i = 0; i < p.size(); ++i)
    {
        arrayBits[i / 64] <<= 1;
		arrayBits[i / 64] += (int)(p[i]);
    }
}

Qfloat::Qfloat(const string& p)
{
    arrayBits[0] = arrayBits[1] = 0;
    string bits = mem_dec_to_bin_float(p);
    for (int i = 0; i < bits.length(); ++i)
    {
        arrayBits[i / 64] <<= 1;
		arrayBits[i / 64] += (int)(bits[i] - '0');
    }
}

Qfloat::Qfloat(const Qfloat& p)
{
    arrayBits[0] = p.arrayBits[0];
    arrayBits[1] = p.arrayBits[1];
}

Qfloat::Qfloat(string str1, string str2)
{
	if (str2 == "10")
		*this = Qfloat(str1);
	if (str2 == "2")
	{
		vector<bool> bits;
		for (auto i : str1)
			bits.push_back(i - '0');
		*this = Qfloat(bits);
	}
}

Qfloat::~Qfloat()
{
    
}

Qfloat& Qfloat::operator = (const Qfloat& p)
{
    if (this != &p)
    {
        arrayBits[0] = p.arrayBits[0];
        arrayBits[1] = p.arrayBits[1];
    }
    return *this;
}

ostream& operator << (ostream& os, const Qfloat& p)
{
    return os << mem_bin_to_dec_float(p.getBitsString(0, 127));
}

istream& operator >> (istream& is, Qfloat& p)
{
	string str;
	getline(cin, str);
    string bits = mem_dec_to_bin_float(str);
    for (int i = 0; i < bits.length(); ++i)
    {
        p.arrayBits[i / 64] <<= 1;
        p.arrayBits[i / 64] += (bits[i] - '0') ? 1 : 0;
    }
    return is;
}

bool Qfloat::is_Zero() const
{
    for (int i = 0; i <= 1; ++i)
    {
        for (int j = 0; j <= 63; ++j)
        {
            if ((arrayBits[i] >> j) & 1)
                return false;
        }
    }
    return true;
}

bool Qfloat::is_Zero(const vector<bool>& a) const
{
    for (auto i : a)
        if (i)
            return false;
    return true;
}

int Qfloat::compare(vector<bool> a, vector<bool> b) const
{
    while (a.size() < b.size())
        a.insert(a.begin(), 0);
    while (b.size() < a.size())
        b.insert(b.begin(), 0);
    for (int i = 0;  i < a.size(); ++i)
    {
        if ((int)a[i] > (int)b[i])
            return 1;
        else if ((int)b[i] > (int)a[i])
            return -1;
    }
    return 0;
}

vector<bool> Qfloat::getBits(int start, int end) const
{
    vector<bool> res;
    for (int i = start; i <= end; ++i)
        res.push_back((arrayBits[i / 64] >> (64 - i % 64 - 1)) & 1);
    return res;
}

string Qfloat::getBitsString(int start, int end) const
{
    string res;
    for (int i = start; i <= end; ++i)
        res.push_back(((arrayBits[i / 64] >> (64 - i % 64 - 1)) & 1) + '0');
    return res;
}

vector<bool> Qfloat::shiftRight(vector<bool> a) const
{
    for (int i = a.size() - 1; i > 0; --i)
        a[i] = a[i - 1];
    a[0] = 0;
    return a;
}

vector<bool> Qfloat::shiftLeft(vector<bool> a) const
{
    int n = a.size();
    for (int i = 0; i < n - 1; ++i)
        a[i] = a[i + 1];
    a[n - 1] = 0;
    return a;
}

int Qfloat::getValue(vector<bool> a) const
{
    int exp = a.size() - 1;
    int res = 0;
    int temp = 1;
    for (int i = 0; i <= exp; ++i)
    {
        res += temp * a[exp - i];
        temp *= 2;
    }
    return res;
}

vector<bool> Qfloat::convertToTwoComplement(vector<bool> a) const
{
    int temp = 1;
    bool value = 0;
    vector<bool> res;
    for (int i = 0; i < a.size(); ++i)
        a[i] = !a[i];
    for (int i = a.size() - 1; i >= 0; --i)
    {
        value = (a[i] + temp) % 2;
        temp = (a[i] + temp) / 2;
        res.insert(res.begin(), value);
    }
    return res;
}

vector<bool> Qfloat::addBinNumber(vector<bool> a, vector<bool> b) const
{
    vector<bool> res;
    bool temp = 0;
    bool value = 0;    for (int i = a.size() - 1; i >= 0; --i)
    {
        value = ((int)a[i] + (int)b[i] + temp) % 2;
        temp = ((int)a[i] + (int)b[i]  + temp) / 2;
        res.insert(res.begin(), value);
    }
    return res;
}

vector<bool> Qfloat::normalize_TwoComplement(vector<bool> a) const
{
    bool temp = 1;
    bool value = 0;
    vector<bool> res;
    for (int i = a.size() - 1; i >= 0; --i)
    {
        value = ((a[i] - temp) == 0) ? 0 : 1;
        temp = (a[i] - temp == -1) ? 1 : 0;
        res.insert(res.begin(), value);
    }
    for (int i = res.size() - 1; i >= 0; --i)
        res[i] = !res[i];
    return res;
}

vector<bool> Qfloat::fillBits(vector<bool> a, int max) const
{
    while (a.size() < max)
        a.insert(a.begin(), 0);
    return a;
}

vector<bool> Qfloat::addSignificand(vector<bool> a, bool sign1, vector<bool> b, bool sign2, bool &sign) const
{    sign = 0;
    a = fillBits(a, 128);
    b = fillBits(b, 128);
    a = (sign1) ? convertToTwoComplement(a) : a;
    b = (sign2) ? convertToTwoComplement(b) : b;
    vector<bool> res = addBinNumber(a, b);
    if (res[0])
    {
        sign = 1;
        res = normalize_TwoComplement(res);
    }
    return res;
}

int Qfloat::normalizeSignificand_Add(vector<bool> &a) const
{    while (a.size() > 114)
        a.erase(a.begin());
    int res = 0;
    if (a[0])
    {
        a = shiftRight(a);
        res++;
        a.erase(a.begin());
    }
    else
    {
        a.erase(a.begin());
        while (!a[0])
        {
            a = shiftLeft(a);
            res--;
        }
    }
    a.erase(a.begin());
    return res;
}

Qfloat Qfloat::getINFfloat(bool sign) const
{
    vector<bool> temp(128, 1);
    temp[0] = sign;
    return Qfloat(temp);
}

Qfloat Qfloat::getNaNFloat() const
{
    vector<bool> e(15, 1);
    vector<bool> significand(112, 0);
    vector<bool> temp(1, 0);
    temp.insert(temp.end(), e.begin(), e.end());
    temp.insert(temp.end(), significand.begin(), significand.end());
    return Qfloat(temp);
}

vector<bool> Qfloat::bin_To_Bias(int value) const
{
    string temp = mem_dec_to_bin_int(std::to_string(value + maxExpVal));
    vector<bool> res;
    for (auto i : temp)
    {
        res.push_back(i - '0');
    }
    while (res.size() > 15)
        res.erase(res.begin());
    return res;
}

Qfloat Qfloat::operator + (const Qfloat& p) const
{
    if (this->is_Zero())
        return p;
    if (p.is_Zero())
        return *this;
    vector<bool> e1 = getBits(1, 15);
    vector<bool> e2 = p.getBits(1, 15);
    int deltaE = getValue(e1) - getValue(e2);
    vector<bool> e = (deltaE >= 0) ? e1 : e2;
    vector<bool> significand1 = getBits(16, 127);
    vector<bool> significand2 = p.getBits(16, 127);
    significand1.insert(significand1.begin(), 1);
    significand2.insert(significand2.begin(), 1);
    if (deltaE > 0)
    {
        for (int i = 1; i <= deltaE; ++i)
            significand2 = shiftRight(significand2);
    }
    else if (deltaE < 0)
    {
        int temp = - deltaE;
        for (int i = 1; i <= temp; ++i)
            significand1 = shiftRight(significand1);
    }
    bool sign1 = (arrayBits[0] >> 63) & 1;
    bool sign2 = (p.arrayBits[0] >> 63) & 1;
    bool sign = 0;
    deltaE = 0;
    vector<bool> significand = addSignificand(significand1, sign1, significand2, sign2, sign);
    if (is_Zero(significand))
        return Qfloat("0");
    deltaE = normalizeSignificand_Add(significand);
    int exp = getValue(e) + deltaE - maxExpVal;
    if (exp < minExpVal)
        return Qfloat("0");
    if (exp > maxExpVal)
        return getINFfloat(sign);
    e = bin_To_Bias(exp);
    vector<bool> temp(significand);
    temp.insert(temp.begin(), e.begin(), e.end());
    temp.insert(temp.begin(), sign);
    return Qfloat(temp);
}

Qfloat Qfloat::operator - (const Qfloat& p) const
{
    vector<bool> bits = p.getBits(0, 127);
    bits[0] = !bits[0];
    return Qfloat(bits) + *this;
}

vector<bool> Qfloat::multiplySignificand(vector<bool> a, vector<bool> b) const
{
    a.insert(a.begin(), 1);
    b.insert(b.begin(), 1);
    a = fillBits(a, 128);
    b = fillBits(b, 128);
    Qint Q(a), M(b);
    Qint A = Q.nhan(M);
    Qint QQ = Q*M;
	string V1 = A.decToBin();
	string V2 = QQ.decToBin();
    for (int i = 0; i < V2.size(); i++)
        V1.push_back(V2[i]);
	vector<bool> res;
	for (auto i : V1)
		res.push_back(i - '0');
	return res;
}

int Qfloat::normalizeSignificand_Multiply(vector<bool> &a) const
{
    while (a.size() > 227)
        a.erase(a.begin());
    int res = 0;
    if (a[0])
    {
        a = shiftRight(a);
        res++;
    }
    a.erase(a.begin());
    while (!a[0])
    {
        a = shiftLeft(a);
        res--;
    }    a.erase(a.begin());
	while (a.size() > 112)
		a.erase(a.end() - 1);
    return res + 1;
}

Qfloat Qfloat::operator * (const Qfloat& p) const
{
    if (this->is_Zero() || p.is_Zero())
        return Qfloat("0");
    bool sign = ((arrayBits[0] >> 63) & 1) ^ ((p.arrayBits[0] >> 63) & 1);
    vector<bool> e1 = getBits(1, 15);
    vector<bool> e2 = p.getBits(1, 15);
    long long deltaE = getValue(e1) + getValue(e2) - 2 * maxExpVal;
    if (deltaE < minExpVal)
        return Qfloat("0");
    if (deltaE > maxExpVal)
        return getINFfloat(sign);
    vector<bool> significand1 = getBits(16, 127);
    vector<bool> significand2 = p.getBits(16, 127);
    vector<bool> significand = multiplySignificand(significand1, significand2);
    deltaE += normalizeSignificand_Multiply(significand);
    if (deltaE < minExpVal)
        return Qfloat("0");
    if (deltaE > maxExpVal)
        return getINFfloat(sign);
    vector<bool> e = bin_To_Bias(deltaE);
    vector<bool> temp(significand);
    temp.insert(temp.begin(), e.begin(), e.end());
    temp.insert(temp.begin(), sign);
    return Qfloat(temp);
}

vector<bool> Qfloat::divideSignificand(vector<bool> a, vector<bool> b) const
{
    a.insert(a.begin(), 1);
    b.insert(b.begin(), 1);
    a = fillBits(a, 128);
    b = fillBits(b, 128);
    vector<bool> res;
    int check = 0;
    if (compare(a, b) >= 0)
    {
        res.push_back(1);
        a = (Qint(a) - Qint(b)).DecToBin();
    }
    else{
        res.push_back(0);
    }
    while (res.size() < 128) res.insert(res.begin(), 0);
    for (int i = 0; i < 128; ++i)
    {
        a = shiftLeft(a);
        check = compare(a, b);
        if (check >= 0)
        {
            res.push_back(1);
            a = (Qint(a) - Qint(b)).DecToBin();
        }
        else
        {
            res.push_back(0);
        }
    }
    return res;
}

int Qfloat::normalizeSignificand_Divide(vector<bool>& a) const
{
    int res = 0;
    while (a.size() > 129)
    {
        if (a[0])
        {
            a = shiftRight(a);
            res++;
        }
        a.erase(a.begin());
    }
    while (!a[0])
    {
        a = shiftLeft(a);
        res--;
    }
    a.erase(a.begin());
    while (a.size() > 112)
        a.erase(a.end() - 1);
    return res;
}

Qfloat Qfloat::operator / (const Qfloat& p) const
{
    if (this->is_Zero())
    {
        if (!p.is_Zero())
        {
            return Qfloat("0");
        }
        else
            return getNaNFloat();
    }
    bool sign = ((arrayBits[0] >> 63) & 1) ^ ((p.arrayBits[0] >> 63) & 1);
    if (p.is_Zero())
        return getINFfloat(sign);
    vector<bool> e1 = getBits(1, 15);
    vector<bool> e2 = p.getBits(1, 15);
    long long deltaE = getValue(e1) - getValue(e2);
    if (deltaE < minExpVal)
        return Qfloat("0");
    if (deltaE > maxExpVal)
        return getINFfloat(sign);
    vector<bool> significand1 = getBits(16, 127);
    vector<bool> significand2 = p.getBits(16, 127);
    vector<bool> significand = divideSignificand(significand1, significand2);
    deltaE += normalizeSignificand_Divide(significand);
    if (deltaE < minExpVal)
        return Qfloat("0");
    if (deltaE > maxExpVal)
        return getINFfloat(sign);
    vector<bool> e = bin_To_Bias(deltaE);
    vector<bool> temp(significand);
    temp.insert(temp.begin(), e.begin(), e.end());
    temp.insert(temp.begin(), sign);
    return Qfloat(temp);
}

vector<bool> Qfloat::decToBin() const
{
	return getBits(0, 127);
}

Qfloat Qfloat::binToDec(const vector<bool>& p)
{
	return Qfloat(p);
}

string Qfloat::write(string p) const
{
	if (p == "2")
		return getBitsString(0, 127);
	if (p == "10")
		return mem_bin_to_dec_float(getBitsString(0, 127));
	return "";
}