#pragma once
#include "MaxPriorityQueue.h"
#include "linkedBinaryTree.h"
#include "binaryTreeNode.h"
#include "myExceptions.h"
#include <sstream>

using namespace std;

template <class T>
class maxHblt:public maxPriorityQueue<T>,
				public linkedBinaryTree<pair<int,T>>
{
public:
	bool empty()const { return this->treeSize == 0; }
	int size() const { return this->treeSize; }
	const T& top () //ûд�������º��溯���������⣬�����λҲ��֪����ô���ġ�
	{
		if (this->treeSize == 0)
		throw queueEmpty();
		return this->root->element.second;//��elementΪ pair ��pair�ĵڶ���Ԫ��
	}
	void pop();
	void push(const T&);
	void initialize(T*, int);
	void meld(maxHblt<T>& theHblt)
	{
		meld(this->root, theHblt.root);
		this->treeSize += theHblt.treeSize;
		theHblt.root = NULL;
		theHblt.treeSize = 0;
	}
	void output() {  linkedBinaryTree<pair<int, T>>:: postOrder(hbltOutput); cout << endl; }
	void hbltInOutput() { linkedBinaryTree<pair<int, T>>::inOrder(hbltOutput); cout << endl; }
private:
	void meld(binaryTreeNode<pair<int, T>>*&,
		binaryTreeNode<pair<int, T>>*&);
	 static void hbltOutput(binaryTreeNode<pair<int, T>> *t)
	{
		cout << t->element.second << ' ';
	}
};
template <class T>
void maxHblt<T>::meld(binaryTreeNode<pair<int, T>> *&x,
	binaryTreeNode<pair<int, T>> *&y)
{
	if (y == NULL)
		return;
	if (x == NULL)
	{
		x = y;
		return;
	}
	if (x->element.second < y->element.second)
	{
		swap(x, y);
	}
	meld(x->rightChild, y);
	if (x->leftChild == NULL)
	{
		x->leftChild = x->rightChild;
		x->rightChild = NULL;
		x->element.first = 1;
	}
	else
	{
		if (x->leftChild->element.first < x->rightChild->element.first)
			swap(x->leftChild, x->rightChild);

		x->element.first = x->rightChild->element.first + 1;
		
	}
}

template <class T>
void maxHblt<T>::push(const T& theElement)
{
	binaryTreeNode<pair<int, T>>* q = new binaryTreeNode<pair<int, T>>(pair<int,T>(1, theElement));
	meld(this->root, q);
	this->treeSize++;
}

template <class T>
void maxHblt<T>::pop()
{
	if (this->root == NULL)
		throw queueEmpty();
	binaryTreeNode<pair<int, T>>* left = this->root->leftChild,
		* right = this->root->rightChild;
	delete this->root;//��дroot ����root��delete֮�󣬻���ʹ�ã�
	//����δ�����κη��Ŵ��󣨻���˵��һ���ϵ㣩
	this->root = left;
	meld(this->root, right);
	this->treeSize--;
}

template <class T>
void maxHblt<T>::initialize(T* theElement, int theSize)
{
	arrayQueue<binaryTreeNode<pair<int, T>>*> q(theSize);
	linkedBinaryTree<pair<int, T>>:: erase();
	for (int i = 1; i <= theSize; i++)
	{
		q.push(new  binaryTreeNode<pair<int,T>> (pair<int, T>(1, theElement[i])));
	}
	for (int i = 1; i <= theSize - 1; i++)
	{
		binaryTreeNode<pair<int, T>> *b = q.front();
		q.pop(); //���������
		binaryTreeNode<pair<int, T>>* c = q.front();
		q.pop();//���������
		meld(b, c);
		q.push(b);
	}
	if (theSize > 0)
		this->root = q.front();
	this->treeSize = theSize;
}