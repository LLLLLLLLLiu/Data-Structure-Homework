#include "RedBlackTree.h"
#include<iostream>
using namespace std;


int main () {
	RedBlack<int,int> myRB;
	pair<int, int> a, b, c, d, e, f, g;
	a.first = 1; a.second = 1;
	b.first = 1; b.second = 2;
	c.first = 3; c.second = 3;
	d.first = 4; d.second = 4;
	e.first = 5; e.second = 5;
	f.first = 6; f.second = 6;
	g.first = 7; g.second = 7;
	myRB.insert(c);
	myRB.insert(a);
	myRB.insert(b);
	myRB.insert(d);
	myRB.insert(f);
	myRB.insert(e);
	myRB.insert(g);
	myRB.remove(1);
	cout << myRB.size() << endl;
	myRB.travIn();
	cout << myRB.search(3)->data.second;
	return 0;
}