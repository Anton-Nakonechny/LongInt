#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <iterator>
#include "LongInt.hpp"
#include "Digits.hpp"

std::ostream& operator<<(std::ostream& os, const LongInt& long_int)
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

std::istream& operator>>(std::istream& is, LongInt &obj)
{
  std::string str;
  is >> str;
  LongInt long_int(str);
  obj = long_int;
  return is;
}

unsigned short LongInt::char2dec(const char digit)
{
	char difference = digit - '0';
	if (difference >= 0 && difference < 10)
		return difference;
	else
		throw std::invalid_argument("");
}

void LongInt::create_from_decimal_str(const std::string &str)
{
	Digits digits(str.length(), 0);
	bool carry = false;
	size_t index = 0;
	for (std::string::const_iterator iter = str.begin(); iter < str.end(); iter++, index++)
		digits[index] = char2dec(*iter);
	this->reserve((digits.size() * 10 + 3) / 3);
	while (digits.non_zero())
		this->push_back(digits.divide2());
}

void LongInt::push_most_significant_hex(const char digit)
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
		throw std::invalid_argument(std::string(1, digit));
	}
}

void LongInt::push_hex2bin(const char digit)
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
		throw std::invalid_argument(std::string(1, digit));
	}
}

void LongInt::create_from_hex_str(const std::string &str)
{
	this->reserve((str.size() - 2) * 4);
	for (std::string::const_reverse_iterator iter = str.rbegin(); iter < str.rend() - 3; iter++)
		push_hex2bin(*iter);
	push_most_significant_hex(*(str.rend() - 3));
}

void LongInt::create_from_string(const std::string &str)
{
	if(!str.compare(0, 2, "0x", 2) || !str.compare(0, 2, "0X", 2)){
		create_from_hex_str(str);
	} else {
		create_from_decimal_str(str);
	}
	/* reserved maximum possible needed memory
	 * shrink leading zeroes now */
	remove_leading_zeroes();
}

LongInt::LongInt(const std::string &str)
{
	create_from_string(str);
}

LongInt::LongInt(const char *str)
{
	std::string param(str);
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
				this->set_bit(index);
			else
				this->clear_bit(index);
			carry = 1;
		} else if (!((*this)[index] || rhs[index])) {
			if (carry)
				this->set_bit(index);
			else
				this->clear_bit(index);
			carry = 0;
		} else {
			if (carry)
				this->clear_bit(index);
			else
				this->set_bit(index);
			carry = !(*this)[index];
		}
	}

	num_bits = this->size();
	while (carry)
		if (index < num_bits) {
			carry = (*this)[index];
			if(carry)
				clear_bit(index);
			else
				set_bit(index);
			index++;
		} else {
			push_back(1);
			return *this;
		}
	return *this;
}

LongInt &operator+(LongInt op1, const LongInt &op2)
{
	return op1+=op2;
}

void LongInt::dump(std::ostream& os)
{
	for (int i = this->size() - 1; i >= 0; i--)
		os << (*this)[i];
}

LongInt &LongInt::operator*=(const LongInt &rhs)
{
	LongInt lhs(*this);
	size_t rhs_num_bits = rhs.size(), lhs_num_bits = lhs.size();
	lhs.reserve(lhs_num_bits + rhs_num_bits);
	this->clear();
	size_t last_position = 0;
	if (rhs[0])
		*this += lhs;

	for (size_t index = 1; index < rhs_num_bits; index++)
		if (rhs[index]) {
			lhs.shift_right(last_position, index - last_position);
			*this += lhs;
			last_position = index;
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
