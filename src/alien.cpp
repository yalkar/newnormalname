/**
 * @file alien.cpp
 * @brief Заголовочный файл, содержащий класс Alien.
 */

#include "alien.hpp"

/**
 * @brief Статический массив текстур для изображений инопланетян.
 */

Texture2D Alien::alienImages[3] = {};

/**
 * @brief Конструктор класса Alien.
 *
 * Инициализирует объект инопланетянина с заданным типом и позицией. Загружает изображение инопланетянина,
 * если оно еще не загружено.
 *
 * @param type Тип инопланетянина (1, 2 или 3).
 * @param position Позиция инопланетянина на экране.
 */

Alien::Alien(int type, Vector2 position)
{
    this -> type = type;
    this -> position = position;

    if(alienImages[type -1].id == 0){

    switch (type) {
        case 1:
            alienImages[0] = LoadTexture("../Graphics/alien_1.png");
            break;
        case 2:
            alienImages[1] = LoadTexture("../Graphics/alien_2.png");
            break;
        case 3: 
            alienImages[2] = LoadTexture("../Graphics/alien_3.png");
            break;
        default:
            alienImages[0] = LoadTexture("../Graphics/alien_1.png");
            break;
    }
}
}

/**
 * @brief Отрисовывает изображение инопланетянина на экране.
 */

void Alien::Draw() {
    DrawTextureV(alienImages[type - 1], position, WHITE);
}

/**
 * @brief Возвращает тип инопланетянина.
 *
 * @return Тип инопланетянина (1, 2 или 3).
 */

int Alien::GetType() {
    return type;
}

/**
 * @brief Выгружает изображения инопланетян из памяти.
 */

void Alien::UnloadImages()
{
    for(int i = 0; i < 4; i++) {
        UnloadTexture(alienImages[i]);
    }
}

/**
 * @brief Возвращает прямоугольник, определяющий положение и размер инопланетянина.
 *
 * @return Прямоугольник с координатами и размерами инопланетянина.
 */

Rectangle Alien::getRect()
{
    return {position.x, position.y,
    float(alienImages[type - 1].width),
    float(alienImages[type - 1].height)
    };
}

/**
 * @brief Обновляет позицию инопланетянина.
 *
 * @param direction Направление движения инопланетянина по оси X.
 */

void Alien::Update(int direction) {
    position.x += direction;
}
