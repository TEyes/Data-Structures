#pragma once
#include<iostream>
#include<sstream>
using namespace std;

#include"maxPriorityQueue.h"
#include"arrayQueue.h"
#include"linkedBinaryTree.h"
#include"myExceptions.h"
#include"binaryTreeNode.h"



template<class T>
class maxWblt :public arrayQueue<T>,
	public linkedBinaryTree<pair<int, T>>
{
public:
	bool empty()const { return maxWblt<T>::treeSize == 0; }
	void pop();
	void push(const T& theElement);
	int size()const { return maxWblt<T>::treeSize; }
	const T& top()
	{
		if (maxWblt<T>::treeSize == 0)
			throw queueEmpty();
		return maxWblt<T>::root->element.second;
	}
	void initialize(T*, int);
	void meld(maxWblt<T>& theMaxWblt)
	{
		meld(maxWblt<T>::root, theMaxWblt.root);
		maxWblt<T>::treeSize += theMaxWblt.treeSize;
		theMaxWblt.root = NULL;
		theMaxWblt.treeSize = 0;

	}
	void output() { linkedBinaryTree<pair<int, T>>::postOrder(wbltPostOrder); cout << endl; }
private:
	void meld(binaryTreeNode<pair<int, T>>*& left,
		binaryTreeNode<pair<int, T>>*& right);
	static void wbltPostOrder()
	{
		cout << maxWblt<T>::root->element.second;
	}
};

template<class T>
void maxWblt<T>:: meld (binaryTreeNode<pair<int,T>>* &left,
	binaryTreeNode<pair<int,T>>* &right)
{
	if (right == NULL)
		return;
	if (left == NULL)
	{
		left = right;
		return;
	}
	if (left->element.second < right->element.second)
	{
		swap(left, right);
	}
	meld(left->rightChild, right);
	if (left->leftChild == NULL)
	{
		left->leftChild = left->rightChild;
		left->rightChild = NULL;
		left->element.first = left->leftChild->element.first+1;
	}
	else
	{
		if (left->leftChild->element.first < left->rightChild->element.first)
			swap(left->leftChild, left->rightChild);
		left->element.first = left->leftChild->element.first+
			left->rightChild->element.first+ 1;
	}
}

template<class T>
 void maxWblt<T>::pop()
{
	 if (maxWblt<T>::treeSize == 0)
		 throw queueEmpty();
	 binaryTreeNode<pair<int, T>>* left = maxWblt<T>::root->leftChild,
		 * right = maxWblt<T>::root->rightChild;
	 delete maxWblt<T>::root;
	 maxWblt<T>::root = left;
	 meld(maxWblt<T>::root, right);
	 maxWblt<T>::treeSize--;
}

 template<class T>
  void maxWblt<T>::push(const T& theElement)
 {
	  binaryTreeNode<pair<int, T>>* q = new binaryTreeNode<pair<int, T>>(pair<int, T>(1, theElement));
	  meld(maxWblt<T>::root->rightChild, q);
	  maxWblt<T>::treeSize++;
 }

  template<class T>
   void maxWblt<T>::initialize(T* theElement, int theSize)
  {
	   arrayQueue<binaryTreeNode<pair<int, T>>*> q(theSize);
	   maxWblt<T>::erase();
	   for (int i = 1; i <= theSize; i++)
	   {
		   q.push(new binaryTreeNode<pair<int, T>>(pair<int, T>(1, theElement[i])));
	   }
	   for (int i = 1; i <= theSize - 1; i++)
	   {
		   binaryTreeNode<pair<int, T>>* b = q.front();
		   q.pop();
		   binaryTreeNode<pair<int, T>>* c = q.front();
		   q.pop();
		   meld(b, c);
		   q.push(b);
	   }
	   if (theSize >0)
		   maxWblt<T>::treeSize = theSize;
	   maxWblt<T>::root = q.front();
  }
