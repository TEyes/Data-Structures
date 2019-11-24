#pragma once

#include"maxPriorityQueue.h"
#include"myExceptions.h"
#include"changeLength1D.h"

#include<sstream>
#include<algorithm>
#include<iterator>

using namespace std;
template<class T>
class maxHeap :public maxPriorityQueue<T>
{
public:
	maxHeap(int initialCapacity = 10);
	~maxHeap() { delete[] heap; }
	bool empty() const { return heapSize == 0; }
	int size()const { return heapSize; }
	const T& top()
	{
		if (heapSize == 0)
			throw queueEmpty();
		return heap[1];
	}
	void pop();
	void push(const T& theElement);
	void initialize(T*, int);
	void deactivateArray()
	{
		heap = NULL; arrayLength = heapSize = 0;
	}
	void output(ostream& out) const;
private:
	int heapSize;
	int arrayLength;
	T* heap;
};

template<class T>
 maxHeap<T>::maxHeap(int initialCapacity)
{
	 if (initialCapacity < 1)
	 {
		 ostringstream s;
		 s << "Initial capacity = " << initialCapacity << " Must be > 0";
		 throw illegalParameterValue(s.str());
	 }
	 arrayLength = initialCapacity+1;//用数组作为存储满二叉树，数组第一个元素为空，所以数组长度为元素容量加1
	 heap = new T[arrayLength];
	 heapSize = 0;
}

 template<class T>
 void maxHeap<T>::pop()
 {
	 if (heapSize == 0)
		 throw queueEmpty();
	 heap[1].~T();

	 T lastElement = heap[heapSize--];
	 int currentNode = 1,
		 child = 2;
	 while (child <= heapSize)
	 {
		 if (child < heapSize && heap[child] < heap[child + 1])
			 child++;
		 if (lastElement >= heap[child])
			 break;
		 heap[currentNode] = heap[child];
		 currentNode = child;
		 child *= 2;
	 }
	 heap[currentNode] = lastElement;
 }

 template<class T>
 void maxHeap<T>::push(const T& theElement)
 {
	 if (heapSize == arrayLength - 1)
	 {
		 changeLength1D(heap, arrayLength, arrayLength * 2);
		 arrayLength *= 2;
	 }
	 int currentNode = ++heapSize;
	 while (currentNode != 1 && heap[currentNode / 2] < theElement)
	 {
		 heap[currentNode] = heap[currentNode / 2];
		 currentNode /= 2;
	 }
	 heap[currentNode] = theElement;
 }

 template<class T>
 void maxHeap<T>::initialize(T* theHeap, int theSize)
 {
	 delete[] heap;
	 heap = theHeap;
	 heapSize = theSize;
	 for (int root = heapSize / 2; root >= 1; root--)
	 {
		 T rootElement = heap[root];
		 int child = root * 2;
		 while (child <= heapSize)
		 {
			 if (child < heapSize && heap[child] < heap[child + 1])
				 child++;
			 if (rootElement >= heap[child])
				 break;
			 heap[child / 2] = heap[child];
			 child *= 2;
		 }
		 heap[child / 2] = rootElement;
	 }
 }

 template<class T>
 void maxHeap<T>::output(ostream& out) const
 {
	 copy(heap + 1, heap + heapSize + 1, ostream_iterator<T>(cout, " "));
 }

 template<class T>
 ostream& operator<<(ostream& out, const maxHeap<T>& x)
 {
	 x.output(out); return out;
 }

