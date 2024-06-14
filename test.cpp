#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "external/doctest.h"

class Vector2 {
public:
    float x;
    float y;

    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}
};

class NewBlock {
public:
    NewBlock(Vector2 position) : position(position) {}

    Vector2 getPosition() const { return position; }

private:
    Vector2 position;
};

class NewObstacle {
public:
    NewObstacle(Vector2 position);
    std::vector<NewBlock> getNewBlocks() const { return blocks; }

    std::vector<NewBlock> blocks;

private:
    Vector2 position;
    std::vector<std::vector<int>> grid = {
        {1, 0, 0},
        {1, 1, 0},
        {0, 1, 1}
    };
};


NewObstacle::NewObstacle(Vector2 position) {
    this->position = position;

    for (unsigned int row = 0; row < grid.size(); ++row) {
        for (unsigned int column = 0; column < grid[row].size(); ++column) {
            if (grid[row][column] == 1) {
                float pos_x = position.x + column * 3;
                float pos_y = position.y + row * 3;
                NewBlock block = NewBlock({pos_x, pos_y});
                blocks.push_back(block);
            }
        }
    }
}

TEST_CASE("Testing NewObstacle constructor") {
    Vector2 startPosition = {10, 10};
    NewObstacle obstacle(startPosition);
    std::vector<NewBlock> blocks = obstacle.getNewBlocks();

    SUBCASE("Correct number of blocks") {
        CHECK(blocks.size() == 5); // 5 blocks in grid
    }

    SUBCASE("NewBlocks positions are correct") {
        std::vector<Vector2> expectedPositions = {
            {10, 10},  // Corresponds to grid[0][0]
            {10, 13},  // Corresponds to grid[1][0]
            {13, 13},  // Corresponds to grid[1][1]
            {13, 16},  // Corresponds to grid[2][1]
            {16, 16}   // Corresponds to grid[2][2]
        };

        for (size_t i = 0; i < blocks.size(); ++i) {
            CHECK(blocks[i].getPosition().x == doctest::Approx(expectedPositions[i].x));
            CHECK(blocks[i].getPosition().y == doctest::Approx(expectedPositions[i].y));
        }
    }
}
