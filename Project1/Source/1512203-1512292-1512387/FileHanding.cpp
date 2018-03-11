#include "FileHanding.hpp"
#include "Qfloat.hpp"
#include "Qint.hpp"
#include <algorithm>
#include <cstring>
#include <stdlib.h>

vector<string> splitString(string str)
{
	char *s = strdup(str.c_str());
	char *temp = NULL;
	vector<string> res;
	temp = strtok(s, " ");
	if (temp) res.push_back((string)temp);
	while (temp = strtok(NULL, " ")) res.push_back((string)temp);
	delete[] s;
	return res;
}
vector<string> readFile(fstream& f)
{
	vector<string> res;
	string tmp;
	while (!f.eof())
	{
		getline(f, tmp);
		res.push_back(tmp);
	}
	return res;
}
void writeFile(fstream& f, const vector<string>& str)
{
	for (auto i : str) f << i << endl;
}
string handing_int(vector<string> p)
{
	if (p.size() == 4)
	{
		if (p[2] != ">>" || p[2] != "<<")
		{
			Qint int1(p[1], p[0]);
			Qint int2(p[3], p[0]);
			if (p[2] == "+")
			{
				return (int1 + int2).write(p[0]);
			}
			if (p[2] == "-")
			{
				return (int1 - int2).write(p[0]);
			}
			if (p[2] == "*")
			{
				return (int1 * int2).write(p[0]);
			}
			if (p[2] == "/")
			{
				return (int1 / int2).write(p[0]);
			}
		}
		Qint int1(p[1], p[0]);
		int tmp = atoi(p[3].c_str());
		if (p[2] == ">>")
			return (int1 >> tmp).write(p[0]);
		if (p[2] == "<<")
			return (int1 << tmp).write(p[0]);
	}
	if (p.size() == 3)
	{
		Qint int1(p[2], p[0]);
		if (p[1] == "2")
			return int1.write("2");
		if (p[1] == "10")
			return int1.write("10");
		if (p[1] == "16")
			return int1.write("16");
		if (p[1] == "ror")
			return (int1.ror(1)).write(p[0]);
		if (p[1] == "rol")
			return (int1.rol(1)).write(p[0]);
		if (p[1] == "~")
			return (~int1).write(p[0]);
	}
	return "";
}
string handing_float(vector<string> p)
{
	if (p.size() == 4)
	{
		Qfloat float1(p[1], p[0]);
		Qfloat float2(p[3], p[0]);
		if (p[2] == "+")
		{
			return (float1 + float2).write(p[0]);
		}
		if (p[2] == "-")
		{
			return (float1 - float2).write(p[0]);
		}
		if (p[2] == "*")
		{
			return (float1 * float2).write(p[0]);
		}
		if (p[2] == "/")
		{
			return (float1 / float2).write(p[0]);
		}
	}
	if (p.size() == 3)
	{
		Qfloat float1(p[2], p[0]);
		return float1.write(p[1]);
	}
	return "";
}
void handingFile(string(*p)(vector<string>))
{
	fstream fin;
	fstream fout;
	string fileIn;
	string fileOut;
	cout << "Nhap ten file input:" << endl;
	getline(cin, fileIn);
	fin.open(fileIn, ios_base::in);
	if (!fin.is_open())
	{
		cout << "Khong tim thay file!" << endl;
		exit(0);
	}
	vector<string> tmp = readFile(fin);
	fin.close();
	vector<string> res;
	for (auto i : tmp)
	{
		res.push_back(p(splitString(i)));
	}
	cout << "Nhap ten file output:" << endl;
	getline(cin, fileOut);
	fout.open(fileOut, ios_base::out);
	writeFile(fout, res);
	fout.close();
	cout << "Xu ly thanh cong!" << endl;
	system("pause");
}