/* ball.cpp
 *
 * Описание класса "Ball".
 *
 */

#include <cmath>

#include "ball.h"
#include "include/config.h"


/* ------------------------------------------------------- Конструктор класса */
Ball::Ball() { initBall(); }

/* ----------------------------------------- Конструктор класса с параметрами */
Ball::Ball(double posX, double posY)
{
    initBall();
    setPos(posX, posY);
}

/* --------------------------------------------- Установка начальных значений */
void Ball::initBall()
{
    posX_   = DEF_POS_X;
    posY_   = DEF_POS_Y;
    dX_     = DEF_DX;
    dY_     = DEF_DY;
    active_ = true;
    width_  = SIZE_BALL_W;
    height_ = SIZE_BALL_H;
}

/* --------------------------------------------------------- Проверка статуса */
bool Ball::isActive() { return active_; }

/* -------------------------------------------------- Взять позицию шара по Х */
double Ball::getPosX() { return posX_; }

/* -------------------------------------------------- Взять позицию шара по У */
double Ball::getPosY() { return posY_; }

/* --------------------------------------------------- Установка позиции шара */
void Ball::setPos(double posX, double posY)
{
    posX_ = posX;
    posY_ = posY;
}

/* --------------------------------------------------------- Установка ширины */
void Ball::setWidth(int width) { width_ = width; }

/* --------------------------------------------------------- Установка высоты */
void Ball::setHeight(int height) { height_ = height; }

/* ---------------------------------------------------------- Получить ширину */
int Ball::getWidth() { return width_; }

/* ---------------------------------------------------------- Получить высоту */
int Ball::getHeight() { return height_; }

/* ------------------------------------------------------------ Смещение шара */
void Ball::move()
{
    posX_ += dX_;
    posY_ += dY_;
}

/* -------------------------------------------- Расчет смещения с учетом силы */
void Ball::offset(PtrBall otherBall, int time)
{
    if (!active_ || otherBall.get() == this) return;

    /* Расчет расстояния между шарами */
    double otherX = otherBall->getPosX();
    double otherY = otherBall->getPosY();
    double r      = sqrt(pow(otherX - posX_, 2) + pow(otherY - posY_, 2));

    /* Расчет силы */
    double force  = 1 / r - 1 / (r * r);

    /* Смещение по координатам */
    dX_ += (force * (otherX - posX_) / r) * time;
    dY_ += (force * (otherY - posY_) / r) * time;
}
