#ifndef Qfloat_hpp
#define Qfloat_hpp

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Qfloat
{
private:
    long long arrayBits[2];
	// Kiểm tra số thực có giá trị bằng 0 hay không
    bool is_Zero() const;
	// Kiểm tra 1 chuỗi bit toàn là bit 0 hay không
    bool is_Zero(const vector<bool>&) const;
	// So sánh giá trị 2 chuỗi bit
    int compare(vector<bool>, vector<bool>) const;
	// dịch chuỗi bit sang phải
    vector<bool> shiftRight(vector<bool>) const;
	// dịch chuỗi bit sang trái
    vector<bool> shiftLeft(vector<bool>) const;
	// lấy ra chuỗi bit bất kì từ chuỗi bit của số thực
    vector<bool> getBits(int, int) const;
	// 	lấy ra chuỗi bit bất kì từ chuỗi bit của số thực, trả về string
    string getBitsString(int, int) const;
	// tính giá trị nguyên của 1 chuỗi bit
    int getValue(vector<bool>) const;
	// chuyển 1 chuỗi bit sang dạng bù 2
    vector<bool> convertToTwoComplement(vector<bool>) const;
	// chuyển chuỗi bit từ dạng bù 2 thành bình thường
    vector<bool> normalize_TwoComplement(vector<bool>) const;
	// hàm cộng 2 chuỗi bit
    vector<bool> addBinNumber(vector<bool>, vector<bool>) const;
	// hàm cộng phần định trị của 2 số qfloat
    vector<bool> addSignificand(vector<bool>, bool, vector<bool>, bool, bool&) const;
	// trả về số Qfloat có giá trị là vô cùng
    Qfloat getINFfloat(bool) const;
	// trả về số Qfloat có định dạng NaN (không là số)
    Qfloat getNaNFloat() const;
	// đưa kết quả cộng phần định trị 2 số thực về dạng chuẩn 112 bit
    int normalizeSignificand_Add(vector<bool>&) const;
	// Chuyển đổi từ dạng chuẩn sang bias
    vector<bool> bin_To_Bias(int) const;
	// thêm các bit không vào đầu chuỗi bit để có độ dài mong muốn
    vector<bool> fillBits(vector<bool>, int) const;
	// Nhân phần định trị 2 số Qfloat
    vector<bool> multiplySignificand(vector<bool>, vector<bool>) const;
	// đưa kết quả nhân phần định trị về dạng chuẩn 112 bit
    int normalizeSignificand_Multiply(vector<bool>&) const;
	// Chia phần định trị 2 số Qfloat
    vector<bool> divideSignificand(vector<bool>, vector<bool>) const;
	// Đưa kết quả chia phần định trị về dạng chuẩn 112 bit
    int normalizeSignificand_Divide(vector<bool>&) const;
public:
	// phương thức khởi tạo mặc định
    Qfloat();
	//Khởi tạo
	Qfloat(string, string);
	// khởi tạo số Qfloat từ 1 chuỗi bit cho trước
    Qfloat(const vector<bool>&);
	// khởi tạo số Qfloat từ 1 chuỗi số thực cơ số 10 cho trước
    Qfloat(const string&);
	// khởi tạo sao chép
    Qfloat(const Qfloat&);
	// destructor
    ~Qfloat();
	// toán tử =
    Qfloat& operator = (const Qfloat&);
    
	// Toán tử nhập (người dùng sẽ nhập vào chuỗi số thực ở hệ cơ số 10)
    friend ostream& operator << (ostream&, const Qfloat&);
	// Toán tử xuất kết quả ở hệ cơ số 10
    friend istream& operator >> (istream&, Qfloat&);
    
	// trả về mảng bit biểu diễn số Qfloat
    vector<bool> decToBin() const;
	// trả về giá trị thập phân của số Qfloat
    static Qfloat binToDec(const vector<bool>&);
    
	// toán tử cộng 2 số Qfloat
    Qfloat operator + (const Qfloat&) const;
	// toán tử trừ 2 số Qfloat
    Qfloat operator - (const Qfloat&) const;
	// toán tử nhân 2 số Qfloat
    Qfloat operator * (const Qfloat&) const;
	// toán tử chia 2 số Qfloat
    Qfloat operator / (const Qfloat&) const;
	// Trả về chuỗi output theo điều kiện hệ cơ số 2 hoặc 10
	string write(string) const;
};

#endif /* Qfloat_hpp */
