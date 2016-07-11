/* move.h: Описание класса "Move"
 *
 */


#ifndef MOVE_H
#define MOVE_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QPropertyAnimation>


/* ................................................... Описание класса "Move" */
class Move: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(QRectF rect READ rect WRITE setRect)

  public:
    Move(const QRectF &, int , QObject *parent = 0);
    void moveTo(const QRectF &);

  private:
    int animationSpeed_;
};

#endif // MOVE_H
