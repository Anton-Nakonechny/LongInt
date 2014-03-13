#ifndef BITVECTOR_HPP_
#define BITVECTOR_HPP_

#include "Vector.hpp"

/*TODO would work incorrectly with signed container type
 *should fail in compile time in this case
 *enable_if is to be used
 */
template<typename T = unsigned int> class BitVector{
protected:
	size_t bit_count;
	Vector<T> storage;
public:
	static const unsigned char BITS_PER_TYPE;
	static const T MAX_CONTAINER_ITEM_VALUE;
	BitVector();
	BitVector(const BitVector<T> &bv);
	size_t size() const { return bit_count; }
	size_t reserved_size() const { return storage.reserved_size() * BITS_PER_TYPE; }
	bool operator[](size_t index) const;
	void push_back(bool);
	void reserve(size_t size);
	void resize(size_t size);
	void set_bit(size_t index);
	void clear_bit(size_t index);
	void clear() { storage.clear(); bit_count = 0;}
	/* shifts bitvector to the right
	 * since number is stored in reverse order
	 * shifts in most significant bit direction
	 * i.e. multiply number by a power of 2*/
	void shift_right(size_t start, size_t num_bits);
	void remove_leading_zeroes();
	void swap(BitVector<T> &bit_vector);
};

template<typename T> const unsigned char BitVector<T>::BITS_PER_TYPE =
		sizeof(T) * 8 / sizeof(char);

template<typename T> const T BitVector<T>::MAX_CONTAINER_ITEM_VALUE =
		static_cast<T>(-1);

template<typename T> BitVector<T>::BitVector():bit_count(0) {}

template<typename T> void BitVector<T>::swap(BitVector<T> &bit_vector)
{
	storage.swap(bit_vector.storage);
	std::swap(bit_count, bit_vector.bit_count);
}


template<typename T> BitVector<T>::BitVector(const BitVector<T> &bv)
{
	storage = bv.storage;
	bit_count = bv.bit_count;
}

template<typename T> bool BitVector<T>::operator[](size_t index) const
{
	if (index >= bit_count)
		throw std::out_of_range("");
	return storage[index / BITS_PER_TYPE] & 1 << index % BITS_PER_TYPE;
}

template<typename T> void BitVector<T>::push_back(bool val)
{
	if (bit_count == reserved_size())
		storage.grow();
	if (bit_count % BITS_PER_TYPE == 0)
		storage.push_back(val);
	else
		storage[bit_count / BITS_PER_TYPE] |= val << bit_count % BITS_PER_TYPE;
	bit_count++;
}

template<typename T> void BitVector<T>::reserve(size_t size)
{
	if (size <= storage.reserved_size())
		return;
	storage.reserve((size + BITS_PER_TYPE - 1) / BITS_PER_TYPE);
}

template<typename T> void BitVector<T>::remove_leading_zeroes()
{
	size_t i, storage_size = storage.size();

	if (storage_size == 0)
		return;

	for (i = storage_size - 1; i > 0; i--)
		if (storage[i] != 0)
			break;

	unsigned char num_bits = 0;
	T most_significant_byte = storage[i];
	while (most_significant_byte) {
		most_significant_byte >>= 1;
		num_bits++;
	}
	bit_count = i * BITS_PER_TYPE + num_bits;
}

template<typename T> void BitVector<T>::resize(size_t size)
{
	if (size <= BitVector::size())
		return;
	storage.resize((size + BITS_PER_TYPE - 1) / BITS_PER_TYPE);
	bit_count = size;
}

template<typename T> void BitVector<T>::clear_bit(size_t index)
{
	storage[index / BITS_PER_TYPE] &= ~(1 << index % BITS_PER_TYPE);
}

template<typename T> void BitVector<T>::set_bit(size_t index)
{
	storage[index / BITS_PER_TYPE] |= 1 << index % BITS_PER_TYPE;
}

template<typename T> void BitVector<T>::shift_right(const size_t start, const size_t num_positions)
{
	size_t cur_size = bit_count;
	size_t last_byte = cur_size / BITS_PER_TYPE;
	int first_byte = (start + BITS_PER_TYPE - 1) / BITS_PER_TYPE;
	/* need to compare with -1, must be signed */

	if (start >= bit_count)
		return;

	resize(bit_count + num_positions);

	/* Move by byte if possible */
	if (num_positions % BITS_PER_TYPE == 0) {
		size_t num_bytes = num_positions / BITS_PER_TYPE;
		for (size_t i = cur_size - 1; i >= last_byte * BITS_PER_TYPE; i--)
			if((*this)[i])
				set_bit(i + num_positions);
			else
				clear_bit(i + num_positions);

		for (int i = last_byte - 1; i >= first_byte; i--)
			storage[i + num_bytes] = storage[i];

		for (size_t i = first_byte * BITS_PER_TYPE; i > start; i--)
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
	if (num_positions > BITS_PER_TYPE) {
		for (size_t i = start; i < first_byte * BITS_PER_TYPE; i++)
			clear_bit(i);
		for (size_t i = first_byte; i < last_byte; i++)
			storage[i] = 0;
		for (size_t i = last_byte * BITS_PER_TYPE; i < start + num_positions; i++)
			clear_bit(i);
	} else
		for (size_t i = start; i < start + num_positions; i++)
			clear_bit(i);
}


#endif /* BITVECTOR_HPP_ */
