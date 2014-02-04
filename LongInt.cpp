#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <iterator>
#include "LongInt.hpp"
#include "Digits.hpp"

using namespace std;

ostream& operator<<(ostream& os, const LongInt& long_int)
{
	unsigned short num_digits = long_int.size() * 3 / 10;
	Digits digits(num_digits, 0);
	Digits pow2(1, 1);
	pow2.reserve(num_digits);
	for (size_t index = 0; index < long_int.size(); ++index) {
		if (long_int[index])
			digits += pow2;
		pow2.mul2();
	}

	os << digits;
	return os;
}

LongInt &LongInt::operator=(const LongInt &rhs)
{
	*this = rhs;
	return *this;
}

std::istream& operator>>(std::istream& is, LongInt &obj)
{
  string str;
  is >> str;
  LongInt long_int(str);
  obj = long_int;
  return is;
}

unsigned short LongInt::char2dec(char digit)
{
	char difference = digit - '0';
	if (difference >= 0 && difference < 10)
		return difference;
	else
		throw invalid_argument(&digit);
}

void LongInt::create_from_decimal_str(string &str)
{
	Digits digits(str.length(), 0);
	bool carry = false;
	transform(str.begin(), str.end(), digits.begin(), char2dec);
	this->reserve((digits.size() * 10 + 3) / 3);
	while (find_if(
			digits.rbegin(),
			digits.rend(),
			bind1st(not_equal_to<unsigned short>(), 0)) <
						digits.rend()) {
		this->push_back(digits.divide2());
	}
}

void LongInt::push_most_significant_hex(char digit)
{
	switch (digit) {
	case '0':
	break;
	case '1':
		this->push_back(1);
	break;
	case '2':
		this->push_back(0); this->push_back(1);
	break;
	case '3':
		this->push_back(1); this->push_back(1);
	break;
	case '4':
		this->push_back(0); this->push_back(0); this->push_back(1);
	break;
	case '5':
		this->push_back(1); this->push_back(0); this->push_back(1);
	break;
	case '6':
		this->push_back(0); this->push_back(1); this->push_back(1);
	break;
	case '7':
		this->push_back(1); this->push_back(1); this->push_back(1);
	break;
	case '8':
		this->push_back(0); this->push_back(0); this->push_back(0); this->push_back(1);
	break;
	case '9':
		this->push_back(1); this->push_back(0); this->push_back(0); this->push_back(1);
	break;
	case 'A':
	case 'a':
		this->push_back(0); this->push_back(1); this->push_back(0); this->push_back(1);
	break;
	case 'B':
	case 'b':
		this->push_back(1); this->push_back(1); this->push_back(0); this->push_back(1);
	break;
	case 'C':
	case 'c':
		this->push_back(0); this->push_back(0); this->push_back(1); this->push_back(1);
	break;
	case 'D':
	case 'd':
		this->push_back(1); this->push_back(0); this->push_back(1); this->push_back(1);
	break;
	case 'E':
	case 'e':
		this->push_back(0); this->push_back(1); this->push_back(1); this->push_back(1);
	break;
	case 'F':
	case 'f':
		this->push_back(1); this->push_back(1); this->push_back(1); this->push_back(1);
	break;
	default:
		throw invalid_argument(string(1, digit));
	}
}

void LongInt::push_hex2bin(char digit)
{
	switch (digit) {
	case '0':
		this->push_back(0); this->push_back(0); this->push_back(0); this->push_back(0);
	break;
	case '1':
		this->push_back(1); this->push_back(0); this->push_back(0); this->push_back(0);
	break;
	case '2':
		this->push_back(0); this->push_back(1); this->push_back(0); this->push_back(0);
	break;
	case '3':
		this->push_back(1); this->push_back(1); this->push_back(0); this->push_back(0);
	break;
	case '4':
		this->push_back(0); this->push_back(0); this->push_back(1); this->push_back(0);
	break;
	case '5':
		this->push_back(1); this->push_back(0); this->push_back(1); this->push_back(0);
	break;
	case '6':
		this->push_back(0); this->push_back(1); this->push_back(1); this->push_back(0);
	break;
	case '7':
		this->push_back(1); this->push_back(1); this->push_back(1); this->push_back(0);
	break;
	case '8':
		this->push_back(0); this->push_back(0); this->push_back(0); this->push_back(1);
	break;
	case '9':
		this->push_back(1); this->push_back(0); this->push_back(0); this->push_back(1);
	break;
	case 'A':
	case 'a':
		this->push_back(0); this->push_back(1); this->push_back(0); this->push_back(1);
	break;
	case 'B':
	case 'b':
		this->push_back(1); this->push_back(1); this->push_back(0); this->push_back(1);
	break;
	case 'C':
	case 'c':
		this->push_back(0); this->push_back(0); this->push_back(1); this->push_back(1);
	break;
	case 'D':
	case 'd':
		this->push_back(1); this->push_back(0); this->push_back(1); this->push_back(1);
	break;
	case 'E':
	case 'e':
		this->push_back(0); this->push_back(1); this->push_back(1); this->push_back(1);
	break;
	case 'F':
	case 'f':
		this->push_back(1); this->push_back(1); this->push_back(1); this->push_back(1);
	break;
	default:
		throw invalid_argument(string(1, digit));
	}
}

void LongInt::create_from_hex_str(string &str)
{
	this->reserve((str.size() - 2) * 4);
	for (string::reverse_iterator iter = str.rbegin(); iter < str.rend() - 3; iter++)
		push_hex2bin(*iter);
	push_most_significant_hex(*(str.rend() - 3));
}

void LongInt::create_from_string(string &str)
{
	if(!str.compare(0, 2, "0x", 2) || !str.compare(0, 2, "0X", 2)){
		create_from_hex_str(str);
	} else {
		create_from_decimal_str(str);
	}
}

LongInt::LongInt(string &str)
{
	create_from_string(str);
}

LongInt::LongInt(const char *str)
{
	string param(str);
	create_from_string(param);
}

LongInt &LongInt::operator+=(const LongInt &rhs)
{
	size_t num_bits = rhs.size();
	if (this->size() < num_bits)
		this->resize(num_bits);
	bool carry = 0;
	size_t index;
	for (index = 0; index < num_bits; index++)
	{
		if ((*this)[index] && rhs[index]) {
			if (carry)
				(*this)[index] = 1;
			else
				(*this)[index] = 0;
			carry = 1;
		} else if (!((*this)[index] || rhs[index])) {
			if (carry)
				(*this)[index] = 1;
			else
				(*this)[index] = 0;
			carry = 0;
		} else {
			(*this)[index] = !carry;
			carry = !(*this)[index];
		}
	}

	num_bits = this->size();
	while (carry)
		if (index < num_bits) {
			carry = (*this)[index];
			(*this)[index] = !(*this)[index];
		} else {
			this->push_back(1);
			return *this;
		}
	return *this;
}

LongInt &operator+(LongInt op1, const LongInt &op2)
{
	return op1+=op2;
}

void LongInt::dump(ostream& os)
{
	for (int i = this->size() - 1; i >= 0; i--)
		os << (*this)[i];
}

LongInt &LongInt::operator*=(const LongInt &rhs)
{
	LongInt lhs(*this);
	size_t rhs_num_bits = rhs.size(), lhs_num_bits = lhs.size();
	lhs.resize(lhs_num_bits + rhs_num_bits);
	this->clear();
	for (size_t index = 0; index < rhs_num_bits; index++) {
		if (rhs[index])
			*this += lhs;
		for (int i = lhs_num_bits + index - 1; i >= 0; i--)
			lhs[i+1] = lhs[i];
		lhs[index] = 0;
	}
	return *this;
}

LongInt &operator*(LongInt op1, const LongInt &op2)
{
	return op1*=op2;
}

bool operator<(const LongInt &lhs, const LongInt &rhs)
{
	size_t lhs_size = lhs.size();
	size_t rhs_size = rhs.size();

	if (lhs_size < rhs_size)
		return true;
	else if (rhs_size < lhs_size)
		return false;

	for (size_t i = lhs_size - 1; i > 0; i--)
		if (lhs[i] ^ rhs[i])
			return rhs[i];
	return false;
}

bool operator>=(const LongInt &lhs, const LongInt &rhs)
{
	return !(lhs < rhs);
}

bool operator>(const LongInt &lhs, const LongInt &rhs)
{
	return rhs < lhs;
}

bool operator<=(const LongInt &lhs, const LongInt &rhs)
{
	return !(lhs > rhs);
}

bool operator==(const LongInt &lhs, const LongInt &rhs)
{
	return !(lhs > rhs || lhs < rhs);
}
