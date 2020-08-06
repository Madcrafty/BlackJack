#include <iostream>
#include <vector>

typedef std::vector<std::vector<char>> OthelloBoardState;
struct Direction
{
    int x;
    int y;
    bool valid = true;
};
std::vector<Direction> LoadDirections()
{
    std::vector<Direction> directions;
    directions.push_back(Direction{ -1,-1,true });  // UL
    directions.push_back(Direction{ -1,0,true });  // U
    directions.push_back(Direction{ -1,1,true });  // UR
    directions.push_back(Direction{ 0,-1,true });  // L
    directions.push_back(Direction{ 0,1,true });  // R
    directions.push_back(Direction{ 1,-1,true });  // DL
    directions.push_back(Direction{ 1,0,true });  // D
    directions.push_back(Direction{ 1,1,true });  // DR
    return directions;
}
bool DirectionsValid(const std::vector<Direction> directions)
{
    for (size_t i = 0; i < directions.size(); i++)
    {
        if (directions[i].valid == true)
        {
            return true;
        }
    }
    return false;
}
bool IsValidMove(char player, int x, int y, const OthelloBoardState& grid)
{
    std::vector<Direction> Directions = LoadDirections();
    char enemy;
    player == 'B' ? enemy = 'W' : enemy = 'B';
    // First check if current tile is empty
    if (grid[y][x] != ' ')
    {
        return false;
    }
    // Second check if space is adjacent to enemy tile
    for (size_t i = 0; i < Directions.size(); i++)
    {
        if (y + Directions[i].y > grid.size() ||
            y + Directions[i].y < 0 ||
            x + Directions[i].x > grid[0].size() ||
            x + Directions[i].x < 0)
        {
            Directions[i].valid = false;
        }
        else if (grid[y + Directions[i].y][x + Directions[i].x] != enemy)
        {
            Directions[i].valid = false;
        }
    }
    if (!DirectionsValid(Directions))
    {
        return false;
    }
    // Third check if there is a friendly connected piece
    for (size_t i = 0; i < Directions.size(); i++)
    {
        int d = 2;
        while (Directions[i].valid)
        {
            if (y + Directions[i].y*d > grid.size() ||
                y + Directions[i].y*d < 0 ||
                x + Directions[i].x*d > grid[0].size() ||
                x + Directions[i].x*d < 0)
            {
                Directions[i].valid = false;
            }
            else if (grid[y + Directions[i].y*d][x + Directions[i].x*d] == player)
            {
                // fix later to return multiple directions
                return true;
            }
            else if (grid[y + Directions[i].y * d][x + Directions[i].x * d] == ' ')
            {
                Directions[i].valid = false;
            }
            d++;
        }
    }
    return false;
}
OthelloBoardState MakeMove(char player, int x, int y, OthelloBoardState grid)
{
    // if the move was not valid, just return the origional...
    if (IsValidMove(player, x, y, grid) == false)
        return grid;
    // TODO: This is optionan, but gitve it a go if you have time ;)
    // update 'grid' so that the approprate tiles have been flipped.
    return grid;
}

int main(int argc, char** argv)
{
    OthelloBoardState state1 =
    {//   0    1    2    3    4    5    6    7
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 0
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 1
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 2
        {' ', ' ', ' ', 'W', 'B', ' ', ' ', ' '}, // 3
        {' ', ' ', ' ', 'B', 'W', ' ', ' ', ' '}, // 4
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 5
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 6
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}  // 7
    };
    auto ShouldBe = [](auto result, auto expected) {
        std::cout << (result == expected ? "\033[32m [PASS]" : "\033[31m [FAIL]") << "\033[0m" << std::endl;
    };
    ShouldBe(IsValidMove('B', 5, 4, state1), true); // true
    ShouldBe(IsValidMove('B', 2, 4, state1), false); // false
    ShouldBe(IsValidMove('B', 3, 2, state1), true); // true
    ShouldBe(IsValidMove('B', 3, 5, state1), false); // false
    ShouldBe(IsValidMove('B', 5, 5, state1), false); // false
    ShouldBe(IsValidMove('W', 5, 4, state1), false); // false
    ShouldBe(IsValidMove('W', 2, 4, state1), true); // true
    ShouldBe(IsValidMove('W', 3, 2, state1), false); // false
    ShouldBe(IsValidMove('W', 3, 5, state1), true); // true
    ShouldBe(IsValidMove('W', 5, 5, state1), false); // false
    OthelloBoardState state2 =
    {//   0    1    2    3    4    5    6    7
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 0
        {' ', ' ', 'B', ' ', ' ', ' ', ' ', ' '}, // 1
        {' ', ' ', 'B', 'W', ' ', ' ', ' ', ' '}, // 2
        {' ', ' ', 'B', 'W', 'B', ' ', ' ', ' '}, // 3
        {' ', ' ', 'W', 'W', 'W', ' ', ' ', ' '}, // 4
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 5
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 6
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}  // 7
    };
    ShouldBe(IsValidMove('B', 2, 5, state2), true); // true
    ShouldBe(IsValidMove('B', 3, 5, state2), false); // false
    ShouldBe(IsValidMove('B', 4, 5, state2), true); // true
    ShouldBe(IsValidMove('B', 3, 1, state2), false); // false
    ShouldBe(IsValidMove('B', 4, 2, state2), true); // true
    ShouldBe(IsValidMove('B', 4, 1, state2), true); // true

    ShouldBe(IsValidMove('W', 2, 5, state2), false); // false
    ShouldBe(IsValidMove('W', 2, 0, state2), true); // true
    ShouldBe(IsValidMove('W', 3, 1, state2), false); // false
    return 0;
}