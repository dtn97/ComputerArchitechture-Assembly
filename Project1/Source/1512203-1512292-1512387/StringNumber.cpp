#include "StringNumber.hpp"

const int maxLenBit = 128;
const int maxLenFra = 112;
const int maxLenExp = 15;
const int maxExpVal = (1 << 14) - 1;
const int minExpVal = -(1 << 14) + 2;
const int speExpVal = -(1 << 14) + 1;

template<typename T> void swap(T &x, T &y) {
	T temp = x;
	x = y;
	y = temp;
}

void reverse(std::string &num) {
	for (int i = 0, len = num.length(); i < len / 2; ++i)
		swap(num[i], num[len - i - 1]);
}

/* ---------------------------------------------------------------------------------- */

bool isZero(const std::string &num) {
	for (int i = 0, len = num.length(); i < len; ++i)
	if (num[i] >= '1' && num[i] <= '9')
		return false;
	return true;
}

char dec_mod_2(const std::string &num) {
	return ((num[num.length() - 1] - '0') % 2) + '0';
}

std::string bin_one_complement(const std::string &num) {
	std::string res = num;
	for (int i = 0, len = res.length(); i < len; ++i)
		res[i] = (1 - (res[i] - '0')) + '0';
	return res;
}

std::string bin_plus_1(const std::string &num) { // num is a non-negative binary integer
	std::string res = "";
	int t = 1;
	for (int i = num.length() - 1; i >= 0; --i) {
		t += (num[i] - '0');
		res += (t % 2) + '0';
		t /= 2;
	}
	if (t > 0 && res.length() < maxLenBit) res += '1';
	reverse(res);
	return res;
}

std::string bin_minus_1(const std::string &num) { // num is a positive binary integer 
	std::string res = "";
	int t = 1;
	for (int i = num.length() - 1; i >= 0; --i) {
		if (num[i] - '0' >= t) {
			res += (num[i] - '0' - t) + '0';
			t = 0;
		}
		else {
			res += (num[i] - '0' + 2 - t) + '0';
			t = 1;
		}
	}
	reverse(res);
	return res;
}

std::string dec_div(const std::string &num, int val) { // num is a positive integer
	std::string res = "";
	int t = 0;
	for (int i = 0, len = num.length(); i < len; ++i) {
		t = t * 10 + (num[i] - '0');
		res += (t / val) + '0';
		t %= val;
	}
	int l = res.length() - 1;
	for (int i = 0; i < res.length() - 1; ++i)
	if (res[i] != '0') {
		l = i;
		break;
	}
	return res.substr(l);
}

std::string dec_mul(const std::string &num, int val) { // num is a positive integer
	std::string res = "";
	int t = 0;
	for (int i = num.length() - 1; i >= 0; --i) {
		t += (num[i] - '0')*val;
		res += (t % 10) + '0';
		t /= 10;
	}
	while (t > 0) {
		res += (t % 10) + '0';
		t /= 10;
	}
	reverse(res);
	return res;
}

std::string dec_plus_1(const std::string &num) { // num is a positive integer
	std::string res = "";
	int t = 1;
	for (int i = num.length() - 1; i >= 0; --i) {
		t += (num[i] - '0');
		res += (t % 10) + '0';
		t /= 10;
	}
	if (t > 0 && res.length() < maxLenBit) res += '1';
	reverse(res);
	return res;
}

std::string decToBin_int(std::string num) {
	// num is a positive integer, which represents the part going before the decimal point
	std::string res = "";
	do {
		res += dec_mod_2(num);
		num = dec_div(num, 2);
	} while (!isZero(num));
	reverse(res);
	return res;
}

std::string decToBin_fra(std::string num) {
	// num is a positive integer, which represents the part going after the decimal point
	std::string res = "";
	int reslen = 0;
	do {
		int len = num.length();
		num = dec_mul(num, 2);
		if (len == num.length()) res += '0', reslen++;
		else {
			res += '1', reslen++;
			num = num.substr(1);
		}
		if (reslen > 2 * maxExpVal) break;
	} while (!isZero(num));
	return res;
}

std::string dec_to_bin_int(std::string num) {
	std::string res = decToBin_int(num[0] == '-' ? num.substr(1) : num);
	if (num[0] == '-') return "-" + res;
	return res;
}

std::string mem_dec_to_bin_int(std::string num) {
	std::string res = decToBin_int(num[0] == '-' ? num.substr(1) : num);
	reverse(res);
	while (res.length() < maxLenBit) res += '0';
	res = res.substr(0, maxLenBit);
	reverse(res);
	if (num[0] == '-') res = bin_plus_1(bin_one_complement(res));
	return res;
}

int normalize_float(std::string &b_num) { // bring b_num (in binary) to normalized form
	int p = b_num.find('.');
	int pow_2 = 0;
	while (p > 1) {
		++pow_2;
		swap(b_num[p], b_num[p - 1]);
		--p;
	}
	p = b_num.length();
	if (b_num != "0.0") while (b_num[0] == '0') {
		--pow_2;
		swap(b_num[1], b_num[2]);
		if (b_num[p - 1] == '.') b_num += '0', ++p;
		b_num = b_num.substr(1), --p;
		if (b_num[0] == '.') b_num = '0' + b_num, ++p;
	}
	return pow_2;
}

static const std::string ZERO_float() { // generate ZERO number (according to IEEE 754-2008)
	static std::string result;
	if (result.empty())
	for (int i = 0; i < maxLenExp; ++i)
		result += '0';
	return result;
}

static const std::string INF_float() { // generate INF number (according to IEEE 754-2008)
	static std::string result;
	if (result.empty())
	for (int i = 0; i < maxLenExp; ++i)
		result += i >= 1 && i <= 15 ? '1' : '0';
	return result;
}

bool isNaN(const std::string &num) { // check if num is a NaN (not a number)
	for (int i = 1; i <= 15; ++i)
	if (num[i] != '1')
		return false;
	for (int i = 16; i < maxLenExp; ++i)
	if (num[i] != '0')
		return true;
	return false;
}

void bin_shr(std::string &num, int pow_2) { // divide num into 2^pow_2 
	int p = num.find('.');
	if (p == std::string::npos) {
		p = num.length();
		num += ".0";
	}
	int len = num.length();
	for (int i = 0; i < pow_2; ++i) {
		swap(num[p], num[p + 1]);
		++p;
		if (num[len - 1] == '.') num += '0', ++len;
	}
	p = 0;
	while (num[p] == '0' && num[p + 1] != '.')
		++p;
	num = num.substr(p);
}

std::string value_to_bias(int num) { // convert num to bias number, where the bias is maxExpVal
	num += maxExpVal;
	std::string res = "";
	for (int i = 0; i < 15; ++i) {
		res += (num % 2) + '0';
		num /= 2;
	}
	reverse(res);
	return res;
}

int bias_to_value(std::string num) { // change num back to value (integer), where the bias is maxExpVal
	int res = 0;
	for (int i = 0, len = num.length(); i < len; ++i) {
		res *= 2;
		res += (num[i] - '0');
	}
	return res - maxExpVal;
}

std::string dec_to_bin_float(std::string num) {
	if (isZero(num)) return ZERO_float();
	std::string res = "";
	if (num[0] == '-') res += '-';
	num = num.substr(1);
	int p = num.find('.');
	if (p == std::string::npos) {
		p = num.length();
		num += ".0";
	}

	return res + decToBin_int(num.substr(0, p))
		+ '.' + decToBin_fra(num.substr(p + 1));
}

std::string mem_dec_to_bin_float(std::string num) {
	if (isZero(num)) return ZERO_float();
	std::string res;
	if (num[0] == '-') res += '1', num = num.substr(1);
	else res += '0';

	int p = num.find('.');
	if (p == std::string::npos) {
		p = num.length();
		num += ".0";
	}
	std::string firstPart = decToBin_int(num.substr(0, p));
	std::string secondPart = decToBin_fra(num.substr(p + 1));
	std::string b_num = firstPart + '.' + secondPart;
	std::string b_num_special = b_num;
	int pow_2 = normalize_float(b_num);
	if (pow_2 > maxExpVal)
		return res[0] == '0' ? INF_float() : ('1' + INF_float().substr(1));
	if (pow_2 < minExpVal) {
		for (int i = 1; i <= 15; ++i)
			res += '0';
		bin_shr(b_num_special, -minExpVal + 1);
		for (int i = 16, len = b_num.length(); i < maxLenBit; ++i)
		if (i - 16 + 2 < len) res += b_num_special[i - 16 + 2];
		else res += '0';

		return res;
	}
	res += value_to_bias(pow_2);
	for (int i = 16, len = b_num.length(); i < maxLenBit; ++i) {
		if (i - 16 + 2 < len) res += b_num[i - 16 + 2];
		else res += '0';
	}
	return res;
}

std::string binToDec_int(std::string num) {
	std::string temp = "0";
	for (int i = 0, len = num.length(); i < len; ++i) {
		temp = dec_mul(temp, 2);
		if (num[i] == '1')
			temp = dec_plus_1(temp);
	}
	return temp;
}

std::string binToDec_fra(std::string num) {
	std::string temp = "0";
	for (int i = num.length() - 1; i >= 0; --i) {
		temp = num[i] + temp;
		temp = dec_mul(temp, 5);
	}
	return temp;
}

std::string bin_to_dec_int(std::string num) {
	std::string res = "";
	if (num[0] == '-') res += '-', num = num.substr(1);
	return res + binToDec_int(num);
}

std::string mem_bin_to_dec_int(std::string num) {
	std::string res = "";
	if (num[0] == '1') {
		res += '-';
		num = bin_one_complement(bin_minus_1(num));
	}
	return res + binToDec_int(num);
}

void denormalize_float(std::string &num, int pow_2) {
	int p = num.find('.'), len = num.length();
	while (pow_2 > 0) {
		swap(num[p], num[p + 1]);
		++p;
		if (p == len - 1) {
			num += '0';
			++len;
		}
		--pow_2;
	}
	while (pow_2 < 0) {
		swap(num[p], num[p - 1]);
		--p;
		if (p == 0) {
			num = '0' + num;
			++len;
			p = 1;
		}
		++pow_2;
	}
}

std::string return_float(const std::string &num) {
	int pow_2 = bias_to_value(num.substr(1, 15));
	if (pow_2 < minExpVal) {
		if (isZero(num.substr(1))) return "0.0";
		std::string res = "0.";
		for (int i = 0; i < maxExpVal; ++i) res += '0';
		res += num.substr(16);
		return res;
	}
	if (pow_2 > maxExpVal) return num[0] == '0' ? "INF" : "-INF";
	std::string res = "1." + num.substr(16);
	denormalize_float(res, pow_2);
	return res;
}

std::string bin_to_dec_float(std::string num) {
	char sig = num[0] == '-' ? '-' : '\0';
	if (num[0] == '-') num = num.substr(1);
	int p = num.find('.');
	if (p == std::string::npos) {
		p = num.length();
		num += ".0";
	}
	std::string r1 = binToDec_int(num.substr(0, p));
	std::string r2 = binToDec_fra(num.substr(p + 1));
	return sig + r1 + '.' + r2;
}

std::string mem_bin_to_dec_float(std::string num) {
	char sig = num[0] == '1' ? '-' : '\0';
	num = return_float(num);
	if (num == "-INF" || num == "INF" || num == "0.0") return num;
	int p = num.find('.');
	if (p == std::string::npos) {
		p = num.length();
		num += ".0";
	}
	std::string r1 = binToDec_int(num.substr(0, p));
	std::string r2 = binToDec_fra(num.substr(p + 1));
	return sig + r1 + '.' + r2;
}

std::string hexToBin_c(char c) {
	if (c == '0') return "0000";
	if (c == '1') return "0001";
	if (c == '2') return "0010";
	if (c == '3') return "0011";
	if (c == '4') return "0100";
	if (c == '5') return "0101";
	if (c == '6') return "0110";
	if (c == '7') return "0111";
	if (c == '8') return "1000";
	if (c == '9') return "1001";
	if (c == 'A') return "1010";
	if (c == 'B') return "1011";
	if (c == 'C') return "1100";
	if (c == 'D') return "1101";
	if (c == 'E') return "1110";
	if (c == 'F') return "1111";
	return "";
}

char binToHex_c(std::string num) { // num has length of 4
	if (num == "0000") return '0';
	if (num == "0001") return '1';
	if (num == "0010") return '2';
	if (num == "0011") return '3';
	if (num == "0100") return '4';
	if (num == "0101") return '5';
	if (num == "0110") return '6';
	if (num == "0111") return '7';
	if (num == "1000") return '8';
	if (num == "1001") return '9';
	if (num == "1010") return 'A';
	if (num == "1011") return 'B';
	if (num == "1100") return 'C';
	if (num == "1101") return 'D';
	if (num == "1110") return 'E';
	if (num == "1111") return 'F';
	return '\0';
}

std::string hex_to_bin_int(std::string num) { // positive integer only
	std::string res = "";
	for (int i = 0, len = num.length(); i < len; ++i)
		res += hexToBin_c(num[i]);
	return res;
}

std::string bin_to_hex_int(std::string num) { // positive integer only
	std::string res = "";
	int k = num.length() % 4;
	std::string leadingzero(k, '0');
	num = leadingzero + num;
	for (int i = 0, len = num.length(); i < len; i += 4)
		res += binToHex_c(num.substr(i, 4));
	return res;
}

void writeIntBin(std::string num, std::ostream &os) {
	reverse(num);
	while (num.length() % 4 != 0) num += '0';
	for (int len = num.length(); len > 4; len -= 4) {
		if (num[len - 1] == '0' && num[len - 2] == '0' && num[len - 3] == '0' && num[len - 4] == '0')
			num = num.substr(0, len - 4);
		else break;
	}
	reverse(num);
	os << num;
}

void writeIntHex(std::string num, std::ostream &os) {
	reverse(num);
	for (int len = num.length(); len > 1; --len)
	if (num[len - 1] == '0') num = num.substr(0, len - 1);
	else break;
	reverse(num);
	os << num;
}