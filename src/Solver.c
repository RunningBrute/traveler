#include "Solver.h"

static int getNeighbourScore(const Grid* grid, const size_t row, const size_t column)
{
    const size_t maxRows = getGridRowsCount(grid);
    const size_t maxCols = getGridColumnsCount(grid);

    Point neighbour = {
        .row = row,
        .column = column
    };

    if(isPointInsideGrid(grid, neighbour))
        return 0;
    if(isCellBlocked(grid, row, column))
        return -100;
    if(isCellVisited(grid, row, column))
        return 10;

    return 200;
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

Point* findBestStartingCell(const Grid* grid)
{
    const size_t maxRows = getGridRowsCount(grid);
    const size_t maxCols = getGridColumnsCount(grid);
    const size_t bufferSize = maxRows*maxCols;
    size_t bestScore = 0;
    Point* result = (Point*)malloc(sizeof(*result));

    int* bestNeighboringScoreMap = (int*)malloc(sizeof(*bestNeighboringScoreMap)*bufferSize);

    for (size_t row = 0; row < maxRows; row++)
    {
        for (size_t col = 0;  col < maxCols; col++)
        {
            if (isCellBlocked(grid, row, col))
                continue;

            const int score = get3x3WindowScore(grid, row, col);
            if (score > bestScore)
            {
                bestScore = score;
                result->row = row;
                result->column = col;
            }
        }
    }

    return NULL;
}

Point* findFirstUnvisitedCell(const Grid* grid)
{
    Point* result = (Point*)malloc(sizeof(*result));

    for (size_t row = 0; row < getGridRowsCount(grid); row++)
    {
        for (size_t col = 0;  col < getGridColumnsCount(grid); col++)
        {
            if (!isCellBlocked(grid, row, col))
            {
                result->row=row;
                result->column=col;
                return result;
            }
        }
    }

    return NULL;
}

static Candidate* checkCandidate(Grid* grid, const Point candidate, const int bestScore)
{
    if (!isPointInsideGrid(grid, candidate))
        return NULL;

    printf(
        "Candidate: row=%u col=%u\n",
        candidate.row,
        candidate.column);

    printf(
    "Inside=%d blocked=%d\n",
    isPointInsideGrid(grid, candidate),
    isCellBlocked(grid,
                  candidate.row,
                  candidate.column));

    if (!isCellBlocked(grid, candidate.row, candidate.column))
    {   
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
        if (score > bestScore)
        {
            Candidate* next = (Candidate*)malloc(sizeof(*next));
            next->score = score;
            next->point.row = candidate.row;
            next->point.column = candidate.column;
            return next;
        }
    }
    return NULL;
}

Output* solve(Grid* grid, const size_t movementPoints, StartingPointStrategy startingPointStrategy)
{
    if (!grid)
        return NULL;

    size_t possibleMaxPath = movementPoints;

    Output* output = (Output*)malloc(sizeof(*output));
    output->uniqueSquers = 0;
    output->path = (Point*)malloc(sizeof(*output->path)*possibleMaxPath);
    output->pathLength = 0;

    Point* startingPoint = startingPointStrategy(grid);
    if (!startingPoint)
        return NULL;

    Point currentPoint;
    currentPoint.column = startingPoint->column;
    currentPoint.row = startingPoint->row;

    free(startingPoint);

    printf("Starting point added to path! Row: %d, Col: %d \n", currentPoint.row, currentPoint.column);
    output->path[0] = currentPoint;
    output->pathLength++;
    output->uniqueSquers++;

    size_t pointsInPath = 1;
    size_t counter = movementPoints;
    while(counter > 0)
    {
        Cell* currentCell = getGridCell(grid, currentPoint.row, currentPoint.column);
        setVisited(currentCell);

        int bestScore = -100000;
        bool foundCandidate = false;
        Point bestPoint = {
            .row = 0,
            .column = 0
        };

        Point nextPoint = {currentPoint.row - 1, currentPoint.column};
        Candidate* nextCandidate = checkCandidate(grid, nextPoint, bestScore);
        if (nextCandidate)
        {
            foundCandidate = true;
            bestScore = nextCandidate->score;
            bestPoint = nextCandidate->point;
            printf("[Up] New best score found: %d \n", bestScore);
        }
        free(nextCandidate);

        nextPoint.row = currentPoint.row + 1;
        nextPoint.column = currentPoint.column;
        nextCandidate = checkCandidate(grid, nextPoint, bestScore);
        if (nextCandidate)
        {
            foundCandidate = true;
            bestScore = nextCandidate->score;
            bestPoint = nextCandidate->point;
            printf("[Down] New best score found: %d \n", bestScore);
        }
        free(nextCandidate);

        nextPoint.row = currentPoint.row;
        nextPoint.column = currentPoint.column - 1;
        nextCandidate = checkCandidate(grid, nextPoint, bestScore);
        if (nextCandidate)
        {
            foundCandidate = true;
            bestScore = nextCandidate->score;
            bestPoint = nextCandidate->point;
            printf("[Left] New best score found: %d \n", bestScore);
        }
        free(nextCandidate);

        nextPoint.row = currentPoint.row;
        nextPoint.column = currentPoint.column + 1;
        nextCandidate = checkCandidate(grid, nextPoint, bestScore);
        if (nextCandidate)
        {
            foundCandidate = true;
            bestScore = nextCandidate->score;
            bestPoint = nextCandidate->point;
            printf("[Right] New best score found: %d \n", bestScore);
        }
        free(nextCandidate);

        if (bestScore == 0)
        {
            printf("[HMMMMM] bestScore equal 0 is not that bad ... \n");
        }

        if (foundCandidate)
        {
            printf("[PathLength: %ld] New new point added to path! Row: %d, Col: %d \n", output->pathLength + 1, bestPoint.row, bestPoint.column);
            currentPoint = bestPoint;
            output->path[pointsInPath] = bestPoint;
            output->pathLength++;
            pointsInPath++;
        }

        if (!isCellVisited(grid, currentPoint.row, currentPoint.column))
        {
            printf("[ADD] unique squer, nice! \n");
            output->uniqueSquers++;
        }

        counter--;
    }

    return output;
}

void cleanupSolvedOutput(Output* output)
{
    if (output) free(output->path);
    free(output);
}