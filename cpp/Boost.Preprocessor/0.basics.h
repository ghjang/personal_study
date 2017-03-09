//==============================================================================
// 1. C++ Built-in Preprocessor
//==============================================================================

// An ordinary include-file guard
// 
// It is possible to decide whether a preprocessor macro is defined or not
// by using '#ifndef, if not defined' or '#ifdef, if defined'. 
#ifndef BASICS_H

// define the preprocessor macro, BASICS_H, if it was not defined.
#define BASICS_H

// other forms of preprocessor macro definition test
#ifdef BASICS_H
#endif

#if defined(BASICS_H)
#endif

#if not defined(BASICS_H)
#endif

#ifdef BASICS_H
// You can use spaces between the '#' and the preprocessor keywords.
// Sometimes, it's good for indentation.
#   ifdef ADVANCED_H
#   endif
#endif

// integral operations are allowed.
#if 10 > 3 * 2
"10 > 3 * 2"
#endif

#define MY_NUMBER 10

#if MY_NUMBER > 3 * 2
"MY_NUMBER > 3 * 2"
#endif

#if MY_NUMBER > 3 * 2 && (MY_NUMBER % 2 == 0)
"MY_NUMBER > 3 * 2. even number."
#else
"MY_NUMBER > 3 * 2. odd number."
#endif

//==============================================================================
// 2. Preprocessor Macro
//==============================================================================

//==============================================================================
//     1. Object-like Macro
//==============================================================================
#define OBJECT_LIKE_MACRO I am an object-like macro.

// Backslash character at the end of the line can be used.
// Note that the final result of this obejct-like macro is a single line.
#define ANOTHER_OBJECT_LIKE_MACRO I am an \
    another object-like macro.

// This is an empty object-like macro.
#define EMPTY_OBJECT_LIKE_MACRO

/*
OBJECT_LIKE_MACRO
ANOTHER_OBJECT_LIKE_MACRO
EMPTY_OBJECT_LIKE_MACRO
*/

//==============================================================================
//     2. Function-like Macro
//==============================================================================
#define FUNCTION_LIKE_MACRO_0(arg) arg

#define FUNCTION_LIKE_MACRO_1(arg0, arg1) arg0 and arg1

// Multiple lines are possible.
// Note that the last backslash extends the macro definition to the next line.
#define FUNCTION_LIKE_MACRO_2(arg)  \
    first line: arg,                \
    second line: arg

#define FUNCTION_LIKE_MACRO_3() empty arguments.

/*
FUNCTION_LIKE_MACRO_0(I am a function-like macro 0.)

// comma(',') is special to the preprocessor.
// comma is used to separate the arguments to the function-like macro.
// If you want to pass a comma, you need to enclose them with parenthesises.
FUNCTION_LIKE_MACRO_0((I am a funny, short and useful function-like macro 0.))

// matched pairs of parenthesises can be passed.
FUNCTION_LIKE_MACRO_0((I am a (funny short and useful) function-like macro 0.))

// This is OK.
FUNCTION_LIKE_MACRO_0(I am a (funny short and useful) function-like macro 0.)

// But this isn't.
//FUNCTION_LIKE_MACRO_0((I am a (funny short and useful function-like macro 0.))

FUNCTION_LIKE_MACRO_1(argument1, argumen2)

// Note that the result is a single line.
FUNCTION_LIKE_MACRO_2(duplicate arguments)

// no arguments to this macro function
FUNCTION_LIKE_MACRO_3()
*/

//==============================================================================
// 3. Higher-Order Function-like Macro
//==============================================================================
#define HOF_MACRO_0(f, arg) f(arg)

// Note that the enclosing f with parenthesises can cause some un-expeced results.
// Use it only when it's appropriate.
#define HOF_MACRO_1(f, arg) (f)(arg)

#define TWICE(f, arg) \
    f(f(arg))

#define DUPLICATE_ARG(arg) arg arg

/*
HOF_MACRO_0(
    FUNCTION_LIKE_MACRO_0,
    indirect macro function call argument.
)

HOF_MACRO_1(
    FUNCTION_LIKE_MACRO_0,
    indirect macro function call argument.
)

TWICE(
    DUPLICATE_ARG,
    "XYZ"
)
*/

//==============================================================================
// 4. Concatenating Tokens
//==============================================================================

#define CONCAT(arg0, arg1) arg0 ## arg1

//CONCAT(I am , a boy.)

// refer to BOOST_PP_CAT

//==============================================================================
// 5. Preprocessor Token to String
//==============================================================================

#define TO_STR_IMPL(s) #s
#define TO_STR(s) TO_STR_IMPL(s)

/*
TO_STR_IMPL(
    CONCAT(I am , a boy.)
)

TO_STR(
    CONCAT(I am , a boy.)
)

TO_STR(
    "I am a boy."
)
*/

// refer to BOOST_PP_STRINGIZE

//==============================================================================
// 6. Variadic Macro
//==============================================================================

#define VARIADIC_ARG_FUNCTION(...) \
    __VA_ARGS__

// This seems not to work.
//#define CONCAT_VARIADIC_ARG(...) \
//    ##__VA_ARGS__

#define TO_STR_VARIADIC_ARG(...) \
    #__VA_ARGS__

/*
VARIADIC_ARG_FUNCTION(arg0, arg1, arg2, arg3)

//CONCAT_VARIADIC_ARG(arg0, arg1, arg2, arg3)

TO_STR_VARIADIC_ARG(arg0, arg1, arg2, arg3)
*/


// It's a good habit to #undef the local macros when it's done.
#undef OBJECT_LIKE_MACRO
#undef ANOTHER_OBJECT_LIKE_MACRO
#undef EMPTY_OBJECT_LIKE_MACRO
#undef FUNCTION_LIKE_MACRO_0
#undef FUNCTION_LIKE_MACRO_1
#undef FUNCTION_LIKE_MACRO_2
#undef FUNCTION_LIKE_MACRO_3
#undef HOF_MACRO_0
#undef HOF_MACRO_1
#undef TWICE
#undef DUPLICATE_ARG
#undef CONCAT
#undef TO_STR_IMPL
#undef TO_STR
#undef VARIADIC_ARG_FUNCTION
#undef TO_STR_VARIADIC_ARG
#undef MY_NUMBER

// #elif and #else branches are available.
#elif defined(SOME_MACRO)
#   pragma message("reached the first #elif branch")
#elif !defined(STILL_ANOTHER_MACRO)
#   pragma message("reached the second #elif branch")
#else
#   pragma message("reached #else branch")
#endif // BASICS_H
