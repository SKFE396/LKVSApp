#include "pch.h"
#include <iostream>
#include "endian.h"

using namespace std;

int dynamic_little() {
	int x = 0;
	*(char*)&x = 1;
	return x < 255;
}

int main() {
	cout << "Static : " << little_endian() << endl
		<< "Dynamic : " << dynamic_little() << endl;
	return 0;
}

