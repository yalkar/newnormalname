/**
 * @file block.hpp
 * @brief Заголовочный файл, содержащий класс Block.
 */

#pragma once
#include "raylib.h"

/**
 * @class Block
 * @brief Класс, представляющий блок в игре.
 */

class Block {
    public:
    /**
    * @brief Конструктор класса Block.
    *
    * Инициализирует объект блока с заданной позицией.
    *
    * @param position Позиция блока на экране.
    */
        Block(Vector2 position);
     /**
     * @brief Отрисовывает блок на экране.
     */
        void Draw();
    /**
     * @brief Возвращает прямоугольник, определяющий положение и размер блока.
     *
     * @return Прямоугольник с координатами и размерами блока.
     */
        Rectangle getRect();
    private:
       /**
     * @brief Позиция блока на экране.
     */
        Vector2 position;
};