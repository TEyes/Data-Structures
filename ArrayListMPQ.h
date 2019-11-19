#pragma once
#include "MaxPriorityQueue.h"
#include<sstream>
template <class T>
class ArrayListMPQ :
	public MaxPriorityQueue<T>
{
public:
	ArrayListMPQ(int initialCapacity = 10);
	ArrayListMPQ(const ArrayListMPQ<T>&);
	~ArrayListMPQ();

	bool empty() const;
	int size() const;
	const T& top();
	void push(const T& theElement);
	void pop();

};

template<class T>
 ArrayListMPQ<T>::ArrayListMPQ(int initialCapacity)
{
	 if (initialCapacity < 1)
	 {
		 ostringstream s;
		 s << "Initial capacity =" << initialCapacity << " Must be > 0";
		 
	 }
}

template<class T>
 ArrayListMPQ<T>::ArrayListMPQ(const ArrayListMPQ<T>&)
{
}

template<class T>
 ArrayListMPQ<T>::~ArrayListMPQ()
{
}

template<class T>
 bool ArrayListMPQ<T>::empty() const
{
	return false;
}

template<class T>
 int ArrayListMPQ<T>::size() const
{
	return 0;
}

template<class T>
 const T& ArrayListMPQ<T>::top()
{
	// TODO: 在此处插入 return 语句
}

template<class T>
 void ArrayListMPQ<T>::push(const T& theElement)
{
}

template<class T>
 void ArrayListMPQ<T>::pop()
{
}
