#pragma once
#include<iostream>

#include"huffmanNode.h"
#include"minHeap.h"
#include"huffmanTree.h"
using namespace std;

template <class T>
linkedBinaryTree<int>* huffmanTree(T weight[], int n)
{//哈夫曼树的输入为储存在数组[1:n]中的n个频率
	//创建一组单节点树
	huffmanNode<T>* hNode = new huffmanNode<T>[n + 1];
	linkedBinaryTree<int> emptyTree;
	for (int i = 1; i <= n; i++)
	{
		hNode[i].weight = weight[i];
		hNode[i].tree = new linkedBinaryTree<T>;
		hNode[i].tree->makeTree(i, emptyTree, emptyTree);//i为频率。
	}
	//使用一组单节点树构成小根堆
	minHeap<huffmanNode<T>> hHeap(1);
	hHeap.initialize(hNode, n);
	//从小根堆中取出两课树，合并后在push到堆中去。
	huffmanNode<T> w, x, y;
	linkedBinaryTree<int>* z;
	for (int i = 1; i < n; i++)
	{
		x = hHeap.top(); hHeap.pop();
		y = hHeap.top(); hHeap.pop();
		z = new linkedBinaryTree<int>;
		z->makeTree(0, *x.tree, *y.tree);
		w.weight = x.weight + y.weight;
		w.tree = z;
		hHeap.push(w);
		delete x.tree;
		delete y.tree;
	}
	return hHeap.top().tree;
}
