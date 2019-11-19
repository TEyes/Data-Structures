#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H

using namespace std;
template <class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild,
		* rightChild;
	binaryTreeNode() { leftChild = rightChild = nullptr; }
	binaryTreeNode(const T& theElement):element(theElement)
	{
		leftChild = rightChild = nullptr;
	}
	binaryTreeNode(const T& theElement,
		binaryTreeNode<T>* theLeftChild,
		binaryTreeNode<T>* theRightChild):element(theElement)
	{
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};
#endif