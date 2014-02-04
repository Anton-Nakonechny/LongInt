#include <iterator>
#include "Digits.hpp"

using namespace std;

bool Digits::divide2()
{
	bool carry = false;
	for (vector<unsigned short>::iterator iter = this->begin(); iter < this->end(); iter++) {
		unsigned char cur_dig = *iter + carry * 10;
		*iter = cur_dig / 2;
		carry = cur_dig % 2;
	}
	return carry;
}

void Digits::mul2()
{
	bool carry = false;
	for (vector<unsigned short>::iterator iter = this->begin(); iter < this->end(); iter++) {
		unsigned char cur_dig = *iter * 2  + carry;
		*iter = cur_dig % 10;
		carry = cur_dig / 10;
	}
	if (carry)
		this->push_back(1);
}

Digits &Digits::operator+=(const Digits &rhs)
{
	if (this->size() < rhs.size())
		this->resize(rhs.size());
	vector<unsigned short>::iterator lhs_iter = this->begin();
	bool carry = false;
	for (vector<unsigned short>::const_iterator rhs_iter = rhs.begin();
				rhs_iter < rhs.end();
				rhs_iter++, lhs_iter++) {
		unsigned char tmp = *lhs_iter + *rhs_iter + carry;
		*lhs_iter = tmp % 10;
		carry = tmp / 10;
	}
	while (carry) {
		if (lhs_iter < this->end()) {
			unsigned char tmp = *lhs_iter + carry;
			*lhs_iter = tmp % 10;
			carry = tmp / 10;
			lhs_iter+=1;
		} else {
			this->push_back(1);
			return *this;
		}
	}
	return *this;
}

Digits::Digits(size_t num, unsigned char val):
		std::vector<unsigned short>(num, val) {}

ostream& operator<<(ostream& os, const Digits& digits)
{
	copy(digits.rbegin(), digits.rend(), ostream_iterator<unsigned short>(os));
	return os;
}
