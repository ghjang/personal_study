#include <array>
#include <string>
#include <iostream>
#include <sstream>


template <typename T>
auto adjacent_matrix_to_weighted_graph(T && mat, std::size_t row, std::size_t col)
        -> decltype(mat[0][0], std::string{})
{
    std::ostringstream oss;

    oss << "digraph\n"
        << "{\n";

    for (std::size_t i = 0; i < row; ++i) {
        for (std::size_t j = 0; j < col; ++j) {
            if (mat[i][j] != 0) {
                oss << '\t' << i << " -> " << j << "[label=" << mat[i][j] << ", weight=" << mat[i][j] << "];" << '\n';
            }
        }
    }

    oss << "}\n";

    return oss.str();
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
        { 0, 2, 0, 0, 0 },
        { 0, 0, 0, 5, 0 },
        { 1, 0, 0, 0, 0 },
        { 0, 0, 0, 3, 0 },
        { 1, 0, 4, 0, 0 }
    }};

    std::cout << adjacent_matrix_to_weighted_graph(mat) << '\n';

    return 0;
}
