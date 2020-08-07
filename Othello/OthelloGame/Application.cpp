#include "Application.h"
#include "raylib.h"
#include <vector>
Application::Application()
{
}
Application::~Application()
{
}
void Application::Run()
{
    InitWindow(m_tileSize * 8, m_tileSize * 8, "Othello");
    Load();
    while (!WindowShouldClose())
    {
        Update(GetFrameTime());
        Draw();
    }
    Unload();
    CloseWindow();
}
void Application::Load()
{
    m_board =
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
}
void Application::Unload()
{
}
void Application::Update(float dt)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        int mouseXIndex = GetMouseX() / m_tileSize;
        int mouseYIndex = GetMouseY() / m_tileSize;
        if (mouseXIndex >= 0 && mouseXIndex < 8 && mouseYIndex >= 0 && mouseYIndex < 8)
        {
            if (IsValidMove(m_player, mouseXIndex, mouseYIndex, m_board))
            {
                m_board = MakeMove(m_player, mouseXIndex, mouseYIndex, m_board);
                // swap to next player
                m_player = m_player == 'B' ? 'W' : 'B';
                if (AnyValidMoves(m_player, m_board) == false)
                {
                    // swap back
                    m_player = m_player == 'B' ? 'W' : 'B';
                    // check again - 
                    if (AnyValidMoves(m_player, m_board) == false)
                    {
                        CheckWinState();
                    }
                }
            }
        }
    }
}
void Application::Draw()
{
    Color bgColor = { 34, 34, 34, 255 };
    Color tileColor = { 0, 144, 103, 255 };
    Color tileHoverColor = { 10, 154, 113, 255 };
    Color whitePieceColor = { 244, 253, 250, 255 };
    Color blackPieceColor = { 19, 26, 24, 255 };
    int mouseXIndex = GetMouseX() / m_tileSize;
    int mouseYIndex = GetMouseY() / m_tileSize;
    BeginDrawing();
    ClearBackground(bgColor);
    // draw chekcered background
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            float xp = x * m_tileSize;
            float yp = y * m_tileSize;
            float hs = m_tileSize * 0.5f;
            Color tCol = x == mouseXIndex && y == mouseYIndex ? tileHoverColor : tileColor;
            DrawRectangle(xp, yp, m_tileSize - 1, m_tileSize - 1, tCol);
            if (m_board[y][x] != ' ')
            {
                Color pieceCol = m_board[y][x] == 'B' ? blackPieceColor : whitePieceColor;
                DrawCircle(xp + hs, yp + hs, hs - 10, pieceCol);
            }
            if (IsValidMove(m_player, x, y, m_board))
            {
                DrawCircle(xp + hs, yp + hs, 5, blackPieceColor);
                DrawCircleLines(xp + hs, yp + hs, 5, whitePieceColor);
            }
        }
    }
    if (m_endGameMessage != "")
    {
        // m_endGameMessage = "Black Wins";
        int sw = GetScreenHeight();
        int sh = GetScreenHeight();
        DrawRectangle(0, sh * 0.5f - 100, sh, 200, { 0, 0, 0, 196 });
        auto textSize = MeasureText(m_endGameMessage.c_str(), 32);
        DrawText(m_endGameMessage.c_str(), sw * 0.5f - textSize * 0.5f, sh * 0.5f, 32, RAYWHITE);
        textSize = MeasureText("Space to play again", 24);
        DrawText("Space to play again", sw * 0.5f - textSize * 0.5f, sh * 0.5f + 42, 24, GRAY);
    }
    EndDrawing();
}
bool Application::IsValidMove(char player, int x, int y, const OthelloBoardState& grid)
{
    char opponent = player == 'B' ? 'W' : 'B';
    if (grid[y][x] != ' ')
        return false;
    auto CheckDir = [&](int xd, int yd) -> bool
    {
        // look top left
        bool canPlaceTile = false;
        for (int i = 1; i < 8; i++)
        {
            int xi = x - i * xd;
            int yi = y - i * yd;
            if (xi < 0 || xi >= 7 || yi < 0 || yi >= 7)
            {
                break;
            }
            if (grid[yi][xi] == opponent)
            {
                canPlaceTile = true;
                continue;
            }
            if (grid[yi][xi] == ' ')
                break;
            if (grid[yi][xi] == player && canPlaceTile)
                return true;
        }
        return false;
    };
    if (CheckDir(1, 0)) return true;
    if (CheckDir(-1, 0)) return true;
    if (CheckDir(0, -1)) return true;
    if (CheckDir(0, 1)) return true;
    if (CheckDir(-1, -1)) return true; // top left
    if (CheckDir(1, -1)) return true; // top right
    if (CheckDir(1, 1)) return true; // bottom right
    if (CheckDir(-1, 1)) return true; // bottom left
    return false;
}
OthelloBoardState Application::MakeMove(char player, int x, int y, OthelloBoardState grid)
{
    // Place counter
    grid[y][x] = player;
    // Flip counters
    /*
    directions = directionReturn();
    while (grid[y][x] != ' ')
    {
        grid[y][x] = player;
        y += direction;
        x += direction;
    }
    */
    return grid;
}
bool Application::AnyValidMoves(char player, const OthelloBoardState& grid)
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (IsValidMove(player, x, y, grid))
                return true;
        }
    }
    return false;
}
void Application::CheckWinState()
{
    int numBlack = 0;
    int numWhite = 0;
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (m_board[y][x] == 'W') numWhite++;
            if (m_board[y][x] == 'B') numBlack++;
        }
    }
    if (numBlack > numWhite) m_endGameMessage = "Black Wins";
    else if (numWhite > numBlack) m_endGameMessage = "White Wins";
    else m_endGameMessage = "Draw";
}