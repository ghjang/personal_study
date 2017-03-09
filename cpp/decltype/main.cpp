// refer to http://en.cppreference.com/w/cpp/language/decltype

#include <type_traits>
#include <iostream>

// declaration only
int f(int);
int g();

// with definition
int h() { return 0; }


struct CompleteType { };

struct IncompleteType;

// declaration only
template <typename T>
int doSomething(T const& t);

CompleteType returnCompleteType();
IncompleteType returnIncompleteType();


struct Default
{
    int foo() const { return 1; }
};

struct NonDefault
{
    NonDefault(NonDefault const&) { }
    long foo() const { return 1; }
};

template <typename T>
using ReturnTypeOfFoo = decltype(std::declval<T>().foo());


int main() {
    using std::is_same;

    int i = 1024;

    decltype(i) j = i * i;
    static_assert(is_same<int, decltype(i)>::value, "");

    using i_t = decltype(i);
    static_assert(is_same<int, i_t>::value, "");
    i_t k = j * j;

    // with CLion 1.1 on OS X El Capitan
    std::cout << "i: " << i << std::endl;   // 1024
    std::cout << "j: " << j << std::endl;   // 1048576
    std::cout << "k: " << k << std::endl;   // 0    <== THINK: how to detect something like this?

    static_assert(is_same<int, decltype(1 + 1)>::value, "");

    // string literal is a lvalue.
    // "abc"'s type is char const [4].
    char const str[4] = "abc";
    char const (* pStr) [4] = &"abc";   // can get the address of the string.
    char const * pStr1 = "abc";         // array to pointer decay
    char const * pStr2 = str;           // array to pointer decay
    //char const (* pStr3) [4] = str;   // this is a compile error
    char const (* pStr4) [4] = &str;    // but this works OK.

    static_assert(std::is_same<char const (&) [4], decltype("abc")>::value, "");

    int x = 100;
    static_assert(std::is_same<int, decltype(x)>::value, "");       // decltype(x)
    static_assert(std::is_same<int &, decltype((x))>::value, "");   // decltype((x))

    // it's ok.
    static_assert(is_same<int, decltype(f(0))>::value, "");
    static_assert(is_same<int, decltype(g())>::value, "");
    static_assert(is_same<int, decltype(h())>::value, "");

    // it's also ok.
    static_assert(is_same<int, decltype(f(g()))>::value, "");
    static_assert(is_same<int, decltype(f(h()))>::value, "");

    // it's ok.
    static_assert(is_same<int, decltype(doSomething(CompleteType()))>::value, "");

    // but it's not ok. it's compile-time errors.
    //decltype(doSomething(IncompleteType())) it;
    //static_assert(is_same<int, decltype(doSomething(IncompleteType()))>::value, "");

    // it's ok
    static_assert(is_same<int, decltype(doSomething(returnCompleteType()))>::value, "");

    // but it's not ok. it's compile-time errors.
    //static_assert(is_same<int, decltype(doSomething(returnIncompleteType()))>::value, "");

    // it's ok.
    static_assert(is_same<int, decltype(Default().foo())>::value, "");
    static_assert(is_same<int, ReturnTypeOfFoo<Default>>::value, "");
    static_assert(is_same<long, ReturnTypeOfFoo<NonDefault>>::value, "");

    // but it's not ok. a compile error.
    //static_assert(is_same<long, decltype(NonDefault().foo())>::value, "");

    return 0;
}

