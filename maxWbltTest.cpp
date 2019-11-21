#include"maxWblt.h"
#include<iostream>

using namespace std;
int main()
{
	maxWblt<int> a,b;
	int n1[6]{ 0,1,3,12,9,4 };
	int n2[5]{ 0,20,10,4,2 };
	a.initialize(n1, 5);
	b.initialize(n2, 4);
	a.meld(b);
	a.pop();
	a.pop();
	a.push(4);
	return 0;
}