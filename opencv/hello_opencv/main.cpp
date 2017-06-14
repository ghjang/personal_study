#include <iostream>
#include <opencv2/core.hpp>


int main()
{
    cv::Matx33f m = cv::Matx33f::eye();

    std::cout << m(0, 0) << '\n';
    std::cout << m(2, 2) << '\n';

    return 0;
}
