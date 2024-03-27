#pragma once
#include "iterator.h"
#include "KSet.h"

template <typename T>
class KSetIterator : public Iterator<T> {
protected:
	KSet<T>* set;
	size_t index = 0;
public:
	KSetIterator(KSet<T>* set);
	virtual void forward();
	virtual void back();
	virtual T& get() const;
};

