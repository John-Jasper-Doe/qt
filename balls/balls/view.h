/* view.h: Описание графического поля
 *
 */

#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

#include <mutex>

#include "ball.h"
#include "move.h"


using namespace std;

/* .......................................................... Описание класса */
class View : public QGraphicsView
{
    Q_OBJECT

  public:
    explicit  View(QWidget *parent = 0);
    virtual  ~View();

    void add(QGraphicsItem *);
    void setBalls(PtrList *);
    void setMutex(mutex *);

  protected:
    QGraphicsScene  *ptrScene;
    PtrList         *ptrList;
    mutex           *ptrMutex;

    virtual void mousePressEvent(QMouseEvent *);


  public slots:
    void updateAnimation();
};

#endif // VIEW_H
