#include <stdexcept>
#include "BitVector.hpp"

bool BitVector::operator[](size_t index) const
{
	if (index >= bit_count)
		throw std::out_of_range("");
	return storage[index / BITS_PER_BYTE] & 1 << index % BITS_PER_BYTE;
}

void BitVector::push_back(bool val)
{
	if (bit_count == reserved_size())
		storage.grow();
	if (bit_count % BITS_PER_BYTE == 0)
		storage.push_back(val);
	else
		storage[bit_count / BITS_PER_BYTE] |= val << bit_count % BITS_PER_BYTE;
	bit_count++;
}

void BitVector::reserve(size_t size)
{
	if (size <= storage.reserved_size())
		return;
	storage.reserve((size + BITS_PER_BYTE - 1) / BITS_PER_BYTE);
}

void BitVector::resize(size_t size)
{
	if (size <= BitVector::size())
		return;
	storage.resize((size + BITS_PER_BYTE - 1) / BITS_PER_BYTE);
	bit_count = size;
}

void BitVector::clear_bit(size_t index)
{
	storage[index / BITS_PER_BYTE] &= ~(1 << index % BITS_PER_BYTE);
}

void BitVector::set_bit(size_t index)
{
	storage[index / BITS_PER_BYTE] |= 1 << index % BITS_PER_BYTE;
}
