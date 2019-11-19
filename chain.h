#include"linearList.h"
#include"myExceptions.h"

#include<iostream>
using namespace std;
template<class T>
struct chainNode
{
	T element;
	chainNode<T>* next;
	chainNode() {};
	chainNode(const T& element)
	{
		this->element = element;
	}
	chainNode(const T& element, chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};


template<class T>
class chain :public linearList<T>
{
public:
	chain(int initialCapacity = 10);
	chain(const chain<T>& theChain);
	~chain();

	bool empty() const { return listSize == 0; }
	int size()const { return listSize; }
	T& get(int theIndex)const;
	int indexOf(const T& theELement) const;
	void erase(int theIndex);
	void insert(int theIndex,const T& theElement);
	void output(ostream& out)const;

	friend ostream& operator<<(ostream& out, const chain<T>& x);
	class iterator
	{
	public:
		// typedefs required by C++ for a forward iterator
		typedef forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		// constructor
		iterator(chainNode<T>* theNode = NULL)
		{
			node = theNode;
		}

		// dereferencing operators
		T& operator*() const { return node->element; }
		T* operator->() const { return &node->element; }

		// increment
		iterator& operator++()   // preincrement
		{
			node = node->next; return *this;
		}
		iterator operator++(int) // postincrement
		{
			iterator old = *this;
			node = node->next;
			return old;
		}

		// equality testing
		bool operator!=(const iterator right) const
		{
			return node != right.node;
		}
		bool operator==(const iterator right) const
		{
			return node == right.node;
		}
	protected:
		chainNode<T>* node;
	};  // end of iterator class

protected:
	void checkIndex(int theIndex) const;
	int listSize;
	chainNode<T>* firstNode;
};

template<class T>
 chain<T>::chain(int initialCapacity)
{
	 if (initialCapacity < 1)
	 {
		 ostringstream s;
		 s << "initialCapacity = " << initialCapacity << " must be > 0";
			 throw illegalParameterValue(s.str());
	 }
	 firstNode = NULL;
	 listSize = 0;
}

template<class T>
 chain<T>::chain(const chain<T>& theChain)
{
	 listSize = theChain.listSize;
	 if (listSize == 0)
	 {
		 firstNode = NULL;
		 return;
	 }
	 chainNode<T>* sourceNode = theChain.firstNode;
	 firstNode = new chainNode<T>(sourceNode->element);
	 chainNode<T>* targetNode = firstNode;
	 sourceNode = sourceNode->next;
	 while (sourceNode->next != NULL)
	 {
		 targetNode->next = new chainNode<T>(sourceNode->element);
		 targetNode = targetNode->next;
		 sourceNode = sourceNode->next;
	 }
	 targetNode->next = NULL;
}

template<class T>
 chain<T>::~chain()
{
	 while (firstNode!= NULL)
	 {
		 chainNode<T>* nextNode = firstNode->next;
		 delete firstNode;
		 firstNode = nextNode;
	 }
}

template<class T>
 T& chain<T>::get(int theIndex) const
{
	 checkIndex(theIndex);
	 chainNode<T>* currentNode = firstNode;
	 for (int i = 0; i < theIndex; i++)
	 {
		 currentNode = currentNode->next;
	 }
	 return currentNode->element;
}

template<class T>
int chain<T>::indexOf(const T& theELement) const
{
	int theIndex = 0;
	chainNode<T>* currentNode = firstNode;
	while (currentNode != NULL &&
		currentNode->element != theELement)
	{
		currentNode = currentNode->next;
		theIndex++;
	}
	if (currentNode == NULL)
		return -1;
	else return theIndex;
}

template<class T>
 void chain<T>::erase(int theIndex)
{
	 checkIndex(theIndex);
	 chainNode<T>* deleteNode = firstNode;
	 if (theIndex == 0)
	 {
		 deleteNode = firstNode;
		 firstNode = firstNode->next;
	 }
	 else
	 {
		 chainNode<T>* p = firstNode;
		 for (int i = 0; i < theIndex - 1; i++)
		 {
			 p = p->next;
		 }
		 deleteNode = p->next;
		 p->next = p->next->next;
	 }
	 listSize--;
	 delete deleteNode;
}

template<class T>
 void chain<T>::insert(int theIndex, const T& theElement)
{
	 if (theIndex<0 || theIndex>listSize)
	 {
		 ostringstream s;
		 s << "theIndex = " << theIndex << " size = " << listSize;
		 throw illegalIndex(s.str());
	 }

	 if (theIndex == 0)
	 {
		firstNode = new chainNode<T>(theElement, firstNode);
	 }
	 else
	 {
		 chainNode<T>* p = firstNode;
		 for (int i = 0; i < theIndex - 1; i++)
		 {
			 p = p->next;
		 }
		 p->next = new chainNode<T>(theElement, p->next);	 
	 }
	 listSize++;
}

template<class T>
 void chain<T>::output(ostream& out) const
{
	 for (chainNode<T>* currentNode = firstNode;
		 currentNode != NULL; currentNode = currentNode->next)
	 {
		 out << currentNode->element << " ";
	 }
}

template<class T>
 void chain<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		ostringstream s;
		s << "theIndex = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template<class T>
ostream& operator<<(ostream& out, const chain<T>& x)
{
	x.output(out); return out;
}