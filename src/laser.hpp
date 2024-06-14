/**
 * @file laser.hpp
 * @brief Заголовочный файл, содержащий класс Laser.
 */
#pragma once
#include <raylib.h>

/**
 * @class Laser
 * @brief Класс, представляющий лазер в игре.
 */

class Laser {
    public:
    /**
     * @brief Конструктор класса Laser.
     *
     * Инициализирует объект лазера с заданной позицией и скоростью.
     *
     * @param position Начальная позиция лазера.
     * @param speed Скорость движения лазера.
     */
        Laser(Vector2 position, int speed);
    /**
     * @brief Обновляет состояние лазера.
     *
     * Перемещает лазер по экрану в зависимости от его скорости.
     */
        void Update();
    /**
     * @brief Отрисовывает лазер на экране.
     */
        void Draw();
    /**
     * @brief Возвращает прямоугольник, определяющий положение и размер лазера.
     *
     * @return Прямоугольник с координатами и размерами лазера.
     */
        Rectangle getRect();
    /**
     * @brief Состояние лазера.
     *
     * true, если лазер активен, иначе false.
     */
        bool active;
     /**
     * @brief Позиция лазера на экране.
     */
        Vector2 position;
    /**
     * @brief Скорость движения лазера.
     */
        int speed;
    private:
};