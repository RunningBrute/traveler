#include <catch2/catch_test_macros.hpp>

#include "Grid.h"
#include "Point.h"
#include "Solver.h"

TEST_CASE("Create and destroy Grid")
{
    const size_t rows = 10;
    const size_t cols = 10;
    const Point blockedSquers[] = {{0, 0}, {1, 1}};
    const size_t blockedSquesrCount = sizeof(blockedSquers) / sizeof(blockedSquers[0]);

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);

    REQUIRE(isCellBlocked(grid, 0, 0) == true);
    REQUIRE(isCellBlocked(grid, 1, 1) == true);
    REQUIRE(isCellBlocked(grid, 0, 1) == false);
    REQUIRE(isCellBlocked(grid, 2, 5) == false);

    REQUIRE(solve(grid, 2, findFirstUnvisitedCell) != NULL);

    destroyGrid(grid);
}