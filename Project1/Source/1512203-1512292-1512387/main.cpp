#include <iostream>
#include "FileHanding.hpp"
#include <stdlib.h>
#include "Qint.hpp"
#include "Qfloat.hpp"
using namespace std;

int main(int argc, const char * argv[]) {

	while (1)
	{
		system("cls");
		cout << "DO AN 1 - KTMT&HN" << endl;
		cout << "1512203 - 1512292 - 1512387" << endl << endl << endl;
		cout << "Nhap 1 de chon input la file" << endl;
		cout << "Nhap 2 de chon input nhap tren console" << endl;
		int choose = 0;
		cin >> choose;
		cin.ignore();
		string temp;
		int tmp = 0;
		cout << "chon 1 de thuc hien voi so nguyen:" << endl;
		cout << "Chon 2 de thuc hien voi so thuc:" << endl;
		cin >> tmp;
		cin.ignore();
		switch (choose)
		{
		case 1:
			switch (tmp)
			{
			case 1:
				cout << "Xu li so nguyen" << endl;
				handingFile(&handing_int);
				break;
			case 2:
				cout << "Xu li so thuc:" << endl;
				handingFile(&handing_float);
				break;
			}
			break;
		case 2:
			cout << "Moi ban nhap bieu thuc: " << endl;
			getline(cin, temp);
			cout << "Ket qua la: " << endl;
			switch (tmp)
			{
			case 1:
				cout << handing_int(splitString(temp));
				break;
			case 2:
				cout << handing_float(splitString(temp));
				break;
			}
			cout << endl;
			system("pause");
			break;
		default:
			exit(0);
		}
	}

    return 0;
} 		 