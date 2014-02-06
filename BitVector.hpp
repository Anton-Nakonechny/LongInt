#ifndef BITVECTOR_HPP_
#define BITVECTOR_HPP_

#include "Vector.hpp"

class BitVector{
	static const unsigned char BITS_PER_BYTE = 8;
	size_t bit_count;
	Vector storage;
public:
	BitVector():bit_count(0)
	{}

	size_t size() const { return bit_count; }
	size_t reserved_size() const { return storage.reserved_size() * BITS_PER_BYTE; }
	bool operator[](size_t index) const;
//	BitVector &operator=(const BitVector &rhs);
	void push_back(bool);
	void reserve(size_t size);
	void resize(size_t size);
	void set_bit(size_t index);
	void clear_bit(size_t index);
	void clear() { storage.clear(); };
};



#endif /* BITVECTOR_HPP_ */
