#include <iostream>
using namespace std;

class Base {
	public:
		virtual void show() {
			cout << "Base::show()" << endl;
		}
};

class Sub : public Base {
	public:
		/*
		 * 1. 找到虚函数
		 * 编译阶段，编译器从基类虚函数表找到
		 * 一样的函数（返回值，函数名，参数列表）,
		 * 将子类的函数定义为虚函数
		 * void show() --> virtual void show()
		 * 
		 * 2. 子类定义自己的vftable
		 * 由于子类有virtual函数，所以编译器会为子类
		 * 定义vftable
		 *
		 * 3. 子类的vptr指向自己的vftable
		 * 由于子类有自己的vftable，所以子类对象的vptr
		 * 指向自己的vftable.
		 * 如果子类没有自己的vftable，子类对象会继承vptr,
		 * 但是子类对象的vptr指向基类的vftable
		 */
		void show() {
			cout << "Sub::show()" << endl;
		}
};

int main()
{
	Sub s;	
	Base *b;

	b = &s;
	b->show();

	return 0;
}
