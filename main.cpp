#include <cassert>
#include "diameter.hpp"

auto main() -> int {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    assert(input);
    assert(output);

    output << diameter(input);

    input.close();
    output.close();
    return 0;
}