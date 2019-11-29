#include<iostream>

#include"huffmanTree.h"

int p[] = { 0,2,4,5,7,9,10,14,17,18,50 };
template <typename T>
void visit( binaryTreeNode<T>* node)
{
		if (node->element != 0)
		{
			cout << p[node->element] << " ";
		}
		else
			cout << 0 << " ";
}

template <typename T>
void ShowTree( linkedBinaryTree<T>* tree)
{//ShowTree函数使用const修饰形参，导致this指针无法转换（因为inOrder、postOrder函数都是非const函数）
	
	cout << "中序遍历 ：";
	tree->inOrder(visit<T>);
	cout << "后序遍历 ：";
	tree->postOrder(visit<T>);
}
int main()
{
	int a[] = { 0,3,7,9,12,15,20,25 };
	int d[] = { 0,2,5,3 };
	
	linkedBinaryTree<int>* b,*b2;
	b2 = huffmanTree(d, 3);

	b = huffmanTree(a, 7);
	//ShowTree(b);
	int c[] = { 0,2,4,5,7,9,10,14,17,18,50 };
	b = huffmanTree(c, 10);
	ShowTree(b);//这个现实函数得随时更换前面定义的频率数组。
	return 0;
}