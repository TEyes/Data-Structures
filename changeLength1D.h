#pragma once
#include <iostream>     
#include <algorithm>
#include"myExceptions.h"
using namespace std;
 int min(int a, int b) 
 {
	 if (a > b)
		 return b;
	 else 
		 return a;
 }
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0)
		throw illegalParameterValue("newLength must be >=0");
	T* temp = new T[newLength];
	int number = min(oldLength, newLength);
	copy(a, a + number, temp);
	delete[] a;
	a = temp;
}