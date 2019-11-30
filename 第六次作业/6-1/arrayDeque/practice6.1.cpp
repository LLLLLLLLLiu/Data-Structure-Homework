#include<iostream>
#include<fstream>
#include"arrayDeque.h"
using namespace std;

int main() {
	arrayDeque<int> myDeque;
	ifstream inFile("input.txt");
	string str;
	int num;
	while (inFile>>str) {
		if (str == "AddLeft") {
			inFile >> num;
			myDeque.AddLeft(num);
			myDeque.Print();
		}
		else if (str == "AddRight") {
			inFile >> num;
			myDeque.AddRight(num);
			myDeque.Print();
		}
		else if (str == "DeleteLeft") {
			myDeque.DeleteLeft();
			myDeque.Print();
		}
		else if (str == "DeleteRight") {
			myDeque.DeleteRight();
			myDeque.Print();
		}
		else if (str == "IsEmpty") {
			if (myDeque.IsEmpty() == 1) {
				cout << "Yes" << endl;
			}
			else {
				cout << "No" << endl;
			}
		}
		else if (str == "IsFull") {
			if (myDeque.IsFull() == 1) {
				cout << "Yes" << endl;
			}
			else {
				cout << "No" << endl;
			}
		}
		else if (str == "End") {
			break;
		}
	}
	return 0;
}