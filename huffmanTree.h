#pragma once
#include<iostream>

#include"huffmanNode.h"
#include"minHeap.h"
#include"huffmanTree.h"
using namespace std;

template <class T>
linkedBinaryTree<int>* huffmanTree(T weight[], int n)
{//��������������Ϊ����������[1:n]�е�n��Ƶ��
	//����һ�鵥�ڵ���
	huffmanNode<T>* hNode = new huffmanNode<T>[n + 1];
	linkedBinaryTree<int> emptyTree;
	for (int i = 1; i <= n; i++)
	{
		hNode[i].weight = weight[i];
		hNode[i].tree = new linkedBinaryTree<T>;
		hNode[i].tree->makeTree(i, emptyTree, emptyTree);//iΪƵ�ʡ�
	}
	//ʹ��һ�鵥�ڵ�������С����
	minHeap<huffmanNode<T>> hHeap(1);
	hHeap.initialize(hNode, n);
	//��С������ȡ�����������ϲ�����push������ȥ��
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
