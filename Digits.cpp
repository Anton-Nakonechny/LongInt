#include <iterator>
#include "Digits.hpp"

using namespace std;

bool Digits::divide2()
{
	bool carry = false;
	for (size_t index = 0; index < count; index++) {
		unsigned char cur_dig = (*this)[index] + carry * 10;
		(*this)[index] = cur_dig / 2;
		carry = cur_dig % 2;
	}
	return carry;
}

void Digits::mul2()
{
	bool carry = false;
	for (size_t index = 0; index < count; index++) {
		unsigned char cur_dig = (*this)[index] * 2  + carry;
		(*this)[index] = cur_dig % 10;
		carry = cur_dig / 10;
	}
	if (carry)
		this->push_back(1);
}

bool Digits::non_zero()
{
	if (count == 0)
		return false;
	for (size_t i = this->size() - 1; i > 0; i--)
		if ((*this)[i] > 0)
			return true;
	return (*this)[0] != 0;
}

Digits &Digits::operator+=(const Digits &rhs)
{
	size_t rhs_size = rhs.size();
	size_t i;
	if (count < rhs_size)
		this->resize(rhs_size);
	bool carry = false;
	for (i = 0; i < rhs_size; i++) {
		unsigned char tmp = (*this)[i] + rhs[i] + carry;
		(*this)[i] = tmp % 10;
		carry = tmp / 10;
	}

	while (carry) {
		if (i < count) {
			unsigned char tmp = (*this)[i] + carry;
			(*this)[i] = tmp % 10;
			carry = tmp / 10;
		} else {
			this->push_back(1);
			return *this;
		}
	}
	return *this;
}

Digits::Digits(size_t num, unsigned char val):
		Vector(num, val) {}

ostream& operator<<(ostream& os, const Digits& digits)
{
	for (size_t index = digits.size() - 1; index > 0; index--)
		os<<static_cast<unsigned short>(digits[index]);
	os<<static_cast<unsigned short>(digits[0]);
	return os;
}
