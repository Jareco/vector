#include <iostream>
#include <algorithm>
#include <stdexcept>
using namespace std;

template <typename T>
class Vector
{
public:
	class Constiterator;
	class Iterator;
	using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = T &;
	using const_reference = const T &;
	using pointer = T *;
	using const_pointer = const T *;
	using iterator = Iterator;
	using const_iterator = Constiterator;

private:
	size_t max_sz;
	size_t sz;
	static size_t constexpr min_sz = 5;
	value_type *values;

	// increasing of capacity
	void reserve(size_t new_len)
	{
		value_type *new_array = new value_type[new_len];
		for (size_t i{0}; i < sz; i++)
			new_array[i] = values[i];

		delete[] values;
		values = new_array;
		this->max_sz = new_len;
	}

public:
	Vector() : Vector(min_sz)
	{
	}

	Vector(size_t max_sz) : max_sz{max_sz}
	{
		if (max_sz < min_sz)
			max_sz = min_sz;

		sz = 0;
		values = new value_type[max_sz];
	}

	Vector(initializer_list<value_type> il)
	{
		values = il.size() > 0 ? new value_type[il.size()] : nullptr;
		max_sz = il.size();
		sz = 0;
		for (const auto &elem : il)
			values[sz++] = elem;
	}

	// Copy contructor
	Vector(const Vector &right)
	{
		size_t i = 0;
		values = new value_type[right.max_sz];
		for (i = 0; i < right.sz; i++)
		{
			this->values[i] = right.values[i];
		}
		sz = i;
		this->max_sz = right.max_sz;
	}

	Vector(Vector &&src)
	{
		values = src.values;
		sz = src.sz;
		max_sz = src.max_sz;
		src.values = nullptr;
		src.sz = src.max_sz = 0;
	}

	// Destructor
	~Vector()
	{
		delete[] values;
	}

	// returns the size of the vector
	size_t size() const
	{
		return sz;
	}

	// checks if the vector is empty
	bool empty()
	{
		return sz == 0;
	}

	void clear()
	{
		sz = 0;
	}

	// Adds one element to the end of vector
	void push_back(value_type value)
	{
		if (sz == max_sz)
			reserve(max_sz * 2 + 5);

		values[sz] = value;
		sz++;
	}

	// delete one lement
	void pop_back()
	{
		if (sz > 0)
			sz--;
	}

	T &operator[](size_t index)
	{
		return values[index];
	}

	const T &operator[](size_t index) const
	{
		return values[index];
	}

	// overloading of operator =
	Vector<value_type> &operator=(const Vector &src)
	{
		if (this == &src)
			return *this;
		delete[] this->values;
		size_t i = 0;
		this->values = new value_type[src.max_sz];
		for (i = 0; i < src.sz; i++)
		{
			this->values[i] = src.values[i];
		}
		this->sz = src.sz;
		this->max_sz = src.max_sz;
		return *this;
	}
	Vector &operator=(Vector &&rhs)
	{
		delete[] values;
		values = rhs.values;
		sz = rhs.sz;
		max_sz = rhs.max_sz;
		rhs.values = nullptr;
		rhs.sz = rhs.max_sz = 0;
	}

	class Iterator
	{
		T *ptr;
		Vector<T> *v;

	public:
		using value_type = Vector ::value_type;
		using difference_type = Vector::difference_type;
		using reference = Vector::reference;
		using pointer = Vector::pointer;
		using iterator_category = std::forward_iterator_tag;

		Iterator(T *new_iterator, Vector *new_vector)
		{
			this->ptr = new_iterator;
			this->v = new_vector;
		}

		const Iterator &operator++()
		{
			if (ptr >= ((*v).end()).ptr)
				throw runtime_error("Out of bounds");
			this->ptr = this->ptr + 1;
			return *this;
		}

		bool operator!=(const Iterator &src) const
		{
			return !(this->ptr == src.ptr);
		}

		T &operator*()
		{
			if (ptr >= ((*v).end()).ptr)
				throw runtime_error("Out of bounds");
			return *ptr;
		}

		const T &operator*() const
		{
			if (ptr >= ((*v).end()).ptr)
				throw runtime_error("Out of bounds");
			return *ptr;
		}

		bool operator==(const Iterator &src) const
		{
			return this->ptr == src.ptr;
		}

		Iterator operator++(int)
		{
			Iterator old{*this};
			++*this;
			return old;
		}

		const T *operator->()
		{
			return ptr;
		}

		operator Constiterator()
		{
			return Constiterator(ptr, v);
		}
	};

	class Constiterator
	{
		T *ptr;
		const Vector<T> *v;

	public:
		using value_type = Vector ::value_type;
		using difference_type = Vector::difference_type;
		using reference = Vector::reference;
		using pointer = Vector::pointer;
		using iterator_category = std::forward_iterator_tag;

		Constiterator(T *new_iterator, const Vector *new_vector)
		{
			this->ptr = new_iterator;
			this->v = new_vector;
		}

		Constiterator &operator++()
		{
			if (ptr >= ((*v).end()).ptr)
				throw runtime_error("Out of bounds");
			this->ptr = this->ptr + 1;
			// aufg1:	ptr - 1
			return *this;
		}

		bool operator!=(const Constiterator &src) const
		{
			return !(this->ptr == src.ptr);
		}

		const T &operator*() const
		{
			if (ptr >= ((*v).end()).ptr)
				throw runtime_error("Out of bounds");
			return *ptr;
		}

		const T &operator*()
		{
			if (ptr >= ((*v).end()).ptr)
				throw runtime_error("Out of bounds");
			return *ptr;
		}

		bool operator==(const Constiterator &src) const
		{
			return this->ptr == src.ptr;
		}

		Constiterator operator++(int)
		{
			Constiterator old{*this};
			++*this;
			return old;
		}

		const T *operator->()
		{
			return ptr;
		}

		friend difference_type operator-(const Vector::Constiterator &lop,
										 const Vector::Constiterator &rop)
		{
			return lop.ptr - rop.ptr;
		}
	};

	Iterator begin()
	{
		return Iterator(values, this);
	}

	Iterator end()
	{
		return Iterator(values + sz, this);
	}

	Constiterator begin() const
	{
		return Constiterator(values, this);
	}

	Constiterator end() const
	{
		return Constiterator(values + sz, this);
	}

	iterator erase(const_iterator pos)
	{
		auto diff = pos - begin();
		if (diff < 0 || static_cast<size_type>(diff) >= sz)
			throw runtime_error("Iterator out of bounds");
		size_type current{
			static_cast<size_type>(diff)};
		for (; current < sz - 1; ++current)
			values[current] = values[current + 1];
		--sz;
		return iterator{
			values + current, this};
	}

	iterator insert(const_iterator pos,
					Vector<T>::const_reference val)
	{
		auto diff = pos - begin();
		if (diff < 0 || static_cast<size_type>(diff) > sz)
			throw runtime_error("Iterator out of bounds");
		size_type current{
			static_cast<size_type>(diff)};
		if (sz >= max_sz)
			reserve(max_sz * 2 + 10);
		for (size_type i{sz}; i-- > current;)
			values[i + 1] = values[i];
		values[current] = val;
		++sz;
		return iterator{values + current, this};
	}

	ostream &print(ostream &o) const
	{
		o << "[";
		for (size_t i = 0; i < sz; i++)
			if (i == sz - 1)
			{
				o << values[i];
			}
			else
			{
				o << values[i] << ",";
			}
		o << "]";

		return o;
	}
};

template <typename T>
ostream &operator<<(ostream &o, const Vector<T> &t)
{
	return t.print(o);
}