#pragma once
#include<iostream>
using namespace std;

template<class T>
class arrayDeque
{
public:
	arrayDeque(int initialCapacity = 10) {
		if (initialCapacity < 0) {
			cout << "错误！数组长度小于零" << endl;
			return;
		}
		arrayLength = initialCapacity;
		theArray = new T[arrayLength];
		theRight = 1;//这里可能会有问题，比如先加right而不是left会如何
		theLeft = 0;
		size = 0;
	}
	~arrayDeque() { delete[]theArray; }
	void Create(int initialCapacity) {
		if (initialCapacity < 0) {
			cout << "错误！数组长度小于零" << endl;
			return;
		}
		arrayLength = initialCapacity;
		theArray = new T[arrayLength];
		theRight = 0;
		theLeft = 0;
		size = 0;
	}
	bool IsEmpty() { return size == 0; }
	bool IsFull() { return size == arrayLength; }
	void Left() {
		if (size == 0) {
			cout << "数组为空" << endl;
			return;
		}
		return theArray[theLeft];
	}
	void Right() {
		if (size == 0) {
			cout << "数组为空" << endl;
			return;
		}
		return theArray[theRight];
	}
	void AddLeft(const T& theElement) {
		if (size == arrayLength) {
			cout << "数组已满，无法插入" << endl;
			return;
		}
		theArray[theLeft] = theElement;
		if (theLeft == 0) {
			theLeft = arrayLength - 1;
		}
		else {
			theLeft = theLeft - 1;
		}
		size++;
	}
	void AddRight(const T& theElement) {
		if (size == arrayLength) {
			cout << "数组已满，无法插入" << endl;
			return;
		}
		theArray[theRight] = theElement;
		if (theRight == arrayLength - 1) {
			theRight = 0;
		}
		else {
			theRight = theRight + 1;
		}
		size++;
	}
	void DeleteRight() {
		if (size == 0) {
			cout << "数组为空,无法删除" << endl;
			return;
		}
		if (theRight == 0) {
			theRight = arrayLength - 1;
		}
		else {
			theRight = theRight - 1;
		}
		size--;
	}
	void DeleteLeft() {
		if (size == 0) {
			cout << "数组为空，无法删除" << endl;
			return;
		}
		if (theLeft == arrayLength - 1) {
			theLeft = 0;
		}
		else {
			theLeft = theLeft + 1;
		}
		size--;
	}
	void Print() {
		int i;
		if (theLeft == arrayLength - 1) {
			i = 0;
		}
		else {
			i = theLeft + 1;
		}
		int n = size;
		while(n!=0) {
			cout << theArray[i] << " ";
			if (i == arrayLength-1) {
				i = 0;
			}
			else {
				i++;
			}
			n--;
		}
		cout << endl;
	}
private:
	int theLeft;
	int theRight;
	int arrayLength;
	int size;//用size来判断是满还是空；
	T* theArray;
};
