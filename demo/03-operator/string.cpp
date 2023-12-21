#include <alloca.h>
#include <iostream>
#include <ostream>
#include <string.h>
using namespace std;

class String {
public:	
	String(const char *str = nullptr) {
		// 1. nullptr当""，以简化后续处理
		if (str == nullptr)
			str = "";
		_ptr = new char [strlen(str) + 1];
		strcpy(_ptr, str);
	}

	String(const String &str) {
		_ptr = new char [str.length() + 1];
		strcpy(_ptr, str._ptr);
	}

	~String() {
		delete [] _ptr;
		_ptr = nullptr;
	}

	int length() const {
		return strlen(_ptr);	
	}

	String &operator=(const String &str) {
		delete [] _ptr;
		_ptr = new char [strlen(str._ptr) + 1];
		strcpy(_ptr, str._ptr);
		return *this;
	}
		
	// 2. 定义const和非const
	const char &operator[] (int index) const {
		return _ptr[index];
	}
	char &operator[] (int index) {
		return _ptr[index];
	}

	String &operator+=(const String &str) {
		char *tmp;
		tmp = new char [length() + str.length() + 1];
		strcpy(tmp, _ptr);
		strcat(tmp, str._ptr);
		delete [] _ptr;
		_ptr = tmp;
		return *this;
	}
 
	bool operator==(const String &str) const {
		return strcmp(_ptr, str._ptr) == 0;
	}

	bool operator>(const String &str) const {
		return strcmp(_ptr, str._ptr) > 0;
	}

	bool operator<(const String &str) const {
		return strcmp(_ptr, str._ptr) < 0;
	}

	char *c_str() const {
		return _ptr;	
	}

	friend const String operator+(const String &s1, const String &s2);
	friend ostream &operator<<(ostream &out, const String &str);
	friend istream &operator>>(istream &in, String &str);

	/*
	 * 迭代器，为了统一所有容器遍历而实现的中间层，
	 * 本质上是对容器元素的指针的封装
	 *
	 * for (String::iterator i = ss.begin(); i != ss.end(); ++i)
	 * 	cout << *i << " ";
	 * 	迭代器需要：
	 * 		构造函数
	 * 		operator!=
	 * 		operator*
	 * 		operator++()
	 */
	class iterator {
	public:
		iterator(char *p)
		:_p(p) 
		{

		}
		
		bool operator!=(const iterator &i) const 
		{
			return _p != i._p;	
		}

		// 4. 迭代器使用前置++，因为返回引用，不需要临时量
		iterator &operator++() {
			++_p;
			return *this;
		}

		char operator*() {
			return *_p;
		}

		const char operator*() const {
			return *_p;
		}

	private:
		char *_p;
	};

	iterator begin() const {
		return iterator(_ptr);
	}

	iterator end() const {
		return iterator(_ptr + strlen(_ptr));
	}

private:
	char *_ptr;
};

// 3. 不能做类方法，否则下面表达式错误
// s4 = "bbb" + s3;
const String operator+(const String &s1, const String &s2) {
	char *tmp = (char *)alloca(s1.length() + s2.length() + 1);
	strcpy(tmp, s1._ptr);
	strcat(tmp, s2._ptr);
	return String(tmp);
}

ostream &operator<<(ostream &out, const String &str)
{
	out << str._ptr;
	return out;
}


// FIXME
// 支持任意长度的输入 
istream &operator>>(istream &in, String &str)
{
	in >> str._ptr;
	return in;
}

int main()
{
	String s1 = "aaa";
	String s2 = "1234";

	String s3 = s1 + s2;

	cout << s3 << endl;

	String s4 = s3 + "ccc";
	cout << s4 << endl;

	s4 = "bbb" + s3;
	cout << s4 << endl;

	cin >> s4;
	cout << s4 << endl;

	const String ss = "hello world";

	for (String::iterator i = ss.begin(); i != ss.end(); ++i)
		cout << *i << " ";
	cout << endl;
	
	for (char ch: ss)
		cout << ch << " ";
	cout << endl;	

	for (auto i = ss.begin(); i != ss.end(); ++i)
		cout << *i << " ";
	cout << endl;

	return 0;
}
