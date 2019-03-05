#include "pch.h"
#include <iostream>
#include "endian.h"

using namespace std;

int main() {
	int x = 5;
	x = endian_convert(x);
	cout << hex << x << endl;
	return 0;
}

