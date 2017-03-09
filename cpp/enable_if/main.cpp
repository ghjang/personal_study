#include <type_traits>
#include <vector>
#include <list>
#include <iostream>


template <
        typename Container,
        typename = std::enable_if_t<
                            std::is_same<
                                    std::random_access_iterator_tag,
                                    typename std::iterator_traits<typename Container::iterator>::iterator_category
                            >::value
                    >
>
auto medianValue(Container const& c)
{
    return c[c.size() / 2];
}

template <
        typename Container,
        typename = void,
        typename = std::enable_if_t<
                            std::is_base_of<
                                    std::input_iterator_tag,
                                    typename std::iterator_traits<typename Container::iterator>::iterator_category
                            >::value
                                && !std::is_same<
                                        std::random_access_iterator_tag,
                                        typename std::iterator_traits<typename Container::iterator>::iterator_category
                                    >::value
                    >
>
auto medianValue(Container const& c)
{
    auto iter = c.begin();
    std::advance(iter, c.size() / 2);
    return *iter;
}


template <typename T, typename = void>
struct Actor
{
    void doSomething()
    {
        std::cout << "did some work." << std::endl;
    }
};

template <typename T>
struct Actor<T, std::enable_if_t<std::is_integral<T>::value>>
{
    void doSomething()
    {
        std::cout << "did some work for integral type." << std::endl;
    }
};

template <typename T>
struct Actor<T, std::enable_if_t<std::is_floating_point<T>::value>>
{
    void doSomething()
    {
        std::cout << "did some work for floating point type." << std::endl;
    }
};


int main() {
    using std::vector;
    using std::list;
    using std::cout;
    using std::string;

    vector<int> v = { 1, 2, 3, 4, 5 };
    auto vRetVal = medianValue(v);
    cout << "vRetVal: " << vRetVal << std::endl; // vRetVal: 3

    list<char> l = { 'a', 'b', 'c', 'd', 'e' };
    auto lRetVal = medianValue(l);
    cout << "lRetVal: " << lRetVal << std::endl; // lRetVal: c

    Actor<string> as;
    as.doSomething(); // 'did some work.'

    Actor<int> ai;
    ai.doSomething(); // 'did some work for integral type.'

    Actor<double> ad;
    ad.doSomething(); // 'did some work for floating point type.'

    return 0;
}

