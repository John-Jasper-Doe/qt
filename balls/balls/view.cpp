/* view.cpp: графическое поле
 *
 */

#include "view.h"
#include "include/config.h"


/* ....................................................... Конструктор класса */
View::View(QWidget *parent) : QGraphicsView(parent)
{
    /* создание графической сцены */
    ptrScene = new QGraphicsScene;
    ptrScene->setSceneRect(0, 0, SIZE_SCENE_W, SIZE_SCENE_H);
    setScene(ptrScene);
    setRenderHint(QPainter::Antialiasing);
    setMouseTracking(true);
}

/* ............................................................... Диструктор */
View::~View() { ptrScene->clear(); }

/* ......................................................... Добавить элемент */
void View::add(QGraphicsItem* item) { ptrScene->addItem(item); }

/* .................................... Установка списка графических объектов */
void View::setBalls(PtrList *list) { ptrList = list; }

/* ..................................................... Установка блокировки */
void View::setMutex(mutex *m) { ptrMutex = m; }

/* ...................................................... Обнавление анимации */
void View::updateAnimation()
{
    /* ожидание блакировки */
    while (!ptrMutex->try_lock());

    QList<QGraphicsItem *>           graphicBalls   = ptrScene->items();
    QList<QGraphicsItem *>::iterator graphIterBegin = graphicBalls.begin();
    QList<QGraphicsItem *>::iterator graphIterEnd   = graphicBalls.end();

    PtrList::iterator iter = ptrList->begin();

    Move *ptrMoveElem;
    Ball  ball;

    /* перерисовка графики */
    while (graphIterBegin != graphIterEnd) {
        ptrMoveElem = static_cast<Move*>(*graphIterBegin);
        ball        = *iter->get();

        QRectF *ptrRect = new QRectF(ball.getPosX(),  ball.getPosY(),
                                     ball.getWidth(), ball.getHeight());

        ptrMoveElem->moveTo(*ptrRect);

        graphIterBegin++;
        iter++;
    }
    ptrMutex->unlock();
}

/* ................................................... События по щелчку мыши */
void View::mousePressEvent(QMouseEvent *event)
{
    /* Обработка события от правой клавиши */
    if (event->buttons() == Qt::RightButton) {
        QPointF temp = mapToScene(event->pos());

        /* новый указатель на "шар" */
        PtrBall newBall(new Ball(temp.x(), temp.y()));
        ptrList->push_back(newBall);

        /* графическое представление объекта */
        QSizeF *size = new QSizeF(SIZE_BALL_W, SIZE_BALL_H);
        QRectF rect;

        rect.setTopLeft(temp);
        rect.setSize(*size);

        Move *newGrpahicBall = new Move(rect, DURATION);
        ptrScene->addItem(newGrpahicBall);
    }

    if (event->buttons() == Qt::LeftButton) {
        QPointF temp = mapToScene(event->pos());

        QList<QGraphicsItem *>           graphicBalls   = ptrScene->items();
        QList<QGraphicsItem *>::iterator graphIterBegin = graphicBalls.begin();
        QList<QGraphicsItem *>::iterator graphIterEnd   = graphicBalls.end();

        PtrList::iterator iter = ptrList->begin();

        Ball  ball;

        int mousePosX = temp.x();
        int mousePosY = temp.y();

        while (graphIterBegin != graphIterEnd) {
            ball        = *iter->get();

            int ballBorderX1 = ball.getPosX();
            int ballBorderX2 = ball.getPosX() + ball.getWidth();
            int ballBorderY1 = ball.getPosY();
            int ballBorderY2 = ball.getPosY() + ball.getHeight();

            if (ballBorderX1 < mousePosX && mousePosX < ballBorderX2 &&
                ballBorderY1 < mousePosY && mousePosY < ballBorderY2) {
//                graphicBalls.erase(graphIterBegin);

            }

            graphIterBegin++;
            iter++;
        }
    }

    QGraphicsView::mousePressEvent(event);
}
