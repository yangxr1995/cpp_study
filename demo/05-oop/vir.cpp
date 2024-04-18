#include <iostream>
using namespace std;

class A {
	public:
		int m_a;
		A(int a) :m_a(a) {}
};

class B : virtual public A {
	public:
		int m_b;
		B(): A(0) { m_b = 1; }
};

class C : public B {
	public:
		int m_c;
		C(): A(0) { m_c = 1; }
};

void func(B *p)
{
	cout << p->m_a << endl;
}

int main()
{
	C c;
	B b;

	func(&c);
	func(&b);

	return 0;
}

