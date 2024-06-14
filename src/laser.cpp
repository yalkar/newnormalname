/**
 * @file laser.cpp
 * @brief Файл реализации, содержащий методы класса Laser.
 */

#include "laser.hpp"
#include <iostream>

/**
 * @brief Конструктор класса Laser.
 *
 * Инициализирует объект лазера с заданной позицией и скоростью.
 *
 * @param position Начальная позиция лазера.
 * @param speed Скорость движения лазера.
 */

Laser::Laser(Vector2 position, int speed) {
    this->position = position;
    this->speed = speed;
    active = true;
}

/**
 * @brief Отрисовывает лазер на экране.
 */

void Laser::Draw() {
    if (active)
        DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
}

/**
 * @brief Возвращает прямоугольник, определяющий положение и размер лазера.
 *
 * @return Прямоугольник с координатами и размерами лазера.
 */

Rectangle Laser::getRect() {
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}

/**
 * @brief Обновляет состояние лазера.
 *
 * Перемещает лазер по экрану в зависимости от его скорости. Деактивирует лазер, если он выходит за границы экрана.
 */

void Laser::Update() {
    position.y += speed;
    if (active) {
        if (position.y > GetScreenHeight() - 100 || position.y < 25) {
            active = false;
        }
    }
}