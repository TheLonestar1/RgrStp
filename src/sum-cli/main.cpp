#include <iostream>
#include <Matrixlib/Matrixlib.hpp>
#include <algorithm>
int main()
{
    Matrix<int> m(3, 3);
    Matrix<int> m1(3, 3);
    Matrix<int> m2(3, 3);
    for (auto& x : m)
    {
        x = rand() % 6;
    }
    for (auto& x : m1)
    {
        x = rand() % 6;
    }
    for (auto& x : m2)
    {
        x = rand() % 6;
    }
    m2 = (m + m2);
    std::cout << "\n";
    for (auto& x : m)
        std::cout << x << " ";
    std::cout << "\n";
    for (auto& x : m1)
        std::cout << x << " ";
    std::cout << "\n";
    for (auto& x : m2)
        std::cout << x << " ";
    std::cout << "\n";
    auto it = std::find(m.begin(), m.end(), 5);
    if(*it == 5)
        std::cout << m[0][0] << " find = "  << *it << std::endl;
    else
        std::cout << m[0][0] << " Not find" << std::endl;

	return 0;
}
