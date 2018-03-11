#ifndef StringNumber_hpp
#define StringNumber_hpp

#include <string>
#include <iostream>

std::string hex_to_bin_int(std::string num); // positive integer only
/*
Convert a hexa number to a binary number (positive integer only)
e.g. F -> 1111
*/

std::string bin_to_hex_int(std::string num); // positive integer only
/*
Convert a binary number to a hexa number (positive integer only)
e.g. 1111 -> F
*/

std::string dec_to_bin_int(std::string num);
/*
convert a decimal number to binary number (integer)
e.g. 7 -> 111
*/

std::string dec_to_bin_float(std::string num);
/*
Convert a decimal number to binary number (float), according to IEEE 754-2008)
e.g. 1.25 -> 1.01
*/

std::string bin_to_dec_int(std::string num);
/*
Convert a binary number to decimal (int)
e.g. 11 -> 3
e.g. -10 -> -2
*/

std::string bin_to_dec_float(std::string num);
/*
Convert a binary number to decimal (float) according to IEEE 754-2008
e.g. 1.1 -> 1.5
e.g. -1.1 -> -1.5
*/

std::string mem_bin_to_dec_int(std::string num);
/*
Convert a binary sequence, which represents how an integer stored in memory, to a decimal integer
e.g. 0000000..10 -> 2
e.g. 1111111..10 -> -2
*/

std::string mem_bin_to_dec_float(std::string num);
/*
Convert a binary sequence, which represents how a real number stored in memory, to a decimal real number
e.g. 000000000000000110....0 -> 3.0
e.g. 100000000000000110....0 -> -3.0
*/

std::string mem_dec_to_bin_int(std::string num);
/*
Convert a decimal integer to a binary sequence, which represents how a integer stored in memory
e.g. 3 -> 000000...011
e.g. -3 -> 111111...101
*/

std::string mem_dec_to_bin_float(std::string num);
/*
Convert a decimal real number to a binary sequence, which represents how a integer stored in memory
e.g. 3.5 -> 0000000000000001110...0
e.g. -3.5 -> 1000000000000001110...0
*/

void writeIntBin(std::string num, std::ostream &os = std::cout);
/*
Print num and delete leading zero (len%4 = 0)
e.g. 0000000...11 -> 0011
*/

void writeIntHex(std::string num, std::ostream &os = std::cout);

#endif
