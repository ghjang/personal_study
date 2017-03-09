#include <type_traits>
#include <cassert>
#include <iostream>


template <typename T>
T func(T t);


// template type deduction rule is applied for the parameter.
template <typename T>
auto ReturnDecayedValue(T t)
{
    return t;   // template type deduction rule(auto) is applied for the return type.
}

// template type deduction rule is applied for the parameter.
template <typename T>
auto ReturnDecayedValue1(T t) -> decltype(t)
{
    return t;   // decltype deduction rule is applied for the return type.
}

// template type deduction rule is applied for the parameter.
template <typename T>
decltype(auto) ReturnDecayedValue2(T t) // C++14 decltype(auto)
{
    return t;   // decltype deduction rule is applied for the return type.
}


template <typename T>
auto ReturnDecayedValue3(T & t)
{
    return t;   // template type deduction rule(auto) is applied for the return type.
}

template <typename T>
auto ReturnDecayedValue4(T & t) -> decltype(t)
{
    return t;   // decltype deduction rule is applied for the return type.
}

template <typename T>
decltype(auto) ReturnDecayedValue5(T & t)   // C++14 decltype(auto)
{
    return t;   // decltype deduction rule is applied for the return type.
}


int f(int i) { return i + 1; }


int main() {
    using std::is_same;
    using std::is_array;
    using std::remove_reference;
    using std::decay;   // C++11
    using std::decay_t; // C++14

    int i = 100;
    int & ri = i;
    int const j = 200;
    int const volatile k = 300;

    static_assert(is_same<int, decltype(func(i))>::value, "");
    static_assert(is_same<int, decltype(func(ri))>::value, "");
    static_assert(is_same<int, decltype(func(j))>::value, "");
    static_assert(is_same<int, decltype(func(k))>::value, "");

    // int array to pointer decay
    int a[3] = { 1, 2, 3 };
    int * pa = a;
    static_assert(is_same<decltype(a), int[3]>::value, "");
    static_assert(is_same<decltype(pa), int *>::value, "");
    static_assert(is_same<decltype(pa), decay<decltype(a)>::type>::value, "");
    static_assert(is_same<decltype(pa), decay_t<decltype(a)>>::value, "");

    // multi-dimensional array to pointer decay
    int aa[2][3] = {
            { 1, 2, 3 },
            { 4, 5, 6 }
    };
    int (* paa) [3] = aa; // loses top-level dimension size information, 2.
    static_assert(is_same<decltype(aa), int [2][3]>::value, "");
    static_assert(is_same<decltype(paa), int (*) [3]>::value, ""); // pointer to 'int [3]'
    paa[1][0] = 44;
    assert(aa[1][0] == 44);

    // const char array to pointer decay

    {
        using abc_t = decltype("abc");
        abc_t c = "abc";
        char const * pc = c;

        static_assert(is_same<decltype("abc"), char const (&) [4]>::value, ""); // reference to 'char const [4]'
        static_assert(is_same<abc_t, char const (&) [4]>::value, "");
        static_assert(is_array<remove_reference<abc_t>::type>::value, "");

        static_assert(is_same<decltype(pc), decay<abc_t>::type>::value, "");
        static_assert(is_same<decltype(pc), decay_t<abc_t>>::value, "");
    }

    {
        char const c[] = "abc";
        char const * pc = c;
        static_assert(is_same<decltype(c), char const [4]>::value, "");
        static_assert(is_same<decltype(pc), decay<decltype(c)>::type>::value, "");
        static_assert(is_same<decltype(pc), decay_t<decltype(c)>>::value, "");

        // const can be removed at this context.
        char c1[] = "defg";
        static_assert(is_same<decltype(c1), char [5]>::value, "");
    }

    // function-to-pointer decay
    auto pf = f;
    int (&rf) (int) = f;
    int (*pf1) (int) = f;
    static_assert(is_same<int (int), decltype(f)>::value, "");                  // function type
    static_assert(is_same<int (&) (int), decltype(rf)>::value, "");             // function reference type
    static_assert(is_same<int (*) (int), decltype(pf)>::value, "");             // function pointer type
    static_assert(is_same<int (*) (int), decay<decltype(f)>::type>::value, "");
    static_assert(is_same<int (*) (int), decay_t<decltype(f)>>::value, "");

    static_assert(is_same<int *, decltype(ReturnDecayedValue(a))>::value, "");
    static_assert(is_same<int (*) [3], decltype(ReturnDecayedValue(aa))>::value, "");
    static_assert(is_same<int (*) (int), decltype(ReturnDecayedValue(f))>::value, "");

    static_assert(is_same<int *, decltype(ReturnDecayedValue1(a))>::value, "");
    static_assert(is_same<int (*) [3], decltype(ReturnDecayedValue1(aa))>::value, "");
    static_assert(is_same<int (*) (int), decltype(ReturnDecayedValue1(f))>::value, "");

    static_assert(is_same<int *, decltype(ReturnDecayedValue2(a))>::value, "");
    static_assert(is_same<int (*) [3], decltype(ReturnDecayedValue2(aa))>::value, "");
    static_assert(is_same<int (*) (int), decltype(ReturnDecayedValue2(f))>::value, "");

    // 
    static_assert(is_same<int *, decltype(ReturnDecayedValue1(a))>::value, "");
    static_assert(is_same<int (*) [3], decltype(ReturnDecayedValue1(aa))>::value, "");
    static_assert(is_same<int (*) (int), decltype(ReturnDecayedValue1(f))>::value, "");

    static_assert(is_same<int (&) [3], decltype(ReturnDecayedValue4(a))>::value, "");       // reference to 'int [3]'
    static_assert(is_same<int (&) [2][3], decltype(ReturnDecayedValue4(aa))>::value, "");   // reference to 'int [2][3]'
    static_assert(is_same<int (&) (int), decltype(ReturnDecayedValue4(f))>::value, "");     // reference to 'int (int)'

    static_assert(is_same<int (&) [3], decltype(ReturnDecayedValue5(a))>::value, "");       // reference to 'int [3]'
    static_assert(is_same<int (&) [2][3], decltype(ReturnDecayedValue5(aa))>::value, "");   // reference to 'int [2][3]'
    static_assert(is_same<int (&) (int), decltype(ReturnDecayedValue5(f))>::value, "");     // reference to 'int (int)'

    return 0;
}

