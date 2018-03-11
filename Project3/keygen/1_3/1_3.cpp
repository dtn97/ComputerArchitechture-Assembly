#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int getUserNameValue(string s) {
	int res = 0;
	for (auto i : s) {
		if (i < 'A')
			return -1;
		res += (i >= 'Z') ? (i - 32) : i;
	}
	return res;
}

string getPassWord(int tmp) {
	string res;
	while (tmp > 0) {
		res.push_back(tmp % 10 + '0');
		tmp /= 10;
	}
	int n = res.length();
	for (int i = 0; i <= n / 2; ++i)
		swap(res[i], res[n - 1 - i]);
	return res;
}

int main() {
	cout << "Do an KTMT & HN" << endl;
	cout << "Keygen 1_3" << endl;
	cout << "Do Thanh Nhon - 1512387" << endl;
	cout << "Nguyen Quoc Huy - 1512203" << endl;
	cout << "Chau Hoang Long - 1512292" << endl << endl << endl;
	string username;
	int tmp = 0;
	do {
		cout << "Nhap user name:" << endl;
		getline(cin, username);
		if (username.length() > 10)
			username.resize(10);
		tmp = getUserNameValue(username);
		if (tmp == -1)
			cout << "User name bao gom cac ki tu alphabet co ma askii tu 65 tro len. Moi ban nhap lai" << endl;
	} while (tmp == -1);

	tmp ^= 22136;
	tmp ^= 4660;

	string password = getPassWord(tmp);
	cout << "User name: " << username << endl;
	cout << "PassWord: " << password << endl;

	cin.get();
	return 0;
}