#ifndef FileHanding_hpp
#define FileHanding_hpp

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Cắt chuỗi bởi khoảng trắng
vector<string> splitString(string);
// đọc nội dung file theo từng dòng
vector<string> readFile(fstream&);
// xuất nội dung ra file
void writeFile(fstream&, const vector<string>&);
// xử lí input số Qint
string handing_int(vector<string>);
// Xử lí input số Qfloat
string handing_float(vector<string>);
// Xử lí việc đọc và xuất file
void handingFile(string (*p)(vector<string>));

#endif