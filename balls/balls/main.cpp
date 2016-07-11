/* main.cpp:
 *
 */

#include <QApplication>
#include <QTimer>
#include <thread>

#include "view.h"
#include "ball.h"
#include "move.h"
#include "include/config.h"


using namespace std;


/* глобальные переменные */
PtrList balls;
mutex   ballsMutex;

void action();

/*----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View graphicForm;

    graphicForm.setMutex(&ballsMutex);
    graphicForm.setBalls(&balls);

    int borderStart = SIZE_SCENE_W * 0.2;
    int borderStop  = SIZE_SCENE_W * 0.8;

    for (int i = 0; i < 7; i++) {
        PtrBall tmpBall(new Ball());

        tmpBall.get()->setPos(borderStart + rand() % borderStop,
                              borderStart + rand() % borderStop);
        balls.push_back(tmpBall);

        QRectF rect;
        rect.setLeft(tmpBall->getPosX());
        rect.setTop( tmpBall->getPosY());

        QSizeF *size = new QSizeF(tmpBall->getWidth(), tmpBall->getHeight());
        rect.setSize(*size);
        graphicForm.add(new Move(rect, DURATION));
    }

    graphicForm.show();

    QTimer *timer = new QTimer();
    timer->setInterval(INTERVAL);
    timer->setSingleShot(false);
    QObject::connect(timer, SIGNAL(timeout()), &graphicForm,
                     SLOT(updateAnimation()) );

    thread forceField(action);
    forceField.detach();

    timer->start();

    return a.exec();
}

/*----------------------------------------------------------------------------*/
void action()
{
    PtrList::iterator iterBegin1;
    PtrList::iterator iterBegin2;
    PtrList::iterator iterEnd;

    while (true) {
        while (!ballsMutex.try_lock());

        iterEnd = balls.end();

        for (iterBegin1 = balls.begin(); iterBegin1 != iterEnd; iterBegin1++)
            for (iterBegin2 = balls.begin(); iterBegin2 != iterEnd;
                 iterBegin2++)
                iterBegin1->get()->offset(*iterBegin2, TIME);

        for (iterBegin1 = balls.begin(); iterBegin1 != iterEnd; iterBegin1++)
            (*iterBegin1).get()->move();

        ballsMutex.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(INTERVAL));
    }
}


