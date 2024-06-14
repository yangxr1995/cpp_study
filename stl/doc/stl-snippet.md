# ostream_iterator istream_iterator
## istream_iterator
```cpp
template< class T,
          class CharT = char,
          class Traits = std::char_traits<CharT>,
          class Distance = std::ptrdiff_t >
class istream_iterator
    : public std::iterator<std::input_iterator_tag, T, Distance, const T*, const T&>
template< class T,
          class CharT = char,
          class Traits = std::char_traits<CharT>,
          class Distance = std::ptrdiff_t >
class istream_iterator;
```
istream_iterator 是 istream 的 iterator, 从他构造函数绑定的basic_istream 对象中连续读出 T类型的对象，通过合适的 operator>>实现

实际上读操作在iterator增加时被执行，而不是在 iterator 解引用时。

当iterator构造时，读取第一个对象。解引用只返回最近读取的对象的拷贝

istream_iterator的默认构造被作为 end-of-stream iterator。 

当有效的 istream_iterator 到达底层流的末尾时，他会等于 end-of-stream iterator。

此时进行解引用或增加操作调用是未定义的

end-of-stream iterator 保留 end-of-stream 状态，即使底层流状态改变。 只要没有重新赋值，他就不能再作为 non-end-of-stream iterator

一个典型的 istream_iterator 实现持有两个数据成员 : 一个关联 basic_istream 对象的指针，和最近读取的T类型的值

### NOTE
since it avoids the overhead of constructing and destructing the sentry object once per character.

当读取字符串时， istream_iterator 默认跳过空格（除非禁用 std::noskipws 或等价的函数），

然而 istreambuf_iterator 不会跳过空格，此外， istreambuf_iterator 更加有效，因为他避免了对哨兵对象的构造析构开销。

## ostream_iterator
```cpp
template< class T,
          class CharT = char,
          class Traits = std::char_traits<CharT> >
class ostream_iterator
    : public std::iterator<std::output_iterator_tag, void, void, void, void>
template< class T,
          class CharT = char,
          class Traits = std::char_traits<CharT> >
class ostream_iterator;
```

std::ostream_iterator is a single-pass LegacyOutputIterator that writes successive objects of type T into the std::basic_ostream object for which it was constructed, using operator<<.
		
ostream_iterator 是单方向的 LegacyOutputIterator ，通过 operator<< ，将连续的 T 类型的对象写入他构造参数 basic_ostream 对象。

Optional delimiter string is written to the output stream after every write operation. 

在每次写操作后可选的分割字符串会被写道输出流。

The write operation is performed when the iterator (whether dereferenced or not) is assigned to. 

写操作在 iterator(无论是否解引用) 被赋值时执行.

Incrementing the std::ostream_iterator is a no-op.

增加 ostream_iterator 是空操作

In a typical implementation, the only data members of std::ostream_iterator are a pointer to the associated std::basic_ostream and a pointer to the first character in the delimiter string.

典型的实现中，ostream_iterator 的一个成员数据是一个指针，指针被关联到 basic_ostream ，和另一个指针，指向分割字符串

When writing characters, std::ostreambuf_iterator is more efficient, since it avoids the overhead of constructing and destructing the sentry object once per character.

当写字符时，ostreambuf_iterator 更加高效，因为他避免了哨兵对象的构造和析构的开销

### 示例

```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
 
int main()
{
    std::istringstream str("0.1 0.2 0.3 0.4");
    // 
    std::partial_sum(std::istream_iterator<double>(str),
                     std::istream_iterator<double>(),
                     std::ostream_iterator<double>(std::cout, " "));
 
    std::istringstream str2("1 3 5 7 8 9 10");
    auto it = std::find_if(std::istream_iterator<int>(str2),
                           std::istream_iterator<int>(),
                           [](int i){ return i % 2 == 0; });
 
    if (it != std::istream_iterator<int>())
        std::cout << "\nThe first even number is " << *it << ".\n";
    //" 9 10" left in the stream
}
```

```cpp
#include<iostream>
#include<string>
#include<iterator>
#include<algorithm>
using namespace std;
int main()
{
    string text;
    istream_iterator<int> is(cin);//绑定标准输入装置
    istream_iterator<int> eof;//定义输入结束位置
    copy(is,eof,back_inserter(text));
    sort(text.begin(),text.end());

    ostream_iterator<int> os(cout,", ");//绑定标准输出装置
    copy(text.begin(),text.end(),os);
}
```

```c
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main()
{
    ifstream in_file("input_file.txt");
    ofstream out_file("output_file.txt");
    if(!in_file || !out_file)
    {
        cout<<"filesopen failed!\n";
        return -1;
    }
    istream_iterator<string> is(in_file);
    istream_iterator<string> eof; // istream_iterator 不绑定 istream 对象，则表示 eof
    vector<string> text;

    copy(is,eof,back_inserter(text));
    sort(text.begin(),text.end());

    ostream_iterator<string> os(out_file," ");
    copy(text.begin(),text.end(),os);
    return 0;
}
```

# istreambuf_iterator ostreambuf_iterator
## istreambuf_iterator

std::istreambuf_iterator is a single-pass input iterator that reads successive characters from the std::basic_streambuf object for which it was constructed.

istreambuf_iterator 是单向输入 iterator , iterator 连续从 basic_istream 对象读取字符， basic_ostream 对象在 istreambuf_iterator 构造时绑定

The default-constructed std::istreambuf_iterator is known as the end-of-stream iterator. 

默认的 istreambuf_iterator 是 end-of-stream iterator, 

When a valid std::istreambuf_iterator reaches the end of the underlying stream, it becomes equal to the end-of-stream iterator. Dereferencing or incrementing it further invokes undefined behavior.

当 有效的 istreambuf_iterator 到达底层流末尾时，他变成了 end-of-stream iterator。 无论如何，无论解引用或增加都会导致未定义行为


### 示例
```cpp
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
 
int main()
{
    典型用例：表示为一对迭代器的输入流
    std::istringstream in{"Hello, world"};
    std::istreambuf_iterator<char> it{in}, end;
    std::string ss{it, end};
    std::cout << "ss has " << ss.size() << " bytes; "
                 "it holds \"" << ss << "\"\n";
 
    单程性质的演示
    std::istringstream s{"abc"};
    std::istreambuf_iterator<char> i1{s}, i2{s};
    std::cout << "i1 returns '" << *i1 << "'\n"
                 "i2 returns '" << *i2 << "'\n";
 
    ++i1;
    std::cout << "after incrementing i1, but not i2:\n"
                 "i1 returns '" << *i1 << "'\n"
                 "i2 returns '" << *i2 << "'\n";
 
    ++i2;
    std::cout << "after incrementing i2, but not i1:\n"
                 "i1 returns '" << *i1 << "'\n"
                 "i2 returns '" << *i2 << "'\n";
}
```

## ostreambuf_iterator

std::ostreambuf_iterator is a single-pass LegacyOutputIterator that writes successive characters into the std::basic_streambuf object for which it was constructed. The actual write operation is performed when the iterator (whether dereferenced or not) is assigned to. Incrementing the std::ostreambuf_iterator is a no-op.

In a typical implementation, the only data members of std::ostreambuf_iterator are a pointer to the associated std::basic_streambuf and a boolean flag indicating if the end of file condition has been reached.

### 示例
```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
 
int main()
{
    std::string s = "This is an example\n";
    std::copy(s.begin(), s.end(), std::ostreambuf_iterator<char>(std::cout));
}
```

# back_inserter
```cpp
template< class Container >
std::back_insert_iterator<Container> back_inserter( Container& c );
```

模板函数，根据 容器c 构造对应类型的 back_insert_iterator。

容器c需要支持 push_back 

back_insert_iterator 用于在容器末尾添加元素

```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
 
int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::fill_n(std::back_inserter(v), 3, -1);
    for (int n : v)
        std::cout << n << ' ';
    std::cout << '\n';
}
```

# back_insert_iterator

```cpp
template< class Container >
class back_insert_iterator
    : public std::iterator<std::output_iterator_tag, void, void, void, void>
template< class Container >
class back_insert_iterator;
```

std::back_insert_iterator is a LegacyOutputIterator that appends elements to a container for which it was constructed. 

back_insert_iterator 是 LegacyOutputIterator ，追加元素到构造时的容器

The container's push_back() member function is called whenever the iterator (whether dereferenced or not) is assigned to. 

当iterator 被赋值时，容器的 push_back 方法被调用。

Incrementing the std::back_insert_iterator is a no-op.

增加 back_insert_iterator 是空操作


```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
 
int main()
{
    std::vector<int> v;
 
    std::generate_n(
        std::back_insert_iterator<std::vector<int>>(v),
            // Or use std::back_inserter helper
            // Or use std::back_insert_iterator(v) C++17's syntax
        10,
        [n = 0]() mutable { return ++n; }
    );
 
    for (int n : v)
        std::cout << n << ' ';
    std::cout << '\n';
}
```

# find find_if find_if_not

Returns an iterator to the first element in the range [first, last) that satisfies specific criteria (or last if there is no such iterator).

返回指向第一个在 [first, last) 范围内满足特定条件的元素的 iterator.

如果没有，则返回last iterator

1) find searches for an element equal to value (using operator==).

find 查找一个元素，使用 operator== value

3) find_if searches for an element for which predicate p returns true.

find_if 搜索元素，谁的谓词 (predicate) 为真

5) find_if_not searches for an element for which predicate q returns false.

find_if_not 搜索元素，说的谓词为假

支持的谓词为一元谓词，返回值必须为bool，不论是函数对象还是函数，只要支持 operator(), 支持 p(v)。p()中不能修改v

## 示例

```cpp
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <vector>

using namespace  std;
 
int main()
{
    const auto v = {1, 2, 3, 4};
 
    for (const int n : {3, 5})
        (std::find(v.begin(), v.end(), n) == std::end(v))
            ? std::cout << "v does not contain " << n << '\n'
            : std::cout << "v contains " << n << '\n';

    auto is_even = [](int i) { return i % 2 == 0; };

    for (const auto &w : {vector<int>{1, 2 , 3, 4}, vector<int>{1, 3, 5}}) {
        auto it = find_if(w.begin(), w.end(), is_even);
        if (it != w.end())
            cout << "w contains even number" << endl;
        else
            cout << "w not contains even number" << endl;
    }

    return 0;
}
```



