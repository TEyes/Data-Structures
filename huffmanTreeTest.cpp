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
{//ShowTree����ʹ��const�����βΣ�����thisָ���޷�ת������ΪinOrder��postOrder�������Ƿ�const������
	
	cout << "������� ��";
	tree->inOrder(visit<T>);
	cout << "������� ��";
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
	ShowTree(b);//�����ʵ��������ʱ����ǰ�涨���Ƶ�����顣
	return 0;
}