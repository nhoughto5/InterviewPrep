#pragma once
using namespace std;

template <class T>
class ring
{
public:
	//Nested class
	class iterator;

public:
	ring(int size) : m_pos(0), m_size(size), m_values(NULL) {
		m_values = new T[size];
	}

	~ring() {
		delete[] m_values;
	}

	int size() {
		return m_size;
	}

	//void add(T value) {
	//	m_values[m_pos % m_size] = value;
	//	++m_pos;
	//}

	void add(T value) {
		m_values[m_pos++] = value;

		if (m_pos == m_size) {
			m_pos = 0;
		}
	}

	T & get(int i) {
		return m_values[i];
	}

	iterator begin() {
		return iterator(0, *this);
	}

	iterator end() {
		return iterator(m_size, *this);
	}

	
private:
	int m_size, m_pos;
	T* m_values;
};

template <class T>
class ring<T>::iterator {
public:
	iterator(int pos, ring &aRing): m_pos(pos), m_ring(aRing) {

	}

	void print() {
		cout << "Hello from iterator\n";
	}

	//Postfix
	iterator &operator++(int) {
		++m_pos;
		return *this;
	}

	//Prefix
	iterator &operator++() {
		++m_pos;
		return *this;
	}

	T &operator*() {
		return m_ring.get(m_pos);
	}

	bool operator!=(const iterator &other) const{
		return m_pos != other.m_pos;
	}
private:
	int m_pos;
	ring &m_ring;
};