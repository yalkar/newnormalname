/**
 * @file mysteryship.cpp
 * @brief Файл реализации, содержащий методы класса MysteryShip.
 */

#include "mysteryship.hpp"

/**
 * @brief Конструктор класса MysteryShip.
 *
 * Инициализирует объект загадочного корабля, загружает изображение и устанавливает начальные параметры.
 */

MysteryShip::MysteryShip()
{
    image = LoadTexture("../Graphics/mystery.png");
    alive = false;
}

/**
 * @brief Деструктор класса MysteryShip.
 *
 * Освобождает ресурсы, загруженные для загадочного корабля.
 */

MysteryShip::~MysteryShip() {
    UnloadTexture(image);
}

/**
 * @brief Появление загадочного корабля на экране.
 *
 * Устанавливает корабль в начальное положение и активирует его.
 */

void MysteryShip::Spawn() {
    position.y = 90;
    int side = GetRandomValue(0, 1);

    if(side == 0) {
        position.x = 25;
        speed = 3;
    } else {
        position.x = GetScreenWidth() - image.width - 25;
        speed = -3;
    }
    alive = true;
}

/**
 * @brief Возвращает прямоугольник, определяющий положение и размер загадочного корабля.
 *
 * @return Прямоугольник с координатами и размерами загадочного корабля.
 */

Rectangle MysteryShip::getRect()
{
    if(alive){
        return {position.x, position.y, float(image.width), float(image.height)};
    } else {
        return {position.x, position.y, 0, 0};
    }
}

/**
 * @brief Обновляет состояние загадочного корабля.
 *
 * Перемещает корабль и проверяет его состояние.
 */

void MysteryShip::Update() {
    if(alive) {
        position.x += speed;
        if(position.x > GetScreenWidth() - image.width -25 || position.x < 25) {
            alive = false;
        }
    }
}

/**
 * @brief Отрисовывает загадочный корабль на экране.
 */

void MysteryShip::Draw() {
    if(alive) {
        DrawTextureV(image, position, WHITE);
    }
}