/* ball.h: Класс "Ball"
 */

#ifndef BALL_H
#define BALL_H

#include <cstdlib>
#include <memory>
#include <list>


using namespace std;

class Ball;

/* Определим тип указателя на наш класс */
typedef      shared_ptr<Ball>   PtrBall;
typedef list<shared_ptr<Ball>>  PtrList;

/* --------------------------------------------------- Описание объекта "Шар" */
class Ball
{
  private:
        double  posX_;
        double  posY_;
        double  dX_;
        double  dY_;
        bool    active_;
        int     width_;
        int     height_;

  public:
        Ball();
        Ball(double, double);

        void    initBall();
        bool    isActive();

        void    setPos(double, double);
        void    setWidth(int);
        void    setHeight(int);

        double  getPosX();
        double  getPosY();
        int     getWidth();
        int     getHeight();

        void    move();
        void    offset(PtrBall, int);
};

#endif // BALL_H
