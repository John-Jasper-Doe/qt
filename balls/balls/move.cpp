/* move.cpp:
 *
 */

#include "move.h"


/* ...................................................... Конструктор каласса */
Move::Move(const QRectF &rect, int animationSpeed, QObject *parent):
    QObject(parent), QGraphicsEllipseItem(rect)
{
    this->setFlags(QGraphicsItem::ItemIsMovable);
    this->animationSpeed_ = animationSpeed;
}

/* .................................................... Настройка перемещения */
void Move::moveTo(const QRectF &rect)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "rect");

    animation->setEndValue(rect);
    animation->setDuration(animationSpeed_);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
