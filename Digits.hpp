#include <iostream>
#include "Vector.hpp"

#ifndef DIGITS_HPP_
#define DIGITS_HPP_

/* digits are stored in parent container class in reverse order
 * form least significant to most significant*/
class Digits : public Vector {

public:
	Digits(size_t num, unsigned char val);

	/* divides decimal number by 2 returns the modulo*/
	bool divide2();

	/* multiplies number passed by 2 */
	void mul2();
	bool non_zero();

	Digits &operator+=(const Digits &rhs);
	friend std::ostream &operator<<(std::ostream& os, const Digits &digits);
};

#endif /* DIGITS_HPP_ */
