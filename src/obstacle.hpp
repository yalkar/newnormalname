/**
 * @file obstacle.hpp
 * @brief Заголовочный файл, содержащий класс Obstacle.
 */

#include "block.hpp"
#pragma once
#include <vector>

/**
 * @class Obstacle
 * @brief Класс, представляющий препятствие, состоящее из блоков.
 */

class Obstacle {
    public:
    /**
     * @brief Конструктор класса Obstacle.
     *
     * Инициализирует объект препятствия с заданной позицией и создает блоки на основе сетки.
     *
     * @param position Позиция препятствия на экране.
     */
        Obstacle(Vector2 position);
    /**
     * @brief Отрисовывает препятствие на экране.
     */
        void Draw();
    /**
     * @brief Позиция препятствия на экране.
     */
        Vector2 position;
    /**
     * @brief Вектор, содержащий блоки, составляющие препятствие.
     */
        std::vector<Block> blocks;
    
    /**
     * @brief Статическая сетка, определяющая форму препятствия.
     */
        static std::vector<std::vector<int>> grid;
    private:
    // Здесь могут быть добавлены приватные члены класса, если потребуется.
};