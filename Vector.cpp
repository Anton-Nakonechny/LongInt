#include <stdexcept>
#include "Vector.hpp"

Vector::Vector(size_t count, unsigned char value):
	count(count), capacity(count), storage(NULL)
{
	storage = static_cast<unsigned char *>(malloc(count * sizeof(unsigned char)));
	if (storage == NULL)
		throw std::bad_alloc();
	for (size_t i = 0; i < count; i++)
		storage[i] = value;
}

unsigned char &Vector::operator[](size_t index)
{
	if (index >= count)
		throw std::out_of_range("");
	return storage[index];
}

const unsigned char &Vector::operator[](size_t index) const
{
	if (index >= count)
		throw std::out_of_range("");
	return storage[index];
}

void Vector::reserve(size_t size)
{
	unsigned char *new_storage;
	if (size <= capacity)
		return;

	if (storage != NULL)
		new_storage = static_cast<unsigned char *>(
				realloc(storage, size * sizeof(unsigned char)));
	else
		new_storage = static_cast<unsigned char *>(
				malloc( size * sizeof(unsigned char)));

	if (new_storage == NULL)
		throw std::bad_alloc();
	storage = new_storage;
	capacity = size;
}

void Vector::grow()
{
	size_t new_capacity;

	if (capacity == 0)
		new_capacity = DEFAULT_CAPACITY;
	else
		new_capacity = capacity * 2;
	reserve(new_capacity);
}

void Vector::push_back(unsigned char what)
{
	if (capacity == count)
		grow();
	storage[count++] = what;
}

void Vector::resize(size_t size)
{
	//only increasing count
	size_t old_size = count;
	if (size <= count)
		return;
	if (size > capacity)
		reserve(size);
	for (size_t i = old_size; i < size; i++)
		storage[i] = 0;
	count = size;
}

Vector::~Vector()
{
	free(storage);
}
