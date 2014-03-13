#include <iostream>
#include <string>
#include "BitVector.hpp"

#ifndef LONGINT_HPP_
#define LONGINT_HPP_

struct	bad_num{};

/* bits are stored in parent container class in reverse order
 * form least significant to most significant*/
class LongInt : public BitVector<unsigned int> {

	/* converts character to corresponding numeric value */
	static unsigned short char2dec(const char digit);

	/*parses decimal string*/
	void create_from_decimal_str(const std::string &str);

	/*parses hex string*/
	void create_from_hex_str(const std::string &str);

	/* wrapper method */
	void create_from_string(const std::string &str);

	/*helper table-like functions for creating from hex */
	void push_hex2bin(const char digit);
	void push_most_significant_hex(const char digit);

public:
	LongInt &operator*=(const LongInt &rhs);
	LongInt &operator+=(const LongInt &rhs);

	/* behaves as >>operator but dumps in binary form */
	void dump(std::ostream& os);
	bool is_zero() const { return bit_count == 0; }

	LongInt(const std::string &str);
	LongInt(const char *str);
	friend bool operator< (const LongInt &lhs, const LongInt &rhs);
	friend bool operator>=(const LongInt &lhs, const LongInt &rhs);
	friend bool operator>(const LongInt &lhs, const LongInt &rhs);
	friend bool operator<=(const LongInt &lhs, const LongInt &rhs);
	friend bool operator==(const LongInt &lhs, const LongInt &rhs);

	friend std::ostream &operator<<(std::ostream& os, const LongInt &long_int);
	friend std::istream &operator>>(std::istream& is, LongInt &obj);
	friend LongInt &operator+(LongInt, const LongInt &long_int);
	friend LongInt &operator*(LongInt, const LongInt &long_int);
};

#endif /* LONGINT_HPP_ */
