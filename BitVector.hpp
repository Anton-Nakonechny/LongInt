#ifndef BITVECTOR_HPP_
#define BITVECTOR_HPP_

#include "Vector.hpp"

class BitVector{
	size_t bit_count;
	Vector storage;
public:
	static const unsigned char BITS_PER_BYTE = 32;
	BitVector():bit_count(0) {}
	BitVector(const BitVector &bv);
	size_t size() const { return bit_count; }
	size_t reserved_size() const { return storage.reserved_size() * BITS_PER_BYTE; }
	bool operator[](size_t index) const;
	void push_back(bool);
	void reserve(size_t size);
	void resize(size_t size);
	void set_bit(size_t index);
	void clear_bit(size_t index);
	void clear() { storage.clear(); };
	void shift_right(size_t start, size_t num_bits);
	void remove_leading_zeroes();
};



#endif /* BITVECTOR_HPP_ */
