/*
 * Vector.hpp
 *
 *  Created on: Feb 6, 2014
 *      Author: brain
 */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <stdlib.h>
#include <string.h>
#include <stdexcept>

template<typename T = unsigned char> class Vector {
	static const size_t DEFAULT_CAPACITY = 11;
	T *storage;

protected:
	size_t count;
	size_t capacity;
	void copy(const Vector &vec);

public:
	Vector():
		count(0), capacity(0), storage(NULL) {}
	Vector(size_t count, T value);
	Vector(const Vector &vec);
	~Vector();
	Vector &operator=(const Vector &);
	T &operator[](size_t index);
	const T &operator[](size_t index) const;
	size_t size() const { return this->count; }
	size_t reserved_size() const { return this->capacity; }
	void resize(size_t size);
	void push_back(T);
	void reserve(size_t size);
	void grow();
	void swap(Vector &);
	void clear() {	for (size_t i = 0; i < count; i++) storage[i] = 0; }
};


template<typename T> Vector<T>::Vector(size_t count, T value):
	count(count), capacity(count), storage(NULL)
{
	storage = static_cast<T *>(malloc(count * sizeof(T)));
	if (storage == NULL)
		throw std::bad_alloc();
	for (size_t i = 0; i < count; i++)
		storage[i] = value;
}

template<typename T> Vector<T>::Vector(const Vector &vec)
{
	void *new_container = malloc(vec.capacity * sizeof(T));
	if (new_container == NULL)
		throw std::bad_alloc();
	memcpy(new_container, vec.storage, vec.capacity * sizeof(T));
	storage = static_cast<T *>(new_container);
	capacity = vec.capacity;
	count = vec.count;
}

template<typename T> Vector<T> &Vector<T>::operator=(const Vector &vec)
{
	Vector tmp(vec);
	swap(tmp);
	return *this;
}

template<typename T> void Vector<T>::swap(Vector<T> &vec)
{
	std::swap(this->storage, vec.storage);
	std::swap(this->capacity, vec.capacity);
	std::swap(this->count, vec.count);
}


template<typename T> T &Vector<T>::operator[](size_t index)
{
	if (index >= count)
		throw std::out_of_range("");
	return storage[index];
}

template<typename T> const T &Vector<T>::operator[](size_t index) const
{
	if (index >= count)
		throw std::out_of_range("");
	return storage[index];
}

template<typename T> void Vector<T>::reserve(size_t size)
{
	T *new_storage;
	if (size <= capacity)
		return;

	if (storage != NULL)
		new_storage = static_cast<T *>(
				realloc(storage, size * sizeof(T)));
	else
		new_storage = static_cast<T *>(
				malloc( size * sizeof(T)));

	if (new_storage == NULL)
		throw std::bad_alloc();
	storage = new_storage;
	capacity = size;
}

template<typename T> void Vector<T>::grow()
{
	size_t new_capacity;

	if (capacity == 0)
		new_capacity = DEFAULT_CAPACITY;
	else
		new_capacity = capacity * 2;
	reserve(new_capacity);
}

template<typename T> void Vector<T>::push_back(T what)
{
	if (capacity == count)
		grow();
	storage[count++] = what;
}

template<typename T> void Vector<T>::resize(size_t size)
{
	/* only increasing count */
	size_t old_size = count;
	if (size <= count)
		return;
	if (size > capacity)
		reserve(size);
	for (size_t i = old_size; i < size; i++)
		storage[i] = 0;
	count = size;
}

template<typename T> Vector<T>::~Vector()
{
	free(storage);
}

#endif /* VECTOR_HPP_ */
