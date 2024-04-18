#include <iostream>
using namespace std;

/*
 * 继承中构造和析构顺序
 * 构造：先调用基类的构造函数，再调用组合对象的构造函数(如果有多个对象，顺序为声明顺序)，再调用派生类的构造函数
 * 析构：顺序相反
 *
 * 重载，隐藏
 * 重载：在同一作用域下，函数名相同，参数列表不同
 * 隐藏：当派生类中有和基类中同名的成员时，派生类会隐藏基类中的同名成员
 *
 * 基类和派生类的转换
 * 基类对象->派生类对象 N
 * 派生类对象->基类对象 Y
 * 基类指针指向派生类对象 Y 多态
 * 派生类指针指向基类对象 N
 */

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
