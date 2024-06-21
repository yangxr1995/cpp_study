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

std::ostreambuf_iterator is a single-pass LegacyOutputIterator that writes successive characters into the std::basic_streambuf object for which it was constructed. 

The actual write operation is performed when the iterator (whether dereferenced or not) is assigned to. Incrementing the std::ostreambuf_iterator is a no-op.

In a typical implementation, the only data members of std::ostreambuf_iterator are a pointer to the associated std::basic_streambuf and a boolean flag indicating 

if the end of file condition has been reached.

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

# back_inserter front_inserter inserter
## back_inserter
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

### back_insert_iterator

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

## front_inserter
```cc
template< class Container >
std::front_insert_iterator<Container> front_inserter( Container& c );
```

front_inserter is a convenience function template that constructs a std::front_insert_iterator for the container c 

with the type deduced from the type of the argument.

front_inserter 根据 模板参数类型 推导 容器c ，构造 容器c的 front_insert_iterator

A std::front_insert_iterator which can be used to add elements to the beginning of the container c.

front_inserter 用于在容器c的开头添加元素

```cc
#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <vector>
 
int main()
{
    std::vector<int> v{1, 2, 3, 4, 5};
    std::deque<int> d;
    std::copy(v.begin(), v.end(), std::front_inserter(d));
    for (int n : d)
        std::cout << n << ' ';
    std::cout << '\n';
}
```

## inserter
```cc
template< class Container >
std::insert_iterator<Container>
    inserter( Container& c, typename Container::iterator i );
template< class Container >
constexpr std::insert_iterator<Container>
    inserter( Container& c, ranges::iterator_t<Container> i );
```
inserter is a convenience function template that constructs a std::insert_iterator for the container c 

and its iterator i with the type deduced from the type of the argument.

inserter 用于构造 insert_iterator 

### Parameters
c	-	container that supports an insert operation

c - 支持insert操作的容器

i	-	iterator in c indicating the insertion position

i - c的iterator，用于指示插入位置

### 示例
```cc
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>
 
int main()
{
    std::multiset<int> s{1, 2, 3};
 
    // std::inserter is commonly used with multi-sets
    std::fill_n(std::inserter(s, s.end()), 5, 2);
 
    for (int n : s)
        std::cout << n << ' ';
    std::cout << '\n';
 
    std::vector<int> d{100, 200, 300};
    std::vector<int> v{1, 2, 3, 4, 5};
 
    // when inserting in a sequence container, insertion point advances
    // because each std::insert_iterator::operator= updates the target iterator
    std::copy(d.begin(), d.end(), std::inserter(v, std::next(v.begin())));
 
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

# search
```cpp
(1)
template< class ForwardIt1, class ForwardIt2 >
ForwardIt1 search( ForwardIt1 first, ForwardIt1 last,
                   ForwardIt2 s_first, ForwardIt2 s_last );

(2)
template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2 >
ForwardIt1 search( ExecutionPolicy&& policy,
                   ForwardIt1 first, ForwardIt1 last,
                   ForwardIt2 s_first, ForwardIt2 s_last );

(3)
template< class ForwardIt1, class ForwardIt2, class BinaryPred >
ForwardIt1 search( ForwardIt1 first, ForwardIt1 last,
                   ForwardIt2 s_first, ForwardIt2 s_last,
                   BinaryPred p );
(4)
template< class ExecutionPolicy,
          class ForwardIt1, class ForwardIt2, class BinaryPred >
ForwardIt1 search( ExecutionPolicy&& policy,
                   ForwardIt1 first, ForwardIt1 last,
                   ForwardIt2 s_first, ForwardIt2 s_last,
                   BinaryPred p );

```
1-4) Searches for the first occurrence of the sequence of elements [s_first, s_last) in the range [first, last).

1-4) 搜索[s_first, s_last) 的元素序列在 [first, last) 范围内的第一次的出现

- 1) Elements are compared using operator==.

重载1的元素比较使用 operator==

3) Elements are compared using the given binary predicate p.

重载3的元素比较使用用户指定的二进制谓词p

2,4) Same as (1,3), but executed according to policy.

重载2，4 和 1，3 一样，但是 根据 policy

## Type requirements
- ForwardIt1, ForwardIt2 must meet the requirements of LegacyForwardIterator.

- BinaryPred must meet the requirements of BinaryPredicate.

### BinaryPredicate
两个参数，返回bool
```cpp
bool p(iter *, iter *)
```

## 返回值

1-4) Iterator to the beginning of first occurrence of the sequence [s_first, s_last) in the range [first, last). If no such occurrence is found, last is returned.

1-4) 返回迭代器，如果找到，迭代器指向 [first, last) 中的第一个元素，此元素是首次匹配的位置，如果没有，则返回 last

 If [s_first, s_last) is empty, first is returned.

如果 [s_first, s_last) 为空，返回 first

## 示例
```cpp
#include <algorithm>
#include <cassert>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string_view>
#include <vector>
 
using namespace std::literals;
 
bool contains(const auto& cont, std::string_view s)
{
    // str.find() (or str.contains(), since C++23) can be used as well
    return std::search(cont.begin(), cont.end(), s.begin(), s.end()) != cont.end();
}
 
int main()
{
    const auto str{"why waste time learning, when ignorance is instantaneous?"sv};
    assert(contains(str, "learning"));
    assert(not contains(str, "lemming"));
 
    const std::vector vec(str.begin(), str.end());
    assert(contains(vec, "learning"));
    assert(not contains(vec, "leaning"));
 
    // The C++17 overload with searchers demo:
    constexpr auto quote
    {
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed "
        "do eiusmod tempor incididunt ut labore et dolore magna aliqua"sv
    };
 
    for (const auto word : {"pisci"sv, "Pisci"sv})
    {
        std::cout << "The string " << std::quoted(word) << ' ';
        const std::boyer_moore_searcher searcher(word.begin(), word.end());
        const auto it = std::search(quote.begin(), quote.end(), searcher);
        if (it == quote.end())
            std::cout << "not found\n";
        else
            std::cout << "found at offset " << std::distance(quote.begin(), it) << '\n';
    }
}
```
# getline
```
template< class CharT, class Traits, class Allocator >
std::basic_istream<CharT, Traits>&
    getline( std::basic_istream<CharT, Traits>& input,
             std::basic_string<CharT, Traits, Allocator>& str, CharT delim );
(1)	
template< class CharT, class Traits, class Allocator >
std::basic_istream<CharT, Traits>&
    getline( std::basic_istream<CharT, Traits>&& input,
             std::basic_string<CharT, Traits, Allocator>& str, CharT delim );
(2)	(since C++11)
template< class CharT, class Traits, class Allocator >
std::basic_istream<CharT, Traits>&
    getline( std::basic_istream<CharT, Traits>& input,
             std::basic_string<CharT, Traits, Allocator>& str );
(3)	
template< class CharT, class Traits, class Allocator >
std::basic_istream<CharT, Traits>&
    getline( std::basic_istream<CharT, Traits>&& input,
             std::basic_string<CharT, Traits, Allocator>& str );
```


getline reads characters from an input stream and places them into a string:

getline 从input stream 读取字符，并将其存入 string

1,2) Behaves as UnformattedInputFunction, except that input.gcount() is not affected. After constructing and checking the sentry object, performs the following:

1,2) 作为 UnformattedInputFunction, 不影响 input.gcount()。 

1) Calls str.erase().


2) Extracts characters from input and appends them to str until one of the following occurs (checked in the order listed)

从流提取字符，并追加到str，直到以下情况发送

a) end-of-file condition on input, in which case, getline sets eofbit.

到达流末尾，getline 设置 eofbit

b) the next available input character is delim, as tested by Traits::eq(c, delim), in which case the delimiter character is extracted from input, 

but is not appended to str.

下一个有效的输入字符是分隔符，内部使用 Traits::eq(c, delim) 检查，这种情况分隔符字符被从流中提取，但是不追加到 str

c) str.max_size() characters have been stored, in which case getline sets failbit and returns.

str 满了，这种情况设置failbit

3) If no characters were extracted for whatever reason (not even the discarded delimiter), getline sets failbit and returns.

3,4) Same as getline(input, str, input.widen('\n')), that is, the default delimiter is the endline character.

## NOTE

When consuming whitespace-delimited input (e.g. int n; std::cin >> n;) 

当消耗空白分隔符输入，如 int n; std::cin>> n; 

any whitespace that follows, including a newline character, will be left on the input stream. 

任何随后的空白符，包括换行符，会被留在流中。

Then when switching to line-oriented input, the first line retrieved with getline will be just that whitespace. 

当再次进行流输入时，首次接受会是空格符，

In the likely case that this is unwanted behaviour, possible solutions include:

这种情况通常时不希望的，有以下可能解决方法

An explicit extraneous initial call to getline.

1. 显示进行额外的getline

Removing consecutive whitespace with std::cin >> std::ws.

2. 使用 std::cin>>std::ws 来移除连续的空白符

Ignoring all leftover characters on the line of input with cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');.

3. 忽略行输入行上的所有字符，使用 cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');.

```cpp
#include <iostream>
#include <sstream>
#include <string>
 
int main()
{
    // greet the user
    std::string name;
    std::cout << "What is your name? ";
    std::getline(std::cin, name);
    std::cout << "Hello " << name << ", nice to meet you.\n";
 
    // read file line by line
    std::istringstream input;
    input.str("1\n2\n3\n4\n5\n6\n7\n");
    int sum = 0;
    for (std::string line; std::getline(input, line);)
        sum += std::stoi(line);
    std::cout << "\nThe sum is " << sum << ".\n\n";
 
    // use separator to read parts of the line
    std::istringstream input2;
    input2.str("a;b;c;d");
    for (std::string line; std::getline(input2, line, ';');)
        std::cout << line << '\n';
}
```

# accumulate
```cc
template< class InputIt, class T >
T accumulate( InputIt first, InputIt last, T init );
template< class InputIt, class T, class BinaryOp >
T accumulate( InputIt first, InputIt last, T init, BinaryOp op );
```

Computes the sum of the given value init and the elements in the range [first, last).

求和：init值 累加 [first, last) 的元素

1) Initializes the accumulator acc (of type T) with the initial value init and then modifies it 

with `acc = acc + *i(until C++20)acc = std::move(acc) + *i(since C++20)` for every iterator i in the range [first, last) in order.

2) Initializes the accumulator acc (of type T) with the initial value init and then modifies it 

with `acc = op(acc, *i)(until C++20)acc = op(std::move(acc), *i)(since C++20) ` for every iterator i in the range [first, last) in order.

If any of the following conditions is satisfied, the behavior is undefined:

T is not CopyConstructible.
T is not CopyAssignable.
op modifies any element of [first, last).
op invalidates any iterator or subrange in [first, last].

```cc
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
 
int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 
    int sum = std::accumulate(v.begin(), v.end(), 0);
    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
 
    auto dash_fold = [](std::string a, int b)
    {
        return std::move(a) + '-' + std::to_string(b);
    };
 
    std::string s = std::accumulate(std::next(v.begin()), v.end(),
                                    std::to_string(v[0]), // start with first element
                                    dash_fold);
 
    // Right fold using reverse iterators
    std::string rs = std::accumulate(std::next(v.rbegin()), v.rend(),
                                     std::to_string(v.back()), // start with last element
                                     dash_fold);
 
    std::cout << "sum: " << sum << '\n'
              << "product: " << product << '\n'
              << "dash-separated string: " << s << '\n'
              << "dash-separated string (right-folded): " << rs << '\n';
}
```

# copy remove_copy remove_copy_if
## remove_copy remove_copy_if
```cc
template< class InputIt, class OutputIt, class T >
OutputIt remove_copy( InputIt first, InputIt last,
                      OutputIt d_first, const T& value );

(1)
template< class InputIt, class OutputIt,
          class T = typename std::iterator_traits
                        <InputIt>::value_type >
constexpr OutputIt remove_copy( InputIt first, InputIt last,
                                OutputIt d_first, const T& value );

template< class ExecutionPolicy,
          class ForwardIt1, class ForwardIt2, class T >
ForwardIt2 remove_copy( ExecutionPolicy&& policy,
                        ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 d_first, const T& value );

(2)
template< class ExecutionPolicy,
          class ForwardIt1, class ForwardIt2,
          class T = typename std::iterator_traits
                        <ForwardIt1>::value_type >
ForwardIt2 remove_copy( ExecutionPolicy&& policy,
                        ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 d_first, const T& value );

(3)
template< class InputIt, class OutputIt, class UnaryPred >
OutputIt remove_copy_if( InputIt first, InputIt last,
                         OutputIt d_first, UnaryPred p );

(4)
template< class ExecutionPolicy,
          class ForwardIt1, class ForwardIt2, class UnaryPred >
ForwardIt2 remove_copy_if( ExecutionPolicy&& policy,
                           ForwardIt1 first, ForwardIt1 last,
                           ForwardIt2 d_first, UnaryPred p );
```

从 [first, last) 拷贝元素到 从 d_first开始的范围，省略满足特定条件的元素。

1） 忽略所有等于value的元素 ,使用operator==

2)  忽略所有谓词 p 为真的元素

## Return value
Iterator to the element past the last element copied.

## 可能的实现
### remove_copy
```cc
template<class InputIt, class OutputIt,
         class T = typename std::iterator_traits<InputIt>::value_type>
constexpr OutputIt remove_copy(InputIt first, InputIt last,
                               OutputIt d_first, const T& value)
{
    for (; first != last; ++first)
        if (!(*first == value))
            *d_first++ = *first;
    return d_first;
}
```

### remove_copy_if
```cc
template<class InputIt, class OutputIt, class UnaryPred>
constexpr OutputIt remove_copy_if(InputIt first, InputIt last,
                                  OutputIt d_first, UnaryPred p)
{
    for (; first != last; ++first)
        if (!p(*first))
            *d_first++ = *first;
    return d_first;
}
```

## 示例
```cc
#include <algorithm>
#include <complex>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
 
int main()
{
    // Erase the hash characters '#' on the fly.
    std::string str = "#Return #Value #Optimization";
    std::cout << "before: " << std::quoted(str) << '\n';
 
    std::cout << "after:  \"";
    std::remove_copy(str.begin(), str.end(),
                     std::ostream_iterator<char>(std::cout), '#');
    std::cout << "\"\n";
 
    // Erase {1, 3} value on the fly.
    std::vector<std::complex<double>> nums{{2, 2}, {1, 3}, {4, 8}, {1, 3}};
    std::remove_copy(nums.begin(), nums.end(),
                     std::ostream_iterator<std::complex<double>>(std::cout),
    #ifdef __cpp_lib_algorithm_default_value_type
                     {1, 3}); // T gets deduced
    #else
                     std::complex<double>{1, 3});
    #endif
}
```

# remove remove_if
```cc
template< class ForwardIt, class T >
ForwardIt remove( ForwardIt first, ForwardIt last, const T& value );

(1)
template< class ForwardIt, class T = typename std::iterator_traits
                                         <ForwardIt>::value_type >
constexpr ForwardIt remove( ForwardIt first, ForwardIt last,
                            const T& value );

template< class ExecutionPolicy, class ForwardIt, class T >
ForwardIt remove( ExecutionPolicy&& policy,
                  ForwardIt first, ForwardIt last, const T& value );

(2)
template< class ExecutionPolicy, class ForwardIt,
          class T = typename std::iterator_traits
                        <ForwardIt>::value_type >
ForwardIt remove( ExecutionPolicy&& policy,
                  ForwardIt first, ForwardIt last, const T& value );

(3)
template< class ForwardIt, class UnaryPred >
ForwardIt remove_if( ForwardIt first, ForwardIt last, UnaryPred p );

(4)
template< class ExecutionPolicy, class ForwardIt, class UnaryPred >
ForwardIt remove_if( ExecutionPolicy&& policy,
                     ForwardIt first, ForwardIt last, UnaryPred p );
```

Removes all elements satisfying specific criteria from the range [first, last) and returns a past-the-end iterator for the new end of the range.

删除所有满足特定条件的元素，返回新范围的end 迭代器

1) Removes all elements that are equal to value (using operator==).

3) Removes all elements for which predicate p returns true.

2,4) Same as (1,3), but executed according to policy.
 These overloads participate in overload resolution only if

## 可能实现
### remove
```cc
template<class ForwardIt, class T = typename std::iterator_traits<ForwardIt>::value_type>
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
{
    first = std::find(first, last, value);
    if (first != last)
        for (ForwardIt i = first; ++i != last;)
            if (!(*i == value))
                *first++ = std::move(*i);
    return first;
}
```

### remove_if
```cc
template<class ForwardIt, class UnaryPred>
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPred p)
{
    first = std::find_if(first, last, p);
    if (first != last)
        for (ForwardIt i = first; ++i != last;)
            if (!p(*i))
                *first++ = std::move(*i);
    return first;
}
```

## 示例
```cc
#include <algorithm>
#include <cassert>
#include <cctype>
#include <complex>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
 
int main()
{
    std::string str1{"Text with some   spaces"};
 
    auto noSpaceEnd = std::remove(str1.begin(), str1.end(), ' ');
 
    // The spaces are removed from the string only logically.
    // Note, we use view, the original string is still not shrunk:
    std::cout << std::string_view(str1.begin(), noSpaceEnd) 
              << " size: " << str1.size() << '\n';
 
    str1.erase(noSpaceEnd, str1.end());
 
    // The spaces are removed from the string physically.
    std::cout << str1 << " size: " << str1.size() << '\n';
 
    std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
    str2.erase(std::remove_if(str2.begin(), 
                              str2.end(),
                              [](unsigned char x) { return std::isspace(x); }),
               str2.end());
    std::cout << str2 << '\n';
 
    std::vector<std::complex<double>> nums{{2, 2}, {1, 3}, {4, 8}};
    #ifdef __cpp_lib_algorithm_default_value_type
        nums.erase(std::remove(nums.begin(), nums.end(), {1, 3}), nums.end());
    #else
        nums.erase(std::remove(nums.begin(), nums.end(), std::complex<double>{1, 3}),
                   nums.end());
    #endif
    assert((nums == std::vector<std::complex<double>>{{2, 2}, {4, 8}}));
}
```

输出
```
Textwithsomespaces size: 23
Textwithsomespaces size: 18
Textwithsomewhitespaces
```

# transform
```cc
(1)
template< class InputIt, class OutputIt, class UnaryOp >
OutputIt transform( InputIt first1, InputIt last1,
                    OutputIt d_first, UnaryOp unary_op );

(2)
template< class ExecutionPolicy,
          class ForwardIt1, class ForwardIt2, class UnaryOp >
ForwardIt2 transform( ExecutionPolicy&& policy,
                      ForwardIt1 first1, ForwardIt1 last1,
                      ForwardIt2 d_first, UnaryOp unary_op );

(3)
template< class InputIt1, class InputIt2,
          class OutputIt, class BinaryOp >
OutputIt transform( InputIt1 first1, InputIt1 last1, InputIt2 first2,
                    OutputIt d_first, BinaryOp binary_op );

(4)
template< class ExecutionPolicy,
          class ForwardIt1, class ForwardIt2,
          class ForwardIt3, class BinaryOp >
ForwardIt3 transform( ExecutionPolicy&& policy,
                      ForwardIt1 first1, ForwardIt1 last1,
                      ForwardIt2 first2,
                      ForwardIt3 d_first, BinaryOp binary_op );
```

std::transform applies the given function to the elements of the given input range(s), and stores the result in an output range starting from d_first.

transform 使用 给定的函数 调用 给定的范围每个元素。并存储结果到 d_first 开始的容器

1) The unary operation unary_op is applied to the elements of [first1, last1).

一元操作 unary_op 用于 [first, last1)的元素

 If unary_op invalidates an iterator or modifies an element in any of the following ranges, the behavior is undefined:

如果unary_op 是 iterator 无效，或者修改元素，这种行为是未定义的。

[first1, last1].

The range of std::distance(first1, last1) + 1 elements starting from d_first.


3) The binary operation binary_op is applied to pairs of elements from two ranges: [first1, last1) and another range of std::distance(first1, last1) elements starting from first2.
 If binary_op invalidates an iterator or modifies an element in any of the following ranges, the behavior is undefined:

二元操作 binary_op 被用于 pairs 元素，pairs一个来自 [first, last1), 另一个来自 从 first2 开始的 

[first1, last1].
The range of std::distance(first1, last1) + 1 elements starting from first2.
The range of std::distance(first1, last1) + 1 elements starting from d_first.

## 可能的实现

```cc
template<class InputIt, class OutputIt, class UnaryOp>
constexpr //< since C++20
OutputIt transform(InputIt first1, InputIt last1,
                   OutputIt d_first, UnaryOp unary_op)
{
    for (; first1 != last1; ++d_first, ++first1)
        *d_first = unary_op(*first1);
 
    return d_first;
}
```

```cc
template<class InputIt1, class InputIt2, 
         class OutputIt, class BinaryOp>
constexpr //< since C++20
OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                   OutputIt d_first, BinaryOp binary_op)
{
    for (; first1 != last1; ++d_first, ++first1, ++first2)
        *d_first = binary_op(*first1, *first2);
 
    return d_first;
}
```

## 注意
std::transform does not guarantee in-order application of unary_op or binary_op. 

transform 不保证顺序应用 unary_op 或 binary_op

To apply a function to a sequence in-order or to apply a function that modifies the elements of a sequence, use std::for_each.

要按顺序应用函数 对一个序列，修改序列的元素，使用 for_each

```cc
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
 
void print_ordinals(const std::vector<unsigned>& ordinals)
{
    std::cout << "ordinals: ";
    for (unsigned ord : ordinals)
        std::cout << std::setw(3) << ord << ' ';
    std::cout << '\n';
}
 
char to_uppercase(unsigned char c)
{
    return std::toupper(c);
}
 
void to_uppercase_inplace(char& c)
{
    c = to_uppercase(c);
}
 
void unary_transform_example(std::string& hello, std::string world)
{
    // Transform string to uppercase in-place
 
    std::transform(hello.cbegin(), hello.cend(), hello.begin(), to_uppercase);
    std::cout << "hello = " << std::quoted(hello) << '\n';
 
    // for_each version (see Notes above)
    std::for_each(world.begin(), world.end(), to_uppercase_inplace);
    std::cout << "world = " << std::quoted(world) << '\n';
}
 
void binary_transform_example(std::vector<unsigned> ordinals)
{
    // Transform numbers to doubled values
 
    print_ordinals(ordinals);
 
    std::transform(ordinals.cbegin(), ordinals.cend(), ordinals.cbegin(),
                   ordinals.begin(), std::plus<>{});
 
    print_ordinals(ordinals);
}
 
int main()
{
    std::string hello("hello");
    unary_transform_example(hello, "world");
 
    std::vector<unsigned> ordinals;
    std::copy(hello.cbegin(), hello.cend(), std::back_inserter(ordinals));
    binary_transform_example(std::move(ordinals));
}
```

输出
```
hello = "HELLO"
world = "WORLD"
ordinals:  72  69  76  76  79 
ordinals: 144 138 152 152 158
```

# partition

(1)
template< class ForwardIt, class UnaryPred >
ForwardIt partition( ForwardIt first, ForwardIt last, UnaryPred p );

(2)
template< class ExecutionPolicy, class ForwardIt, class UnaryPred >
ForwardIt partition( ExecutionPolicy&& policy,
                     ForwardIt first, ForwardIt last, UnaryPred p );

1) Reorders the elements in the range [first, last) in such a way that all elements for 

重新排序元素，

which the predicate p returns true precede all elements for which predicate p returns false. Relative order of the elements is not preserved.

使谓词返回为true的元素在所有谓词返回为false的元素前面，

元素相对顺序不保留

## 可能的实现
```cc
template<class ForwardIt, class UnaryPred>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPred p)
{
    first = std::find_if_not(first, last, p);
    if (first == last)
        return first;
 
    for (auto i = std::next(first); i != last; ++i)
        if (p(*i))
        {
            std::iter_swap(i, first);
            ++first;
        }
 
    return first;
}
```

## 示例
```cc
#include <algorithm>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <vector>
 
template<class ForwardIt>
void quicksort(ForwardIt first, ForwardIt last)
{
    if (first == last)
        return;
 
    auto pivot = *std::next(first, std::distance(first, last) / 2);
    auto middle1 = std::partition(first, last, [pivot](const auto& em)
    {
        return em < pivot;
    });
    auto middle2 = std::partition(middle1, last, [pivot](const auto& em)
    {
        return !(pivot < em);
    });
 
    quicksort(first, middle1);
    quicksort(middle2, last);
}
 
int main()
{
    std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "Original vector: ";
    for (int elem : v)
        std::cout << elem << ' ';
 
    auto it = std::partition(v.begin(), v.end(), [](int i) {return i % 2 == 0;});
 
    std::cout << "\nPartitioned vector: ";
    std::copy(std::begin(v), it, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "* ";
    std::copy(it, std::end(v), std::ostream_iterator<int>(std::cout, " "));
 
    std::forward_list<int> fl {1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92};
    std::cout << "\nUnsorted list: ";
    for (int n : fl)
        std::cout << n << ' ';
 
    quicksort(std::begin(fl), std::end(fl));
    std::cout << "\nSorted using quicksort: ";
    for (int fi : fl)
        std::cout << fi << ' ';
    std::cout << '\n';
}
```

# next distance
## next
```cc
template< class InputIt >
InputIt next( InputIt it, typename std::iterator_traits<InputIt>::difference_type n = 1 );

template< class InputIt >
constexpr
InputIt next( InputIt it, typename std::iterator_traits<InputIt>::difference_type n = 1 );
```

Return the nth successor (or -nth predecessor if n is negative) of iterator it.

返回迭代器 it 的第n个后续，如果 n为负值，则返回第n 个前续

### 可能的实现 

```cc
template<class InputIt>
constexpr // since C++17
InputIt next(InputIt it, typename std::iterator_traits<InputIt>::difference_type n = 1)
{
    std::advance(it, n);
    return it;
}
```

### 注意
Although the expression ++c.begin() often compiles, it is not guaranteed to do so: c.begin() is an rvalue expression, 

虽然 `++c.begin()` 常常可以编译，但不保证 `c.begin()` 返回一个右值，

and there is no LegacyInputIterator requirement that specifies that increment of an rvalue is guaranteed to work. 

并且 LegacyInputIterator 没有要求 右值的增加操作保证能生效，

In particular, when iterators are implemented as pointers or its operator++ is lvalue-ref-qualified, ++c.begin() does not compile, while std::next(c.begin()) does.

具体而言，当 iterator 被实现为指针或 operator++ 是左值引用限定时， `++c.begin()` 不能编译，但 `std::next(c.begin())` 可以


### 示例
```cc
#include <iostream>
#include <iterator>
#include <vector>
 
int main()
{
    std::vector<int> v{4, 5, 6};
 
    auto it = v.begin();
    auto nx = std::next(it, 2);
    std::cout << *it << ' ' << *nx << '\n';
 
    it = v.end();
    nx = std::next(it, -2);
    std::cout << ' ' << *nx << '\n';
}
```

输出
```
4 6
 5
```

## distance
```cc
template< class InputIt >
typename std::iterator_traits<InputIt>::difference_type
    distance( InputIt first, InputIt last );
```
Returns the number of hops from first to last.

返回 first 到 last 的跳跃数

If InputIt is not LegacyRandomAccessIterator, the behavior is undefined if last is not reachable from first.

If InputIt is LegacyRandomAccessIterator, the behavior is undefined if first and last are neither reachable from each other.

### 可能的实现
```cc
namespace detail
{
    template<class It>
    constexpr // required since C++17
    typename std::iterator_traits<It>::difference_type 
        do_distance(It first, It last, std::input_iterator_tag)
    {
        typename std::iterator_traits<It>::difference_type result = 0;
        while (first != last)
        {
            ++first;
            ++result;
        }
        return result;
    }
 
    template<class It>
    constexpr // required since C++17
    typename std::iterator_traits<It>::difference_type 
        do_distance(It first, It last, std::random_access_iterator_tag)
    {
        return last - first;
    }
} // namespace detail
 
template<class It>
constexpr // since C++17
typename std::iterator_traits<It>::difference_type 
    distance(It first, It last)
{
    return detail::do_distance(first, last,
                               typename std::iterator_traits<It>::iterator_category());
}
```

### 示例
```cc
#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{3, 1, 4};
    std::cout << "distance(first, last) = "
              << std::distance(v.begin(), v.end()) << '\n'
              << "distance(last, first) = "
              << std::distance(v.end(), v.begin()) << '\n';
              // the behavior is undefined (until LWG940)
 
    static constexpr auto il = {3, 1, 4};
    // Since C++17 `distance` can be used in constexpr context.
    static_assert(std::distance(il.begin(), il.end()) == 3);
    static_assert(std::distance(il.end(), il.begin()) == -3);
}
```

输出
```
distance(first, last) = 3
distance(last, first) = -3
```

# bind
(1)
template< class F, class... Args >
/* unspecified */ bind( F&& f, Args&&... args );
template< class F, class... Args >
constexpr /* unspecified */ bind( F&& f, Args&&... args );

(2)	
template< class R, class F, class... Args >
/* unspecified */ bind( F&& f, Args&&... args );
template< class R, class F, class... Args >
constexpr /* unspecified */ bind( F&& f, Args&&... args );

The function template std::bind generates a forwarding call wrapper for f. 

函数模板bind 为 f 生成一个转发调用包装器，

Calling this wrapper is equivalent to invoking f with some of its arguments bound to args.

调用这个包装器相当于调用 使用一些参数绑定到 f 后调用 f

## Parameters
f : Callable object (function object, pointer to function, reference to function, pointer to member function, or pointer to data member) that will be bound to some arguments

f 可调用的对象（函数对象，函数指针，函数引用，成员函数指针，成员数据指针）会被绑定一些参数

args : list of arguments to bind, with the unbound arguments replaced by the placeholders _1, _2, _3... of namespace std::placeholders

一系列参数用于绑定，使用占位符替换不绑定参数

## Return value
A function object g of unspecified type T, for which std::is_bind_expression<T>::value is true. It has the following members:

未指定类型的函数对象 g , 有下列成员

Member function operator()
When g is invoked in a function call expression g(u1, u2, ... uM), an invocation of the stored object takes place, as if by

当使用表达式 g(u1, u2, ... uM) 会调用 g 的 operator() , 并使用存储的对象替换位置, 过程类似于

1) INVOKE(fd, std::forward<V1>(v1), std::forward<V2>(v2), ..., std::forward<VN>(vN)), or
2) INVOKE<R>(fd, std::forward<V1>(v1), std::forward<V2>(v2), ..., std::forward<VN>(vN)),

where fd is a value of type std::decay<F>::type, the values and types of the bound arguments v1, v2, ..., vN are determined as specified below.

fd 是类型为 decay<F>::type 的值，绑定参数 v1, v2 .. 的类型和值按照下面方式确定 ：

If some of the arguments that are supplied in the call to g() are not matched by any placeholders stored in g, the unused arguments are evaluated and discarded.

如果一些实参没有被匹配到 存储在 g 中的占位符 ， 这些没有使用的参数将被计算和丢弃

### Bound arguments

For each stored argument arg_i, the corresponding bound argument v_i in the INVOKE or INVOKE<R> operation is determined as follows:

被存储的参数称为 arg_i,  : bind(f, arg_1, arg_2, ..)

在内部调用的参数称为 v_i : f(v_1, v_2 ...)

g(u1, u2, u3 ..) 被调用时，参数为 u1, u2 ...

Case 1: reference wrappers
If arg_i is of type std::reference_wrapper<T> (for example, std::ref or std::cref was used in the initial call to std::bind), 

如果存储的类型是 reference_wrapper，如在调用 bind时使用 std::ref

then v_i is arg_i.get() and its type V_i is T&: the stored argument is passed by reference into the invoked function object.

那么 v_i 等于 arg_i.get() , 并且 v_i 的类型是 T& , 那么存储参数将作为外部某对象的引用，传递到函数对象

Case 2: bind expressions
If arg_i is of type T for which std::is_bind_expression<T>::value is true (for example, another std::bind expression was passed directly into the initial call to std::bind), 

如果存储的是表达式 is_bind_expression<T>，比如使用子bind 做实参调用 bind.

then std::bind performs function composition: instead of passing the function object that the bind subexpression would return, 

那么bind执行函数组合：不传递bind子表达式返回的结果，

the subexpression is invoked eagerly, and its return value is passed to the outer invokable object. 

而是将子表达式本身传递，并在之后被执行后，将返回值传递给外层可调用对象

If the bind subexpression has any placeholder arguments, they are shared with the outer bind (picked out of u1, u2, ...). 

如果bind子表达式有任何占位符参数，他们会共享外部bind的占位符, 从 u1, u2 获得值

Case 3: placeholders
If arg_i is of type T, for which std::is_placeholder<T>::value is not 0 (meaning, a placeholder such as std::placeholders::_1, _2, _3, ... was 

如果 arg_i 是占位符，如 _1, _2 

used as the argument to the initial call to std::bind), then the argument indicated by the placeholder (u1 for _1, u2 for _2, etc) 

那么 u1 u2 通过占位符表示 u1 为 _1 , u2 为 _2

Case 4: ordinary arguments
Otherwise, arg_i is passed to the invokable object as lvalue argument: v_i is simply arg_i and its type V_i is T cv ﻿&, where cv is the same cv-qualification as that of g.

否则，arg_i 作为左值参数传递给可调用对象：v_i 就是简单的 arg_i，其类型 V_i 是 T cv &，其中 cv 与 g 的cv 限定一样。

### 示例

#include <functional>
#include <iostream>
#include <memory>
#include <random>
 
void f(int n1, int n2, int n3, const int& n4, int n5)
{
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}
 
int g(int n1)
{
    return n1;
}
 
struct Foo
{
    void print_sum(int n1, int n2)
    {
        std::cout << n1 + n2 << '\n';
    }
 
    int data = 10;
};
 
int main()
{
    using namespace std::placeholders;  // for _1, _2, _3...
 
    std::cout << "1) argument reordering and pass-by-reference: ";
    int n = 7;
    // (_1 and _2 are from std::placeholders, and represent future
    // arguments that will be passed to f1)
    auto f1 = std::bind(f, _2, 42, _1, std::cref(n), n);
    n = 10;
    f1(1, 2, 1001); // 1 is bound by _1, 2 is bound by _2, 1001 is unused
                    // makes a call to f(2, 42, 1, n, 7)
 
    std::cout << "2) achieving the same effect using a lambda: ";
    n = 7;
    auto lambda = [&ncref = n, n](auto a, auto b, auto /*unused*/)
    {
        f(b, 42, a, ncref, n);
    };
    n = 10;
    lambda(1, 2, 1001); // same as a call to f1(1, 2, 1001)
 
    std::cout << "3) nested(嵌套) bind subexpressions share the placeholders: ";
    auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
    f2(10, 11, 12); // makes a call to f(12, g(12), 12, 4, 5);
 
    std::cout << "4) bind a RNG with a distribution: ";
    std::default_random_engine e;
    std::uniform_int_distribution<> d(0, 10);
    auto rnd = std::bind(d, e); // a copy of e is stored in rnd
    for (int n = 0; n < 10; ++n)
        std::cout << rnd() << ' ';
    std::cout << '\n';
 
    std::cout << "5) bind to a pointer to member function: ";
    Foo foo;
    auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1); // 成员函数，需要传递 this
    f3(5);
 
    std::cout << "6) bind to a mem_fn that is a pointer to member function: ";
    auto ptr_to_print_sum = std::mem_fn(&Foo::print_sum);
    auto f4 = std::bind(ptr_to_print_sum, &foo, 95, _1);
    f4(5);
 
    std::cout << "7) bind to a pointer to data member: ";
    auto f5 = std::bind(&Foo::data, _1);
    std::cout << f5(foo) << '\n';
 
    std::cout << "8) bind to a mem_fn that is a pointer to data member: ";
    auto ptr_to_data = std::mem_fn(&Foo::data);
    auto f6 = std::bind(ptr_to_data, _1);
    std::cout << f6(foo) << '\n';
 
    std::cout << "9) use smart pointers to call members of the referenced objects: ";
    std::cout << f6(std::make_shared<Foo>(foo)) << ' '
              << f6(std::make_unique<Foo>(foo)) << '\n';
}


