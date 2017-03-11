#include <type_traits>
#include <initializer_list>
#include <vector>
#include <iostream>


template <typename T>
void print(std::initializer_list<T> const& l)
{
    for (T const& e: l) {
        std::cout << e << std::endl;
    }
}


template <typename T>
struct Container
{
    Container(std::initializer_list<T> const& l)
           : data_(l)
    { }

    void add(std::initializer_list<T> const& l)
    {
        data_.insert(data_.end(), l.begin(), l.end());
    }

    std::vector<T> data_;
};


int main() {
    using std::is_same;
    using std::initializer_list;
    using std::cout;
    using std::endl;

    // compile error. This is not a valid expression. It's just a kind of comma-separated integers with braces, which is not valid.
    //{ 1, 2, 3 };

    // compile error, 'expected expression'.
    //decltype({ 1, 2, 3 });

    // the list is treated as an initializer list in this auto context.
    auto ints = { 1, 2, 3 };
    static_assert(is_same<decltype(ints), initializer_list<decltype(1)>>::value, "");
    static_assert(is_same<decltype(ints), initializer_list<int>>::value, "");
    for (auto i: ints) {
        cout << i << endl;
    }

    // the list is treated as an initializer list in this auto context.
    for (auto i: { 4, 5, 6 }) {
        cout << i << endl;
    }

    // compile error. 'can't deduce the type for the initializer_list.'.
    //auto mixed = { 7, 8, 9.0 };

    print({ 7, 8, 9 });

    cout << "---" << endl;

    Container<int> c{ 10, 11, 12 };
    c.add({ 13, 14, 15 });
    for (auto i: c.data_) {
        cout << i << endl;
    }

    return 0;
}

