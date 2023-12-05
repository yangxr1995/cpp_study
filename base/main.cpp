#include <iostream>
using namespace std;

int main()
{
	const int a = 10;
	int *p = (int *)&a;
	*p = 30;
	cout << "*p : " << *p << endl;
	cout << "a : " << a << endl;
	cout << "&a : " << &a << endl;
	cout << "p : " << p << endl;

	return 0;
}
