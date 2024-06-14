/**
 * @file main.cpp
 * @brief Основной файл для игры Space Invaders на C++.
 */
#include "game.hpp"
#include <string>
#include <raylib.h>

/**
 * @brief Форматирует число с ведущими нулями.
 *
 * @param number Число для форматирования.
 * @param width Ширина форматируемой строки (количество символов).
 * @return Отформатированная строка с ведущими нулями.
 */

std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

/**
 * @brief Главная функция игры.
 *
 * Инициализирует окно, аудиоустройство, шрифты, текстуры и игровой объект. Запускает основной игровой цикл, в котором обрабатываются ввод, обновление состояния и отрисовка.
 * По завершении игры освобождает все ресурсы.
 * 
 * @return 0 в случае успешного завершения программы.
 */

int main() {
    // Цвета для отрисовки  
    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    // Отступы и размеры окна
    int offset = 50;
    int windowWidth = 750;
    int windowHeight = 700;

    // Инициализация окна
    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "C++ Space Invaders");

    // Инициализация аудиоустройства
    InitAudioDevice();

    // Загрузка шрифта и текстуры космического корабля
    Font font = LoadFontEx("../Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("../Graphics/spaceship.png");

    // Установка целевого FPS
    SetTargetFPS(60);

    // Создание объекта игры
    Game game;

    // Основной игровой цикл
    while (WindowShouldClose() == false) {
        // Обновление музыки
        UpdateMusicStream(game.music);
        // Обработка ввода и обновление состояния игры
        game.HandleInput();
        game.Update();
        // Начало рисования
        BeginDrawing();
        // Очистка фона
        ClearBackground(grey);
        // Отрисовка рамки и линии
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);
        // Отображение текущего состояния игры (уровень или конец игры)
        if (game.run) {
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        } else {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
        }
        // Отрисовка оставшихся жизней (космических кораблей)
        float x = 50.0;
        for (int i = 0; i < game.lives; i++) {
            DrawTextureV(spaceshipImage, {x, 745}, WHITE);
            x += 50;
        }
        // Отрисовка текущего счета
        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);
        // Отрисовка рекорда
        DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, yellow);
        std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
        DrawTextEx(font, highscoreText.c_str(), {655, 40}, 34, 2, yellow);
        // Отрисовка игровых объектов
        game.Draw();
        // Конец рисования
        EndDrawing();
    }
    // Закрытие окна и освобождение аудиоустройства
    CloseWindow();
    CloseAudioDevice();
}