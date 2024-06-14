/**
 * @file game.cpp
 * @brief Файл реализации, содержащий методы класса Game.
 */

#include "game.hpp"
#include <iostream>
#include <fstream>

/**
 * @brief Конструктор класса Game.
 *
 * Инициализирует игровой объект, загружает ресурсы и устанавливает начальные параметры.
 */

Game::Game() {
    music = LoadMusicStream("../Sounds/music.ogg");
    explosionSound = LoadSound("../Sounds/explosion.ogg");
    PlayMusicStream(music);
    InitGame();
}

/**
 * @brief Деструктор класса Game.
 *
 * Освобождает ресурсы, загруженные для игры.
 */

Game::~Game() {
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
}

/**
 * @brief Обновляет состояние игры.
 *
 * Вызывается в основном игровом цикле для обновления состояния всех игровых элементов.
 */

void Game::Update() {
    if (run) {

        double currentTime = GetTime();
        if (currentTime - timeLastSpawn > mysteryShipSpawnInterval) {
            mysteryship.Spawn();
            timeLastSpawn = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }

        for (auto &laser: spaceship.lasers) {
            laser.Update();
        }

        MoveAliens();

        AlienShootLaser();

        for (auto &laser: alienLasers) {
            laser.Update();
        }

        DeleteInactiveLasers();

        mysteryship.Update();

        CheckForCollisions();
    } else {
        if (IsKeyDown(KEY_ENTER)) {
            Reset();
            InitGame();
        }
    }
}

/**
 * @brief Отрисовывает все игровые элементы на экране.
 */

void Game::Draw() {
    spaceship.Draw();

    for (auto &laser: spaceship.lasers) {
        laser.Draw();
    }

    for (auto &obstacle: obstacles) {
        obstacle.Draw();
    }

    for (auto &alien: aliens) {
        alien.Draw();
    }

    for (auto &laser: alienLasers) {
        laser.Draw();
    }

    mysteryship.Draw();
}

/**
 * @brief Обрабатывает ввод пользователя.
 *
 * Вызывается в основном игровом цикле для обработки ввода с клавиатуры и других устройств.
 */

void Game::HandleInput() {
    if (run) {
        if (IsKeyDown(KEY_LEFT)) {
            spaceship.MoveLeft();
        } else if (IsKeyDown(KEY_RIGHT)) {
            spaceship.MoveRight();
        } else if (IsKeyDown(KEY_SPACE)) {
            spaceship.FireLaser();
        }
    }
}

/**
 * @brief Удаляет неактивные лазеры из вектора лазеров.
 */

void Game::DeleteInactiveLasers() {
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
        if (!it->active) {
            it = spaceship.lasers.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = alienLasers.begin(); it != alienLasers.end();) {
        if (!it->active) {
            it = alienLasers.erase(it);
        } else {
            ++it;
        }
    }
}

/**
 * @brief Создает вектор препятствий для игры.
 *
 * @return Вектор препятствий.
 */

std::vector <Obstacle> Game::CreateObstacles() {
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

    for (int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
    }
    return obstacles;
}

/**
 * @brief Создает вектор инопланетян для игры.
 *
 * @return Вектор инопланетян.
 */

std::vector <Alien> Game::CreateAliens() {
    std::vector <Alien> aliens;
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 11; column++) {

            int alienType;
            if (row == 0) {
                alienType = 3;
            } else if (row == 1 || row == 2) {
                alienType = 2;
            } else {
                alienType = 1;
            }

            float x = 75 + column * 55;
            float y = 110 + row * 55;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}

/**
 * @brief Перемещает всех инопланетян в текущем направлении.
 */

void Game::MoveAliens() {
    for (auto &alien: aliens) {
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25) {
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 25) {
            aliensDirection = 1;
            MoveDownAliens(4);
        }

        alien.Update(aliensDirection);
    }
}

/**
 * @brief Перемещает всех инопланетян вниз на заданное расстояние.
 *
 * @param distance Расстояние перемещения вниз.
 */

void Game::MoveDownAliens(int distance) {
    for (auto &alien: aliens) {
        alien.position.y += distance;
    }
}

/**
 * @brief Инопланетяне стреляют лазерами.
 */

void Game::AlienShootLaser() {
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien &alien = aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type - 1].width / 2,
                                     alien.position.y + alien.alienImages[alien.type - 1].height}, 6));
        timeLastAlienFired = GetTime();
    }
}

/**
 * @brief Проверяет столкновения между игровыми объектами.
 */

void Game::CheckForCollisions() {
    // Лазеры космического корабля

    for (auto &laser: spaceship.lasers) {
        auto it = aliens.begin();
        while (it != aliens.end()) {
            if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                PlaySound(explosionSound);
                if (it->type == 1) {
                    score += 100;
                } else if (it->type == 2) {
                    score += 200;
                } else if (it->type == 3) {
                    score += 300;
                }
                checkForHighscore();

                it = aliens.erase(it);
                laser.active = false;
            } else {
                ++it;
            }
        }

        for (auto &obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }

        if (CheckCollisionRecs(mysteryship.getRect(), laser.getRect())) {
            mysteryship.alive = false;
            laser.active = false;
            score += 500;
            checkForHighscore();
            PlaySound(explosionSound);
        }
    }

    // Инопланетные лазеры

    for (auto &laser: alienLasers) {
        if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
            laser.active = false;
            lives--;
            if (lives == 0) {
                GameOver();
            }
        }

        for (auto &obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }
    }

    // Столкновение инопланетян с препятствием

    for (auto &alien: aliens) {
        for (auto &obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
                    it = obstacle.blocks.erase(it);
                } else {
                    it++;
                }
            }
        }

        if (CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
            GameOver();
        }
    }
}

/**
 * @brief Завершает игру, обрабатывая ситуацию "Game Over".
 */

void Game::GameOver() {
    run = false;
}

/**
 * @brief Инициализирует игру, устанавливая начальные параметры и загружая ресурсы.
 */

void Game::InitGame() {
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    timeLastSpawn = 0.0;
    lives = 3;
    score = 0;
    highscore = loadHighscoreFromFile();
    run = true;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
}

/**
 * @brief Проверяет и обновляет рекордный счет.
 */

void Game::checkForHighscore() {
    if (score > highscore) {
        highscore = score;
        saveHighscoreToFile(highscore);
    }
}

/**
 * @brief Сохраняет рекордный счет в файл.
 *
 * @param highscore Рекордный счет для сохранения.
 */

void Game::saveHighscoreToFile(int highscore) {
    std::ofstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open()) {
        highscoreFile << highscore;
        highscoreFile.close();
    } else {
        std::cerr << "Failed to save highscore to file" << std::endl;
    }
}

/**
 * @brief Загружает рекордный счет из файла.
 *
 * @return Загруженный рекордный счет.
 */

int Game::loadHighscoreFromFile() {
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open()) {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    } else {
        std::cerr << "Failed to load highscore from file." << std::endl;
    }
    return loadedHighscore;
}

/**
 * @brief Сбрасывает состояние игры.
 */

void Game::Reset() {
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}
