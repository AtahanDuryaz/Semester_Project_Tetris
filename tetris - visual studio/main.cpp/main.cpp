#pragma warning(disable : 4996)
#include <iostream>
#include "raylib.h"
#include "game.h"
#include "colors.h"

double lastUpdateTime = 0;
int difficulty = 1;
int theme = 1;



bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}
Font font;
int ShowMenu()
{

    ClearBackground(darkGrey);
    DrawRectangleRounded({ 200,85,250,60 }, 0.3, 6, WHITE);
    DrawRectangleRounded({ 200,355,250,60 }, 0.3, 6, WHITE);

    DrawTextEx(font, "Main Menu", { 205,10 }, 40, 2, red);
    DrawTextEx(font, "Start", { 245,105 }, 30, 2, green);
    DrawTextEx(font, "Exit", { 265,365 }, 30, 2, green);

    DrawRectangleRounded({ 200,185,250,30 }, 0.3, 6, WHITE);
    DrawTextEx(font, "Difficulty:", { 210,185 }, 20, 2, green);


    DrawRectangleRounded({ 200,225,250,40 }, 0.3, 6, WHITE);
    DrawTextEx(font, "Theme:", { 210, 235 }, 20, 2, green);


    if (theme == 1)
    {
        DrawTextEx(font, TextFormat("Default"), { 310,235 }, 20, 2, green);

    }
    else if (theme == 2)
    {
        DrawTextEx(font, TextFormat("Fenerbahce"), { 310,235 }, 20, 2, green);

    }
    else
        DrawTextEx(font, TextFormat("Purple"), { 310,235 }, 20, 2, green);



    if (difficulty == 1)
    {
        DrawTextEx(font, TextFormat("Easy"), { 310,185 }, 20, 2, green);
    }
    else if (difficulty == 2)
    {
        DrawTextEx(font, TextFormat("Medium"), { 310,185 }, 20, 2, green);
    }
    else
        DrawTextEx(font, TextFormat("Hard"), { 310,185 }, 20, 2, green);
    int result = 0;
    Vector2 mousePoint = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mousePoint, { 200, 85, 200, 60 }))
        {
            return 1;
        }

        if (CheckCollisionPointRec(mousePoint, { 200, 355, 200, 60 }))
        {
            return 2;
        }

        if (CheckCollisionPointRec(mousePoint, { 200, 185, 200, 40 }))
        {
            difficulty = (difficulty % 3) + 1;
        }
        if (CheckCollisionPointRec(mousePoint, { 200, 225, 200, 40 }))
        {
            theme = (theme % 3) + 1;
        }
        return result;
    }

}







int main() {
    InitWindow(1000, 700, "raylib-tetris");
    Color darkBLue = { 44, 44,127,255 };
    SetTargetFPS(60);
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    bool inMenu = true;
    bool inGame = false;
    bool inKeybinding = false;
    Game game = Game();


    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);
        if (inMenu) {
            BeginDrawing();
            int menuResult = ShowMenu();

            if (menuResult == 1) {
                inMenu = false;
                inGame = true;

            }
            else if (menuResult == 2)
            {
                break;
            }
            else if (menuResult == 3)
            {
                inMenu = false;
                inGame = false;

            }
            EndDrawing();
            continue;
        }


        game.HandleInput();
        if (EventTriggered(0.6 / difficulty))
        {
            game.MoveBlockDown();
        }

        BeginDrawing();
        if (theme == 1) {
            ClearBackground(yellow);
            DrawTextEx(font, "Scoreboard", { 350,15 }, 38, 2, BLACK);
            DrawTextEx(font, "Next Piece", { 350,120 }, 38, 2, BLACK);
            DrawTextEx(font, "Holded Piece", { 350,340 }, 38, 2, BLACK);
            DrawRectangleRounded({ 320,60,300,60 }, 0.3, 6, darkred);

            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

            char holdlimitText[5];
            sprintf(holdlimitText, "%d", game.HoldLimit);
            DrawTextEx(font, "Remaining Hold: ", { 650,15 }, 38, 2, BLACK);
            DrawTextEx(font, holdlimitText, { 950,15 }, 38, 2, BLACK);


            DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2,65 }, 38, 2, BLACK);
            DrawRectangleRounded({ 320,160,300,180 }, 0.3, 6, darkred);
            DrawRectangleRounded({ 320,380,300,200 }, 0.3, 6, darkred);
            if (game.gameOver)
            {
                DrawTextEx(font, "!!!GAME OVER!!!", { 10,620 }, 38, 2, darkGrey);
            }
            game.Draw();
            EndDrawing();
        }
        if (theme == 2) {
            ClearBackground(darkBLue);
            DrawTextEx(font, "Scoreboard", { 350,15 }, 38, 2, BLACK);
            DrawTextEx(font, "Next Piece", { 350,120 }, 38, 2, BLACK);
            DrawTextEx(font, "Holded Piece", { 350,340 }, 38, 2, BLACK);
            DrawRectangleRounded({ 320,60,300,60 }, 0.3, 6, feneryellow);

            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

            char holdlimitText[5];
            sprintf(holdlimitText, "%d", game.HoldLimit);
            DrawTextEx(font, "Remaining Hold: ", { 650,15 }, 38, 2, BLACK);
            DrawTextEx(font, holdlimitText, { 950,15 }, 38, 2, BLACK);


            DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2,65 }, 38, 2, BLACK);
            DrawRectangleRounded({ 320,160,300,180 }, 0.3, 6, feneryellow);
            DrawRectangleRounded({ 320,380,300,200 }, 0.3, 6, feneryellow);
            if (game.gameOver)
            {
                DrawTextEx(font, "!!!GAME OVER!!!", { 10,620 }, 38, 2, BLACK);
            }
            game.Draw();
            EndDrawing();
        }
        if (theme == 3) {
            ClearBackground(purple);
            DrawTextEx(font, "Scoreboard", { 350,15 }, 38, 2, BLACK);
            DrawTextEx(font, "Next Piece", { 350,120 }, 38, 2, BLACK);
            DrawTextEx(font, "Holded Piece", { 350,340 }, 38, 2, BLACK);
            DrawRectangleRounded({ 320,60,300,60 }, 0.3, 6, limegreen);

            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

            char holdlimitText[5];
            sprintf(holdlimitText, "%d", game.HoldLimit);
            DrawTextEx(font, "Remaining Hold: ", { 650,15 }, 38, 2, BLACK);
            DrawTextEx(font, holdlimitText, { 950,15 }, 38, 2, BLACK);


            DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2,65 }, 38, 2, BLACK);
            DrawRectangleRounded({ 320,160,300,180 }, 0.3, 6, limegreen);
            DrawRectangleRounded({ 320,380,300,200 }, 0.3, 6, limegreen);
            if (game.gameOver)
            {
                DrawTextEx(font, "!!!GAME OVER!!!", { 10,620 }, 38, 2, BLACK);
            }
            game.Draw();
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}