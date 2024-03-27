#pragma once
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

class KSetIterator;

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
	friend std::ostream& operator<<(std::ostream& os, const KSet<T>& rhs);
	size_t Size() const;
	void Clear();
	bool IsEmpty() const;
	bool IsFull() const;
	KSetIterator GetIterator();
	friend class KSetIterator;
};

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
	std::vector<int> q, w1(v), w2(rhs.v);
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
	std::vector<int> q, w1(v), w2(rhs.v);
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
	for (const auto& i : rhs.v) {
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

template<typename T>
KSetIterator KSet<T>::GetIterator() {
	return KSetIterator(this);
}