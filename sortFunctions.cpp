#include<iostream>

#include"maxHeap.h"
#include"minHeap.h"
template <class T>
void heapSortMax(T a[], int n)
{
	maxHeap<T> heap(1);
	heap.initialize(a, n);
	for (int i = n - 1; i >= 1; i--)
	{
		T x = heap.top();
		heap.pop();
		a[i + 1] = x;
	}
	heap.deactivateArray();
}
template <class T>
void heapSortMin(T a[], int n)
{
	minHeap<T> heap(1);
	heap.initialize(a, n);
	for (int i = n - 1; i >= 1; i--)
	{
		T x = heap.top();
		heap.pop();
		a[i + 1] = x;
	}
	heap.deactivateArray();
}