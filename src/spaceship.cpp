/**
 * @file spaceship.cpp
 * @brief Файл реализации, содержащий методы класса Spaceship.
 */

#include "spaceship.hpp"

/**
 * @brief Конструктор класса Spaceship.
 *
 * Инициализирует объект космического корабля с начальной позицией и загружает ресурсы.
 */

Spaceship::Spaceship() {
    image = LoadTexture("../Graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height - 100;
    lastFireTime = 0.0;
    laserSound = LoadSound("../Sounds/laser.ogg");
}

/**
 * @brief Деструктор класса Spaceship.
 *
 * Освобождает ресурсы, загруженные для космического корабля.
 */


Spaceship::~Spaceship() {
    UnloadTexture(image);
    UnloadSound(laserSound);
}

/**
 * @brief Отрисовывает космический корабль на экране.
 */

void Spaceship::Draw() {
    DrawTextureV(image, position, WHITE);
}

/**
 * @brief Перемещает космический корабль влево.
 */
void Spaceship::MoveLeft() {
    position.x -= 7;
    if (position.x < 25) {
        position.x = 25;
    }
}

/**
 * @brief Перемещает космический корабль вправо.
 */

void Spaceship::MoveRight() {
    position.x += 7;
    if (position.x > GetScreenWidth() - image.width - 25) {
        position.x = GetScreenWidth() - image.width - 25;
    }
}

/**
 * @brief Стреляет лазером из космического корабля.
 */
void Spaceship::FireLaser() {
    if (GetTime() - lastFireTime >= 0.35) {
        lasers.push_back(Laser({position.x + image.width / 2 - 2, position.y}, -6));
        lastFireTime = GetTime();
        PlaySound(laserSound);
    }
}

/**
 * @brief Возвращает прямоугольник, определяющий положение и размер космического корабля.
 *
 * @return Прямоугольник с координатами и размерами космического корабля.
 */

Rectangle Spaceship::getRect() {
    return {position.x, position.y, float(image.width), float(image.height)};
}

/**
 * @brief Сбрасывает позицию космического корабля и очищает список лазеров.
 */

void Spaceship::Reset() {
    position.x = (GetScreenWidth() - image.width) / 2.0f;
    position.y = GetScreenHeight() - image.height - 100;
    lasers.clear();
}
