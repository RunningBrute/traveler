#include <catch2/catch_test_macros.hpp>

#include <math.h>

#include "Grid.h"
#include "Point.h"
#include "Solver.h"
#include "Helpers.h"

TEST_CASE("No grid, no solution")
{
    const size_t movementPoints = 1;
    const size_t rows = 0;
    const size_t cols = 0;
    const Point blockedSquers[] = {};
    const size_t blockedSquesrCount = 0;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    REQUIRE(grid == NULL);
    REQUIRE(result == NULL);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}

TEST_CASE("Grid is a point so at least we can start")
{
    const size_t movementPoints = 1;
    const size_t rows = 1;
    const size_t cols = 1;
    const Point blockedSquers[] = {};
    const size_t blockedSquesrCount = 0;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    printGridWithPath(grid, result, movementPoints);

    REQUIRE(result->pathLength == 1);
    REQUIRE(result->path[0].row == 0);
    REQUIRE(result->path[0].column == 0);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}

TEST_CASE("Grid is a point, but blocked, so we cant start")
{
    const size_t movementPoints = 1;
    const size_t rows = 1;
    const size_t cols = 1;
    const Point blockedSquers[] = {{0, 0}};
    const size_t blockedSquesrCount = 1;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    printGridWithPath(grid, result, movementPoints);

    REQUIRE(result == NULL);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}

TEST_CASE("Grid is a true grid, but all cells are blocked, so we cant start again")
{
    const size_t movementPoints = 1;
    const size_t rows = 2;
    const size_t cols = 2;
    const Point blockedSquers[] = {{0,0},{0,1},{1,0},{1,1}};
    const size_t blockedSquesrCount = 4;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    printGridWithPath(grid, result, movementPoints);

    REQUIRE(result == NULL);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}

TEST_CASE("Two cells available so both should be added into path")
{
    const size_t movementPoints = 1;
    const size_t rows = 2;
    const size_t cols = 2;
    const Point blockedSquers[] = {{0,0},{0,1}};
    const size_t blockedSquesrCount = 2;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    printGridWithPath(grid, result, movementPoints);

    //REQUIRE(result->pathLength == 2);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}

/*
TEST_CASE("Create and destroy Grid")
{
    const size_t rows = 10;
    const size_t cols = 10;
    const Point blockedSquers[] = {{0, 0}, {1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
    const size_t blockedSquesrCount = sizeof(blockedSquers) / sizeof(blockedSquers[0]);

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);

    REQUIRE(isCellBlocked(grid, 0, 0) == true);
    REQUIRE(isCellBlocked(grid, 1, 1) == true);
    REQUIRE(isCellBlocked(grid, 0, 1) == false);
    REQUIRE(isCellBlocked(grid, 2, 5) == false);

    const size_t movementPoints = 12;
    Output* result = solve(grid, movementPoints, findBestStartingCell);

    printGridWithPath(grid, result, movementPoints);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}
*/
TEST_CASE("Solve empty grid")
{
    const size_t movementPoints = 5;
    const size_t rows = 5;
    const size_t cols = 5;
    const Point blockedSquers[] = {{0,0}};
    const size_t blockedSquesrCount = 1;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    //REQUIRE(validatePath(grid, result, movementPoints));
    printGridWithPath(grid, result, movementPoints);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}