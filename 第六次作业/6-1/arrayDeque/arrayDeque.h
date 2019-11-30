#pragma once
#include<iostream>
using namespace std;

template<class T>
class arrayDeque
{
public:
	arrayDeque(int initialCapacity = 10) {
		if (initialCapacity < 0) {
			cout << "�������鳤��С����" << endl;
			return;
		}
		arrayLength = initialCapacity;
		theArray = new T[arrayLength];
		theRight = 1;//������ܻ������⣬�����ȼ�right������left�����
		theLeft = 0;
		size = 0;
	}
	~arrayDeque() { delete[]theArray; }
	void Create(int initialCapacity) {
		if (initialCapacity < 0) {
			cout << "�������鳤��С����" << endl;
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
			cout << "����Ϊ��" << endl;
			return;
		}
		return theArray[theLeft];
	}
	void Right() {
		if (size == 0) {
			cout << "����Ϊ��" << endl;
			return;
		}
		return theArray[theRight];
	}
	void AddLeft(const T& theElement) {
		if (size == arrayLength) {
			cout << "�����������޷�����" << endl;
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
			cout << "�����������޷�����" << endl;
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
			cout << "����Ϊ��,�޷�ɾ��" << endl;
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
			cout << "����Ϊ�գ��޷�ɾ��" << endl;
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
	int size;//��size���ж��������ǿգ�
	T* theArray;
};
