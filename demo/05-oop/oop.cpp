#include <iostream>
using namespace std;

class Base {
	public:	
		Base() {
			cout << "Base()" << endl;
		}
		~Base() {
			cout << "~Base()" << endl;
		}
};

class AA {
	public:
		AA(int a) :_a(a) {
			cout << "AA()" << endl;
		}
		~AA() {
			cout << "~AA()" << endl;
		}
		int _a;
};

class BB :public Base {
	public:
		BB(int a) :_aa(a) {
			cout << "BB()" << endl;
		}
		~BB() {
			cout << "~BB()" << endl;
		}
		AA _aa;
};

int main()
{
	/*
	 * Base()
	 * AA()
	 * BB()
	 * ~BB()
	 * ~AA()
	 * ~Base()
	 */
	BB b(1);

	return 0;
}
