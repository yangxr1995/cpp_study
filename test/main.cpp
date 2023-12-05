#include <iostream>
using namespace std;

void func(int a)
{
	a = 10;	
}

int main()
{
	int &&c = 10;

	func(c);

	return 0;
}
