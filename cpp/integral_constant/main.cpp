// refer to http://en.cppreference.com/w/cpp/types/integral_constant

#include <type_traits>
#include <cassert>
#include <iostream>

#include <gsl.h>


template <typename T, int N>
void doSomething(T t, std::integral_constant<int, N>)
{
    std::cout << "doSomething(T t, std::integral_constant<int, N>) is called: " << N << std::endl;
};

template <typename T>
void doSomething(T t, std::integral_constant<int, 2>)
{
    std::cout << "doSomething(T t, std::integral_constant<int, 2>) is called." << std::endl;
};


int main() {
    using std::is_same;
    using std::true_type;
    using std::false_type;
    using std::integral_constant;

    // for C++11
    static_assert(is_same<integral_constant<bool, true>, true_type>::value, "");
    static_assert(is_same<integral_constant<bool, false>, false_type>::value, "");

    {
        integral_constant<int, 5> ic;

        int val = ic;
        assert(ic.value == val);

        // since C++14
        int val1 = ic();
        assert(ic.value == val1);
    }

    {
        static_assert(integral_constant<int, 5>::value == 5, "");
        static_assert(integral_constant<int, 5 + 5>::value == 10, "");

        using five_t = integral_constant<int, 5>;
        using another_five_t = integral_constant<int, 2 + 3>;
        static_assert(is_same<five_t, another_five_t>::value, "");
    }

    {
        enum class Note : std::uint8_t {
            C = 0,
            D,
            E
        };

        Note n = Note::C;

        // syntax errors
        //++n;
        //n + 1;
        //Note::C + Note::D;
        //Note::C + 1;
        //n = 3;
        //uint8_t u8 = n;

        using note_c_t = integral_constant<Note, Note::C>;

        // syntax errors
        //using another_note_c_t = integral_constant<Note, 0>;
        //using another_note_c_t = integral_constant<Note, uint8_t(0)>;

        using another_note_c_t = integral_constant<Note, Note(0)>;
        using note_d_t = integral_constant<Note, Note(1)>;
        using note_e_t = integral_constant<Note, Note(2)>;
        using note_f_t = integral_constant<Note, Note(3)>; // out of range

        note_f_t f;

        // syntax error. can't output Note to stdio.
        //std::cout << f() << std::endl;

        static_assert(static_cast<int>(f()) == 3, "");
        static_assert(is_same<note_c_t, another_note_c_t>::value, "");
        static_assert(!is_same<note_c_t, note_f_t>::value, "");

        n = Note::C;
        assert(n == note_c_t::value);
        n = Note::D;
        assert(n != note_c_t::value);

        // Ooops! this is possible.
        n = f();
        std::cout << static_cast<int>(n) << std::endl; // 3

        // syntax error
        //Note m(4);

        // Ooops! this is also possible.
        Note m = Note(4);
        n = m;
        std::cout << static_cast<int>(n) << std::endl; // 4
    }

    // function overloading by integral_constant
    {
        struct s { };
        doSomething(s(), integral_constant<int, 0>());
        doSomething(s(), integral_constant<int, 1>());
        doSomething(s(), integral_constant<int, 2>());
        doSomething(s(), integral_constant<int, 3>());
    }

    return 0;
}

