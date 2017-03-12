#include <type_traits>
#include <tuple>
#include <cassert>
#include <iostream>


namespace Detail
{
    template
    <
            typename T, std::size_t... i,
            typename U, std::size_t... j
    >
    auto binary_tuple_cat(T && a, std::index_sequence<i...>,
                          U && b, std::index_sequence<j...>)
    {
        return std::make_tuple(
                std::get<i>(std::forward<T>(a))...,
                std::get<j>(std::forward<U>(b))...
        );
    }

    struct BinaryTupleCat
    {
        template <typename T, typename U>
        auto operator () (T && a, U && b) const
        {
            constexpr auto aSize = std::tuple_size<std::decay_t<T>>::value;
            constexpr auto bSize = std::tuple_size<std::decay_t<U>>::value;
            return binary_tuple_cat(
                    std::forward<T>(a),
                    std::make_index_sequence<aSize>{},
                    std::forward<U>(b),
                    std::make_index_sequence<bSize>{}
            );
        }
    };
} // namespace Detail


//#define TAKE_1
//#define TAKE_2
#define TAKE_3

#if defined(TAKE_1)

auto tuple_cat_()
{
    return std::make_tuple();
}

template <typename T>
auto tuple_cat_(T && a)
{
    return a;
}

template <typename T, typename U>
auto tuple_cat_(T && a, U && b)
{
    constexpr auto aSize = std::tuple_size<std::decay_t<T>>::value;
    constexpr auto bSize = std::tuple_size<std::decay_t<U>>::value;
    return Detail::binary_tuple_cat(
            std::forward<T>(a),
            std::make_index_sequence<aSize>{},
            std::forward<U>(b),
            std::make_index_sequence<bSize>{}
    );
}

template <typename T, typename... R>
auto tuple_cat_(T && a, R &&... rs)
{
    return tuple_cat_(
            std::forward<T>(a),
            tuple_cat_(std::forward<R>(rs)...)
    );
}

#elif defined(TAKE_2)

template <typename F, typename T, typename U>
auto fold_right(F && f, T && init, U && last)
{
    return f(std::forward<U>(last), std::forward<T>(init));
}

template <typename F, typename T, typename U, typename... R>
auto fold_right(F && f, T && init, U && first, R &&... rs)
{
    return f(
            std::forward<U>(first),
            fold_right(
                    std::forward<F>(f),
                    std::forward<T>(init),
                    std::forward<R>(rs)...
            )
    );
}


auto tuple_cat_()
{
    return std::make_tuple();
}

template <typename... T>
auto tuple_cat_(T &&... ts)
{
    return fold_right(
            Detail::BinaryTupleCat{},
            std::make_tuple(), // empty tuple for init.
            std::forward<T>(ts)...
    );
}

#elif defined(TAKE_3)

template <typename T, typename F, bool isRvalueArg>
struct ArgWrap;

template <typename T, typename F>
struct ArgWrap<T, F, true>
{
    template <typename U>
    auto operator + (ArgWrap<U, F, true> && rhs) const
    {
        using result_t = decltype(F{}(std::move(m_), std::move(rhs.m_)));
        return ArgWrap<result_t, F, true>{ F{}(std::move(m_), std::move(rhs.m_)) };
    }

    template <typename U>
    auto operator + (ArgWrap<U, F, false> && rhs) const
    {
        using result_t = decltype(F{}(std::move(m_), rhs.m_));
        return ArgWrap<result_t, F, true>{ F{}(std::move(m_), rhs.m_) };
    }

    mutable T m_;
};

template <typename T, typename F>
struct ArgWrap<T, F, false>
{
    template <typename U>
    auto operator + (ArgWrap<U, F, true> && rhs) const
    {
        using result_t = decltype(F{}(m_, std::move(rhs.m_)));
        return ArgWrap<result_t, F, true>{ F{}(m_, std::move(rhs.m_)) };
    }

    template <typename U>
    auto operator + (ArgWrap<U, F, false> && rhs) const
    {
        using result_t = decltype(F{}(m_, rhs.m_));
        return ArgWrap<result_t, F, true>{ F{}(m_, rhs.m_) };
    }

    T const& m_;
};

template <typename F, typename... T>
auto fold_right_impl(T &&... xs)
{
    auto r = (
        ...
        + ArgWrap<
                std::decay_t<T>,
                F,
                std::is_rvalue_reference<decltype(xs)>::value
            >{ std::forward<T>(xs) }
    );
    return std::move(r.m_);
}

template <typename F, typename T, typename... R>
auto fold_right(T && init, R &&... rs)
{
    return fold_right_impl<F>(
            std::forward<R>(rs)...,
            std::forward<T>(init)   // append to the right-most position.
    );
}

auto tuple_cat_()
{
    return std::make_tuple();
}

template <typename... T>
auto tuple_cat_(T &&... ts)
{
    return fold_right<Detail::BinaryTupleCat>(
            std::make_tuple(), // init for fold_right
            std::forward<T>(ts)...
    );
}

#endif


int main()
{
    using std::is_same;
    using std::tuple;
    using std::make_tuple;
    using std::tuple_size;
    using std::tuple_element_t;

    auto a = make_tuple(1, 1.0, 'c');
    auto b = make_tuple("abc", 1.0f, 2.0);

    // NOTE: std::tuple_cat will be found by ADL.
    //auto t = tuple_cat(a, b);

    auto t = tuple_cat_(a, b);
    auto t1 = tuple_cat_(a, make_tuple('d', 1, 'f'), b);

    static_assert(tuple_size<decltype(t)>() == 6, "");
    static_assert(tuple_size<decltype(t1)>() == 9, "");
    static_assert(is_same<float, tuple_element_t<4, decltype(t)>>(), "");
    static_assert(is_same<double, tuple_element_t<5, decltype(t)>>(), "");
    static_assert(is_same<char, tuple_element_t<3, decltype(t1)>>(), "");
    static_assert(is_same<char, tuple_element_t<5, decltype(t1)>>(), "");
    static_assert(is_same<float, tuple_element_t<7, decltype(t1)>>(), "");

    assert(std::get<4>(t) == 1.0f);
    assert(std::get<5>(t) == 2.0);
    assert(std::get<3>(t1) == 'd');
    assert(std::get<8>(t1) == 2.0);

    return 0;
}

