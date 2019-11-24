#pragma once
using namespace std;

template<class T>
class minPriorityQueue
{
public:
	virtual ~minPriorityQueue() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual const T& top() = 0;
	virtual void pop() = 0;
	virtual void push(const T& theElement) = 0;
};
