#pragma once
#include"linkedBinaryTree.h"

template <class T>
struct huffmanNode
{
	linkedBinaryTree<T>* tree;
	T weight;
	operator T()const { return weight; }
};