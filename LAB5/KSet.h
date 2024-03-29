#pragma once
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

template <typename T>
class KSet;

template <typename T>
class KSetIterator {
protected:
	KSet<T>* set;
	size_t index = 0;
	KSetIterator();
	KSetIterator(KSet<T>* set, size_t index);
public:
	KSetIterator(KSet<T>* set);
	void forward();
	void back();
	T& get() const;
	KSetIterator operator++();
	KSetIterator operator--();
	KSetIterator& operator++(int i);
	KSetIterator& operator--(int i);
	T& operator*();
	bool operator==(const KSetIterator& other) const;
	template <typename U>
	friend class KSet;
};

template <typename T>
class KSet {
private:
	std::vector<T> v;
public:
	KSet(const std::vector<T>& v);
	KSet();
	~KSet();
	KSet<T>& operator=(const KSet<T>& rhs);
	KSet<T> operator|(const KSet<T>& rhs) const;
	KSet<T>& operator|=(const KSet<T>& rhs);
	KSet<T> operator&(const KSet<T>& rhs) const;
	KSet<T>& operator&=(const KSet<T>& rhs);
	KSet<T> operator/(const KSet<T>& rhs) const;
	KSet<T>& operator/=(const KSet<T>& rhs);
	KSet<T>& operator>>(const T& rhs);
	template <typename Q>
	friend std::ostream& operator<<(std::ostream& os, const KSet<Q>& rhs);
	size_t Size() const;
	void Clear();
	bool IsEmpty() const;
	bool IsFull() const;
	KSetIterator<T> begin();
	KSetIterator<T> end();
	template <typename U>
	friend class KSetIterator;
};

template <typename T>
KSetIterator<T> KSet<T>::begin()
{
	return KSetIterator(this, 0);
}

template <typename T>
KSetIterator<T> KSet<T>::end()
{
	return KSetIterator(this, v.size() - 1);
}

template <typename T>
KSet<T>::KSet()
{
}

template <typename T>
KSet<T>::~KSet()
{
}

template <typename T>
KSet<T>::KSet(const std::vector<T>& v) : v(v) {

}

template <typename T>
KSet<T>& KSet<T>::operator=(const KSet<T>& rhs)
{
	if (this != &rhs) {
		v = rhs.v;
	}
	return *this;
}

template <typename T>
KSet<T> KSet<T>::operator|(const KSet<T>& rhs) const
{
	std::set<T> s(v.begin(), v.end());
	for (const auto& i : rhs.v) {
		s.insert(i);
	}
	std::vector<T> q(s.begin(), s.end());
	return KSet(q);
}

template <typename T>
KSet<T>& KSet<T>::operator|=(const KSet<T>& rhs)
{
	*this = *this | rhs;
	return *this;
}

template <typename T>
KSet<T> KSet<T>::operator&(const KSet<T>& rhs) const
{
	std::vector<T> q, w1(v), w2(rhs.v);
	std::sort(w1.begin(), w1.end());
	std::sort(w2.begin(), w2.end());
	for (auto i = w1.begin(), j = w2.begin(); i != w1.end() && j != w2.end();) {
		if (*i != *j) {
			*i < *j ? i++ : j++;
			continue;
		}
		q.push_back(*i);
		i++;
		j++;
	}
	return KSet(q);
}

template<typename T>
KSet<T>& KSet<T>::operator&=(const KSet<T>& rhs)
{
	*this = *this & rhs;
	return *this;
}

template<typename T>
KSet<T> KSet<T>::operator/(const KSet<T>& rhs) const
{
	std::vector<T> q, w1(v), w2(rhs.v);
	std::sort(w1.begin(), w1.end());
	std::sort(w2.begin(), w2.end());
	for (auto i = w1.begin(), j = w2.begin(); i != w1.end() && j != w2.end();) {
		if (*i == *j) {
			*i < *j ? i++ : j++;
			continue;
		}
		q.push_back(*i);
		i++;
		j++;
	}
	return KSet(q);
}

template<typename T>
KSet<T>& KSet<T>::operator/=(const KSet<T>& rhs)
{
	*this = *this / rhs;
	return *this;
}

template <typename T>
KSet<T>& KSet<T>::operator>>(const T& rhs)
{
	v.push_back(rhs);
	return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const KSet<T>& rhs)
{
	for (const T& i : rhs.v) {
		os << i << " ";
	}
	return os;
}

template<typename T>
size_t KSet<T>::Size() const {
	return v.size();
}

template<typename T>
void KSet<T>::Clear() {
	v.clear();
}

template<typename T>
bool KSet<T>::IsEmpty() const {
	return v.empty();
}

template<typename T>
bool KSet<T>::IsFull() const {
	return false;
}

template <typename T>
bool KSetIterator<T>::operator==(const KSetIterator& other) const
{
	return index == other.index && set == other.set;
}

template <typename T>
KSetIterator<T>::KSetIterator()
{
}

template <typename T>
KSetIterator<T>::KSetIterator(KSet<T>* set) : set(set)
{
}

template <typename T>
KSetIterator<T>::KSetIterator(KSet<T>* set, size_t index) : set(set), index(index)
{
}

template <typename T>
T& KSetIterator<T>::get() const
{
	return set->v[index];
}

template <typename T>
void KSetIterator<T>::forward()
{
	index++;
}

template <typename T>
void KSetIterator<T>::back()
{
	index--;
}

template <typename T>
KSetIterator<T> KSetIterator<T>::operator--()
{
	KSetIterator<T> temp = *this;
	back();
	return temp;
}

template <typename T>
KSetIterator<T>& KSetIterator<T>::operator--(int i)
{
	back();
	return *this;
}

template <typename T>
KSetIterator<T> KSetIterator<T>::operator++()
{
	KSetIterator<T> temp = *this;
	forward();
	return temp;
}

template <typename T>
KSetIterator<T>& KSetIterator<T>::operator++(int i)
{
	forward();
	return *this;
}

template <typename T>
T& KSetIterator<T>::operator*()
{
	return get();
}