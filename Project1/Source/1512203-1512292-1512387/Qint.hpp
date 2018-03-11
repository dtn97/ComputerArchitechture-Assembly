//
//  Qint.hpp
//  BigNum
//
//  Created by NhonItus on 3/18/17.
//  Copyright © 2017 NhonItus. All rights reserved.
//

#ifndef Qint_hpp
#define Qint_hpp

#include <vector>
#include <istream>
using namespace std;

class Qint
{
private:
    long long arrayBits[2]; 

	//hàm set bit vào vị trí
	void setBit(long long, int);

	// dịch trái 1 bit
    Qint left()const;    
    
	// dịch phải 1 bit
    Qint right()const;   
public:
	// khởi tạo Qint từ 2 long long
	Qint(long long, long long);

	// hàm trả về chuỗi nhị phân của Qint
	string decToBin() const; 

	// hàm trả về chuỗi nhị phân của Qint
	vector<bool> DecToBin() const;

	// khởi tạo mặc định
    Qint();      
    
	// khởi tạo từ chuỗi số thập phân
    Qint(const string&);              

	// khởi tạo từ chuỗi số và kiểu của nó
	Qint(const string&, const string&); 
    
	// khởi tạo sao chép
    Qint(const Qint&);     

	//khởi tạo từ vector<bool>

	Qint(const vector<bool>&);
    
	// hủy mặc định
    ~Qint();    
    
	// toán tử =
    Qint& operator = (const Qint&);     
    
	//tra ve chuoi so co kieu cho truoc 
	string write(const string&)const;           

	//hàm trả về 128 bit trước của phép nhân 
    Qint nhan(const Qint&a)const;     
    
	// toán tử dịch trái
    Qint operator << (unsigned int )const;     
    
	// toán tử dịch phải
    Qint operator >> (unsigned int )const;     
    
	// toán tử &
    Qint operator & (const Qint&) const;      
    
	// toán tử |
    Qint operator | (const Qint&) const;      
    
	// toán tử ^
	Qint operator ^ (const Qint&) const;      
   
	//toán tử ~
	friend Qint operator ~ (const Qint&t);         

	// toán tử  -
	friend Qint operator - (const Qint&t);      
    
	//toán tử +
    Qint operator + (const Qint&) const;             
    
	//toán tử -
	Qint operator - (const Qint&) const;             
    
	//toán tử *
	Qint operator * (const Qint&) const;             
    
	//toán tử /
	Qint operator / (const Qint&) const;             
    
	//toán tử %
	Qint operator % (const Qint&) const;             

	// phép ror
	Qint ror(unsigned int t) const;              

	//phép rol
	Qint rol(unsigned int t) const;               
};

#endif /* Qint_hpp */
