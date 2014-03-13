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
	size_t num_digits = long_int.size() * 3 / 10;
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
	reserve((digits.size() * 10 + 3) / 3);
	while (digits.non_zero())
		push_back(digits.divide2());
}
/* TODO to be replaced with bytewise assignment*/
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

LongInt::LongInt(const char *str = "0")
{
	std::string param(str);
	create_from_string(param);
}

LongInt &LongInt::operator+=(const LongInt &rhs)
{
	/* check zeroes first*/
	if (rhs.is_zero())
		return *this;

	if (is_zero()) {
		LongInt rhs_copy(rhs);
		swap(rhs_copy);
		return *this;
	}

	/* Adding leading zeroes to sum with */
	size_t rhs_bits = rhs.size();
	if (this->size() <= rhs_bits)
		this->resize(rhs_bits + BITS_PER_TYPE); /*reserve place for overflow*/

	size_t i;
	bool carry = 0;
	size_t rhs_storage_size = rhs.storage.size();
	for (i = 0; i < rhs_storage_size; i++)
	{
		unsigned int sum = this->storage[i] + rhs.storage[i] + carry;
		carry = MAX_CONTAINER_ITEM_VALUE - this->storage[i] < rhs.storage[i] + carry;
		this->storage[i] = sum;
	}

	size_t storage_size = storage.size();
	while (carry)
		if (i < storage_size) {
			carry = (this->storage[i] == MAX_CONTAINER_ITEM_VALUE);
			this->storage[i] += 1;
			i++;
		} else {
			push_back(1);
			return *this;
		}
	/* TODO this looks like a workaround
	 * might reserve bits more accurate
	 * to be more safe in case of an exception*/
	remove_leading_zeroes();
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
	bool change_order = size() < rhs.size();
	const LongInt &multiplied = change_order ? rhs : *this;
	const LongInt &multiplier = change_order ? *this : rhs;

	LongInt lhs(multiplied), acc;
	size_t rhs_num_bits = multiplier.size();

/* reserve to maximum product length at start to avoid reallocations later*/
	lhs.reserve(lhs.size() + rhs_num_bits);

/* how many positions lhs is shifted to the right */
	size_t last_position = 0;
	if (multiplier[0])
		acc += lhs;

	for (size_t index = 1; index < rhs_num_bits; index++)
		if (multiplier[index]) {
			lhs.shift_right(last_position, index - last_position);
			acc += lhs;
			last_position = index;
		}
	swap(acc);
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
