/**
 * @file block.cpp
 * @brief Заголовочный файл, содержащий класс Block.
 */

#include "block.hpp"

// Определения методов класса

/**
 * @brief Конструктор класса Block.
 *
 * Инициализирует объект блока с заданной позицией.
 *
 * @param position Позиция блока на экране.
 */

Block::Block(Vector2 position) {
    this->position = position;
}

/**
 * @brief Отрисовывает блок на экране.
 */

void Block::Draw() {
    DrawRectangle(position.x, position.y, 3, 3, {243, 216, 63, 255});
}

/**
 * @brief Возвращает прямоугольник, определяющий положение и размер блока.
 *
 * @return Прямоугольник с координатами и размерами блока.
 */
Rectangle Block::getRect() {
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 3;
    rect.height = 3;
    return rect;
}