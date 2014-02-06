/*
 * Vector.hpp
 *
 *  Created on: Feb 6, 2014
 *      Author: brain
 */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <stdlib.h>

class Vector {
	static const size_t DEFAULT_CAPACITY = 150;
	unsigned char *storage;
	size_t count;
	size_t capacity;

public:
	Vector():
		count(0), capacity(0), storage(NULL) {}
	Vector(size_t count, unsigned char value);
	~Vector();
	unsigned char &operator[](size_t index);
	const unsigned char &operator[](size_t index) const;
	size_t size() const { return this->count; }
	size_t reserved_size() const { return this->capacity; }
	void resize(size_t size);
	void push_back(unsigned char);
	void reserve(size_t size);
	void grow();
};

#endif /* VECTOR_HPP_ */