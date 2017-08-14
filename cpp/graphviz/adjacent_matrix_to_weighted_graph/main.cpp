#include <array>
#include <string>
#include <iostream>


template <typename T>
auto adjacent_matrix_to_weighted_graph(T && mat, std::size_t row, std::size_t col)
        -> decltype(mat[row][col], std::string{})
{
    return "";
}

template <typename T, std::size_t row, std::size_t col>
auto adjacent_matrix_to_weighted_graph(std::array<std::array<T, col>, row> const & mat)
{
    return adjacent_matrix_to_weighted_graph(mat, row, col);
}

template <typename T, std::size_t row, std::size_t col>
auto adjacent_matrix_to_weighted_graph(std::array<std::array<T, col>, row> && mat)
{
    return adjacent_matrix_to_weighted_graph(std::forward<std::array<std::array<T, col>, row>>(mat), row, col);
}


int main(int, char**)
{
    std::array<std::array<int, 5>, 5> mat = {{
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 }
    }};

    std::cout << adjacent_matrix_to_weighted_graph(mat) << '\n';

    return 0;
}
