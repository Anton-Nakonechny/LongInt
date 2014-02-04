#include <iostream>
#include <string>
#include <vector>

#ifndef LONGINT_HPP_
#define LONGINT_HPP_

struct	bad_num{};

/* bits are stored in parent container class in reverse order
 * form least significant to most significant*/
class LongInt : private std::vector<bool> {

	/* converts character to corresponding numeric value */
	static unsigned short char2dec(char digit);

	/*parses decimal string*/
	void create_from_decimal_str(std::string &str);

	/*parses hex string*/
	void create_from_hex_str(std::string &str);

	/* wrapper method */
	void create_from_string(std::string &str);

	/*helper table-like functions for creating from hex */
	void push_hex2bin(char digit);
	void push_most_significant_hex(char digit);

public:
	LongInt &operator=(const LongInt &rhs);
	LongInt &operator*=(const LongInt &rhs);
	LongInt &operator+=(const LongInt &rhs);

	/* behaves as >>operator but dumps in binary form */
	void dump(std::ostream& os);

	LongInt(std::string &str);
	LongInt(const char *str);
	LongInt(){}
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
