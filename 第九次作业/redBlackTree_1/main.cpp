#include "rbTree.h"
#include<iostream>
using namespace std;


int main () {
	RedBlack<int> myRB;
	myRB.insert(0);
	myRB.insert(3);
	myRB.insert(2);
	myRB.insert(1);
	myRB.insert(9);
	myRB.insert(8);
	myRB.insert(7);
	myRB.insert(6);
	myRB.remove(1);
	cout << myRB.size() << endl;
	myRB.travIn();
	return 0;
}