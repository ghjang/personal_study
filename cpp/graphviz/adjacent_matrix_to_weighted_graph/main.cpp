#include <array>
#include <string>
#include <iostream>
#include <sstream>


struct default_edge_styler
{
    template <typename T>
    constexpr auto operator () (std::size_t i, std::size_t j, T t) const
    {
        return "";
    }
};


template <typename T, typename EdgeStyler>
auto adjacent_matrix_to_weighted_graph(T && mat, std::size_t row, std::size_t col,
                                       EdgeStyler && styler)
        -> decltype(styler(0, 0, mat[0][0]), std::string{})
{
    std::ostringstream oss;

    oss << "digraph\n"
        << "{\n";

    for (std::size_t i = 0; i < row; ++i) {
        for (std::size_t j = 0; j < col; ++j) {
            if (mat[i][j] != 0) {
                oss << '\t' << i << " -> " << j << styler(i, j, mat[i][j]) << ";\n";
            }
        }
    }

    oss << "}\n";

    return oss.str();
}

template <typename T, std::size_t row, std::size_t col, typename EdgeStyler>
auto adjacent_matrix_to_weighted_graph(std::array<std::array<T, col>, row> const & mat,
                                       EdgeStyler && styler)
{
    return adjacent_matrix_to_weighted_graph(
                mat, row, col,
                std::forward<EdgeStyler>(styler)
           );
}

template <typename T, std::size_t row, std::size_t col, typename EdgeStyler>
auto adjacent_matrix_to_weighted_graph(std::array<std::array<T, col>, row> && mat,
                                       EdgeStyler && styler)
{
    return adjacent_matrix_to_weighted_graph(
                std::forward<std::array<std::array<T, col>, row>>(mat), row, col,
                std::forward<EdgeStyler>(styler)
           );
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

    //std::cout << adjacent_matrix_to_weighted_graph(mat, default_edge_styler{}) << '\n';

    std::cout << adjacent_matrix_to_weighted_graph(
                    mat,
                    [](auto i, auto j, auto weight) {
                        std::ostringstream oss;
                        oss << "[label=" << weight << ", weight=" << weight << "]";
                        return oss.str();
                    }
                 ) << '\n';

    return 0;
}
