#include "Solver.h"

static int getNeighbourScore(const Grid* grid, const size_t row, const size_t column)
{
    Point neighbour = {
        .row = row,
        .column = column
    };

    if(!isPointInsideGrid(grid, neighbour))
        return 0;
    if(isCellBlocked(grid, neighbour))
        return -100;
    if(isCellVisited(grid, neighbour))
        return 10;

    return 500;
}

static int get3x3WindowScore(const Grid* grid, const size_t row, const size_t column)
{
    int score = 0;

    score += getNeighbourScore(grid, row - 1, column - 1);
    score += getNeighbourScore(grid, row - 1, column    );
    score += getNeighbourScore(grid, row - 1, column + 1);
    score += getNeighbourScore(grid, row,     column - 1);
    score += getNeighbourScore(grid, row,     column + 1);
    score += getNeighbourScore(grid, row + 1, column - 1);
    score += getNeighbourScore(grid, row + 1, column    );
    score += getNeighbourScore(grid, row + 1, column + 1);

    return score;
}

Point findBestStartingCell(const Grid* grid)
{
    const size_t maxRows = getGridRowsCount(grid);
    const size_t maxCols = getGridColumnsCount(grid);
    const size_t bufferSize = maxRows*maxCols;
    size_t bestScore = 0;
    Point result = {
        .row = -1,
        .column = -1
    };

    for (size_t row = 0; row < maxRows; row++)
    {
        for (size_t col = 0;  col < maxCols; col++)
        {
            Point point = {.row = row, .column = col };
            if (isCellBlocked(grid, point))
                continue;

            const int score = get3x3WindowScore(grid, row, col);
            if (score > bestScore)
            {
                bestScore = score;
                result.row = row;
                result.column = col;
            }
        }
    }

    return result;
}

Point findFirstUnvisitedCell(const Grid* grid)
{
    Point result = {
        .row = -1,
        .column = -1
    };

    for (size_t row = 0; row < getGridRowsCount(grid); row++)
    {
        for (size_t col = 0;  col < getGridColumnsCount(grid); col++)
        {
            Point point = {.row = row, .column = col };
            if (!isCellBlocked(grid, point))
            {
                result.row=row;
                result.column=col;
                return result;
            }
        }
    }

    return result;
}

static bool checkCandidate(Grid* grid, const Point candidate, const int bestScore, Candidate* nextCandidate)
{
    if (!isPointInsideGrid(grid, candidate))
    {
        return false;
    }

    if (isCellBlocked(grid, candidate))
    {   
        return false;
    }

    size_t numOfElements = getGridRowsCount(grid) * getGridColumnsCount(grid);
    int score = 0;
    if (numOfElements > 25)
    {
        score = get3x3WindowScore(grid, candidate.row, candidate.column);
    }
    else
    {
        score = getNeighbourScore(grid, candidate.row, candidate.column);
    }

    if (score <= bestScore)
    {
        return false;
    }

    nextCandidate->score = score;
    nextCandidate->point = candidate;
    
    return true;
}

typedef struct
{
    int dRow;
    int dColumn;
} Direction;

#define MAX_DIRECTIONS 4

static const Direction directions[MAX_DIRECTIONS] =
{
    {-1, 0}, // up
    {1,  0}, // down
    {0, -1}, // left
    {0,  1}  // right
};

static Output* createEmptyOutput(const size_t movementPoints)
{
    size_t possibleMaxPath = movementPoints + 1;
    
    Output* output = (Output*)malloc(sizeof(*output));
    output->uniqueSquers = 0;
    output->path = (Point*)malloc(sizeof(*output->path)*possibleMaxPath);
    output->pathLength = 0;

    return output;
}

static void addPointIntoOutputPath(const Point point, Output* output, const bool uniqueSquere)
{
    output->path[output->pathLength++] = point;
    if (uniqueSquere) output->uniqueSquers++;
}

void cleanupSolvedOutput(Output* output)
{
    if (output) free(output->path);
    free(output);
}

Output* solve(Grid* grid, const size_t movementPoints, StartingPointStrategy startingPointStrategy)
{
    if (!grid)
    {
        return NULL;
    }

    Output* output = createEmptyOutput(movementPoints);

    Point startingPoint = startingPointStrategy(grid);
    if (startingPoint.row < 0)
    {
        cleanupSolvedOutput(output);
        return NULL;
    }
    addPointIntoOutputPath(startingPoint, output, true);

    Point currentPoint = startingPoint;
    size_t counter = movementPoints;
    while(counter > 0)
    {
        Cell* currentCell = getGridCell(grid, currentPoint);
        setVisited(currentCell);

        bool foundNewCell = false;
        Candidate bestCell = {
            .score = -123456,
            .point = {-1, -1}
        };

        for (size_t i = 0; i < MAX_DIRECTIONS; ++i)
        {
            Point nextPoint = { 
                .row = currentPoint.row + directions[i].dRow,
                .column = currentPoint.column + directions[i].dColumn
            };

            Candidate candidate;
            if (checkCandidate(grid, nextPoint, bestCell.score, &candidate))
            {
                foundNewCell = true;
                bestCell = candidate;
            }
        }

        if (foundNewCell)
        {
            const bool uniqueSquere = isCellVisited(grid, currentPoint) ? true : false;
            addPointIntoOutputPath(bestCell.point, output, uniqueSquere);
            currentPoint = bestCell.point;
        }

        counter--;
    }

    return output;
}