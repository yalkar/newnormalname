/**
 * @file game.hpp
 * @brief Заголовочный файл, содержащий класс Game.
 */

#pragma once

#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"

/**
 * @class Game
 * @brief Класс, представляющий основную игровую логику и состояние игры.
 */

class Game {
public:
    /**
     * @brief Конструктор класса Game.
     *
     * Инициализирует игровой объект, загружает ресурсы и устанавливает начальные параметры.
     */
    Game();

    /**
    * @brief Деструктор класса Game.
    *
    * Освобождает ресурсы, загруженные для игры.
    */
    ~Game();

    /**
     * @brief Отрисовывает все игровые элементы на экране.
     */
    void Draw();

    /**
     * @brief Обновляет состояние игры.
     *
     * Вызывается в основном игровом цикле для обновления состояния всех игровых элементов.
     */
    void Update();

    /**
     * @brief Обрабатывает ввод пользователя.
     *
     * Вызывается в основном игровом цикле для обработки ввода с клавиатуры и других устройств.
     */
    void HandleInput();

    /**
     * @brief Флаг, указывающий, запущена ли игра.
     */
    bool run;
    /**
     * @brief Количество жизней игрока.
     */
    int lives;
    /**
     * @brief Текущий счет игрока.
     */
    int score;
    /**
     * @brief Рекордный счет.
     */
    int highscore;
    /**
     * @brief Музыкальный трек, воспроизводимый во время игры.
     */
    Music music;

    /**
* @brief Удаляет неактивные лазеры из вектора лазеров.
*/
    void DeleteInactiveLasers();

    /**
     * @brief Создает вектор препятствий для игры.
     *
     * @return Вектор препятствий.
     */
    std::vector <Obstacle> CreateObstacles();

    /**
     * @brief Создает вектор инопланетян для игры.
     *
     * @return Вектор инопланетян.
     */
    std::vector <Alien> CreateAliens();

    /**
     * @brief Перемещает всех инопланетян в текущем направлении.
     */
    void MoveAliens();

    /**
     * @brief Перемещает всех инопланетян вниз на заданное расстояние.
     *
     * @param distance Расстояние перемещения вниз.
     */
    void MoveDownAliens(int distance);

    /**
     * @brief Инопланетяне стреляют лазерами.
     */
    void AlienShootLaser();

    /**
     * @brief Проверяет столкновения между игровыми объектами.
     */
    void CheckForCollisions();

    /**
     * @brief Завершает игру, обрабатывая ситуацию "Game Over".
     */
    void GameOver();

    /**
     * @brief Сбрасывает состояние игры.
     */
    void Reset();

    /**
     * @brief Инициализирует игру, устанавливая начальные параметры и загружая ресурсы.
     */
    void InitGame();

    /**
     * @brief Проверяет и обновляет рекордный счет.
     */
    void checkForHighscore();

    /**
     * @brief Сохраняет рекордный счет в файл.
     *
     * @param highscore Рекордный счет для сохранения.
     */
    void saveHighscoreToFile(int highscore);/**
     * @brief Загружает рекордный счет из файла.
     *
     * @return Загруженный рекордный счет.
     */
    int loadHighscoreFromFile();

    /**
     * @brief Космический корабль игрока.
     */
    Spaceship spaceship;
    /**
     * @brief Вектор препятствий.
     */
    std::vector <Obstacle> obstacles;
    /**
     * @brief Вектор инопланетян.
     */
    std::vector <Alien> aliens;
    /**
     * @brief Направление движения инопланетян.
     */
    int aliensDirection;
    /**
     * @brief Вектор лазеров, выпущенных инопланетянами.
     */
    std::vector <Laser> alienLasers;
    /**
     * @brief Интервал времени между выстрелами лазеров инопланетян.
     */
    constexpr static float alienLaserShootInterval = 0.35;
    /**
     * @brief Время последнего выстрела инопланетянина.
     */
    float timeLastAlienFired;
    /**
     * @brief Загадочный корабль.
     */
    MysteryShip mysteryship;
    /**
     * @brief Интервал времени между появлениями загадочного корабля.
     */
    float mysteryShipSpawnInterval;
    /**
     * @brief Время последнего появления загадочного корабля.
     */
    float timeLastSpawn;
    /**
     * @brief Звук взрыва.
     */
    Sound explosionSound;
private:

};