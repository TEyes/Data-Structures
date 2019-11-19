#pragma once
#include<iostream>
#include"linearList.h"
#include"myExceptions.h"


template<class T>
struct DchainNode
{
	T element;
	DchainNode<T>* next;
	DchainNode<T>* previous;
	DchainNode(const T& element)
	{
		this->element = element;
		next = previous = NULL;
	}
	DchainNode(const T& element, DchainNode<T>* previous, DchainNode<T>* next)
	{
		this->element = element;
		this->previous = previous;
		this->next = next;
	}
};
template <class T>
class doublyLinkedList :public linearList<T>
{
protected:
	 void checkIndex(int theIndex) const;
	int listSize;
	DchainNode<T>* headerNode;
public:
	doublyLinkedList(int initialCapacity = 10);
	doublyLinkedList(const doublyLinkedList<T>&);
	~doublyLinkedList();
	bool empty() const { return listSize == 0; };
	int size() const { return listSize; };
	T& get(int index) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out)const;

	friend ostream& operator<<(ostream& out, const doublyLinkedList<T> theList);
};

template<class T>
void doublyLinkedList<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		ostringstream s;
		s << "theIndex = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template<class T>
 doublyLinkedList<T>::doublyLinkedList(int initialCapacity)
{
	 if (initialCapacity < 1)
	 {
		 ostringstream s;
		 s << "initialCapacity = " << initialCapacity << " must be > 0";
		 throw illegalParameterValue(s.str());
	 }
	 headerNode = NULL;
	 listSize = 0;
}

template<class T>
 doublyLinkedList<T>::doublyLinkedList(const doublyLinkedList<T>& theList)
{
	 if (theList.listSize == 0)
	 {
		 listSize = 0;
		 headerNode = NULL;
	 }
	 else
	 {
		 DchainNode<T>* sourceNode = theList.headerNode;
		 headerNode = new DchainNode<T>(sourceNode->element);
		 headerNode->previous = headerNode;
		 headerNode->next = headerNode;
		 DchainNode<T>* targetNode = headerNode;
		 sourceNode = sourceNode->next;
		 for (; sourceNode != theList.headerNode;
			 sourceNode = sourceNode->next
			 )
		 {
			 targetNode->next = new DchainNode<T>(sourceNode->element, targetNode, headerNode);
		 }
		 listSize = theList.listSize;
	 }
}

template<class T>
 doublyLinkedList<T>::~doublyLinkedList()
{
	 while (listSize!=0)
	 {
		 DchainNode<T>* p = headerNode->next;
		 delete headerNode;
		 headerNode = p;
		 listSize--;
	 }
}

template<class T>
 T& doublyLinkedList<T>::get(int index) const
{
	 checkIndex(index);
	 DchainNode<T>* currentNode;
	 if (index <= listSize / 2)
	 {
		 currentNode= headerNode->next;
		 for (int i = 0; i < index; i++)
		 {
			 currentNode = currentNode->next;
		 }
	 }
	 else
	 {
		 currentNode = headerNode->previous;
		 for (int i = 0; i < listSize - index; i++)
		 {
			 currentNode = currentNode->previous;
		 }
	 }
	 return currentNode->element;
}

template<class T>
 int doublyLinkedList<T>::indexOf(const T& theElement) const
{
	 int i = 0;
	 headerNode->element = theElement;
	 DchainNode<T>* currentNode;
	 for (currentNode = headerNode->next;
		 currentNode->element != theElement;
		 currentNode=currentNode->next
		 )//到了最后一个节点直接跳出
	 {
		 i++;
	 }
	 if (currentNode == headerNode)
	 {
		 return -1;
	 }
	 else
	 {
		 return i;
	 }
}

template<class T>
 void doublyLinkedList<T>::erase(int theIndex)
{
	 checkIndex(theIndex);
	 DchainNode<T>* p = headerNode->next;
	 for (int i = 0; i < theIndex - 1; i++)
	 {
		 p = p->next;
	 }
	 DchainNode<T>* deleteNode = p->next;
	 p->next = deleteNode->next;
	 deleteNode->next->previous = p;
	 delete deleteNode;
	 listSize--;
}

template<class T>
 void doublyLinkedList<T>::insert(int theIndex, const T& theElement)
{
	 if (theIndex<0 || theIndex>listSize)
	 {
		 ostringstream s;
		 s << "the Index = " << theIndex << " list size =" << listSize;
		 throw illegalIndex(s.str());
	 }
	 if (theIndex == 0)
	 {
		 if (headerNode == NULL)
		 {//表为空时候的插入。
			 headerNode = new DchainNode<T>(theElement, NULL, NULL);//头节点
			 headerNode->next = new DchainNode<T>(theElement,headerNode,headerNode);//第一个元素
			 headerNode->previous = headerNode->next;//头节点的前驱节点。
		 }
		 else
		 {//非空时插入第零个位置。
			 DchainNode<T>* lastNode = headerNode->previous;
			 headerNode->next = new DchainNode<T>(theElement, headerNode, headerNode->next);
			 lastNode->next = headerNode;
		 }
	 }
	 else if (theIndex <= listSize / 2)
	 {
		 DchainNode<T>* p = headerNode->next;//第零个节点
		 for (int i = 0; i < theIndex - 1; i++)
		 {
			 p = p->next;
		 }
		 DchainNode<T>* PnextNode = p->next;
		 p->next = new DchainNode<T>(theElement, p,PnextNode);
		 PnextNode->previous = p->next;
	 }
	 else
	 {
		 DchainNode<T>* p = headerNode->previous;//最后一个节点
		 for (int i = 0; i <listSize-theIndex+1; i++)
		 {
			 p = p->previous;
		 }
		 DchainNode<T>* PnextNode = p->next;
		 p->next = new DchainNode<T>(theElement, p, PnextNode);
		 PnextNode->previous = p->next;
	 }
	 listSize++;
}

template<class T>
 void doublyLinkedList<T>::output(ostream& out) const
{
	 for (DchainNode<T>* currentNode = headerNode->next;
		 currentNode != headerNode;
		 currentNode = currentNode->next)
	 {
		 out << currentNode->element << " ";
	 }
}

 template<class T>
 ostream& operator<<(ostream& out, const doublyLinkedList<T> theList)
 {
	 theList.output(out);
	 return out;
 }

