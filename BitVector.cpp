#include <stdexcept>
#include "BitVector.hpp"

BitVector::BitVector(const BitVector &bv)
{
	storage = bv.storage;
	bit_count = bv.bit_count;
}

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

void BitVector::remove_leading_zeroes()
{
	size_t i;
	for (i = storage.size() - 1; i > 0; i--)
		if (storage[i] != 0)
			break;

	if (storage[i] == 0)
		bit_count = 0;
	else {
			unsigned char num_bits = 0;
			unsigned char most_significant_byte = storage[i];
			while (most_significant_byte) {
				most_significant_byte >>= 1;
				num_bits++;
			}
			bit_count = i * BITS_PER_BYTE + num_bits;
		}
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

void BitVector::shift_right(const size_t start, const size_t num_positions)
{
	size_t cur_size = bit_count;
	size_t first_byte = (start + BITS_PER_BYTE - 1) / BITS_PER_BYTE;
	size_t last_byte = cur_size / BITS_PER_BYTE;

	resize(bit_count + num_positions);

	/* Move by byte if possible */
	if (num_positions % BITS_PER_BYTE == 0) {
		size_t num_bytes = num_positions / BITS_PER_BYTE;
		for (size_t i = cur_size; i >= last_byte * BITS_PER_BYTE; i--)
			if((*this)[i])
				set_bit(i + num_positions);
			else
				clear_bit(i + num_positions);

		for (int i = last_byte - 1; i >= first_byte; i--)
			storage[i + num_bytes] = storage[i];

		for (size_t i = first_byte * BITS_PER_BYTE; i > start; i--)
			if((*this)[i])
				set_bit(i + num_positions);
			else
				clear_bit(i + num_positions);

		if ((*this)[start])
			set_bit(start + num_positions);
		else
			clear_bit(start + num_positions);

	} else {
		for (size_t i = cur_size - 1; i > start; i--)
			if((*this)[i])
				set_bit(i + num_positions);
			else
				clear_bit(i + num_positions);

		if((*this)[start])
			set_bit(start + num_positions);
		else
			clear_bit(start + num_positions);
	}
/* Now replace shifted bits with zeroes */
	if (num_positions > BITS_PER_BYTE) {
		for (size_t i = start; i < first_byte * BITS_PER_BYTE; i++)
			clear_bit(i);
		for (size_t i = first_byte; i < last_byte; i++)
			storage[i] = 0;
		for (size_t i = last_byte * BITS_PER_BYTE; i < start + num_positions; i++)
			clear_bit(i);
	} else
		for (size_t i = start; i < start + num_positions; i++)
			clear_bit(i);
}
