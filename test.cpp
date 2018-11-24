#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "diameter.hpp"

TEST_CASE("test provided") {
    graph g = {{0, {2, 4}},
               {1, {4}},
               {2, {0, 3, 4}},
               {3, {2, 4, 5}},
               {4, {0, 1, 2, 3}},
               {5, {3}}};

    REQUIRE(max_diameter(g) == 3);
}

TEST_CASE("circular graph") {
    graph g = {{0, {1, 5}},
               {1, {0, 2}},
               {2, {1, 3}},
               {3, {2, 4}},
               {4, {3, 5}},
               {5, {4, 0}}};

    REQUIRE(max_diameter(g) == 3);
}

TEST_CASE("double graph") {
    graph g = {{0, {1}},
               {1, {0}},
               {2, {4}},
               {4, {2, 5}},
               {5, {4}}};

    REQUIRE(max_diameter(g) == 2);
}

TEST_CASE("7 graph") {
    graph g = {{0, {1, 3, 5, 6}},
               {1, {0, 2}},
               {2, {1, 3}},
               {3, {0, 2, 4}},
               {4, {3, 5}},
               {5, {0, 4, 6}},
               {6, {0, 5}}};

    REQUIRE(max_diameter(g) == 3);
}

TEST_CASE("from stream should work") {
    std::stringstream in("0 2\n"
                         "0 4\n"
                         "1 4\n"
                         "3 2\n"
                         "2 4\n"
                         "4 3\n"
                         "3 5");

    graph actual;
    from_stream(actual, in, 6, 7);

    graph expected = {{0, {2, 4}},
                      {1, {4}},
                      {2, {0, 3, 4}},
                      {3, {2, 4, 5}},
                      {4, {0, 1, 2, 3}},
                      {5, {3}}};

    REQUIRE(actual == expected);
}