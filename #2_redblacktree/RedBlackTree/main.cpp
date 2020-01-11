#include "redblack.h"
#include <iostream>
using namespace std;

int main() {
	IntRBTree rbt;

	rbt.insert(10, 1);
	rbt.show(10);
	rbt.insert(15, 2);
	rbt.show(15);
	rbt.insert(30, 3);
	rbt.show(30);
	rbt.insert(52, 4);
	rbt.show(52);
	rbt.insert(40, 5);
	rbt.show(40);
	rbt.insert(35, 6);
	rbt.show(35);
	rbt.insert(38, 7);
	rbt.show(38);
	rbt.insert(39, 8);
	rbt.show(39);
	rbt.insert(7, 9);
	rbt.show(7);
	rbt.insert(9, 10);
	rbt.show(9);
	rbt.insert(6, 11);
	rbt.show(6);
}