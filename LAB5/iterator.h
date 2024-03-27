#pragma once
#include "KSet.h"

template <typename T>
class Iterator {
protected:
public:
	virtual void forward() = 0;
	virtual void back() = 0;
	virtual T& get() const = 0;
	Iterator operator++();
	Iterator operator--();
	Iterator& operator++(int i);
	Iterator& operator--(int i);
	T& operator*();
	enum class Exception {
		OutOfRange
	};
};

template <typename T>
Iterator<T> Iterator<T>::operator--()
{
	Iterator<T> temp = *this;
	back();
	return temp;
}

template <typename T>
Iterator<T>& Iterator<T>::operator--(int i)
{
	back();
	return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++()
{
	Iterator<T> temp = *this;
	forward();
	return temp;
}

template <typename T>
Iterator<T>& Iterator<T>::operator++(int i)
{
	forward();
	return *this;
}

template <typename T>
T& Iterator<T>::operator*()
{
	return get();
}