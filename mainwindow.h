#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bird.h"
#include "accelerator.h"
#include "collisioncontecter.h"
#include "item.h"
#include "land.h"
#include "piggie.h"
#include "object.h"

#include <Box2D/Box2D.h>
#include <QGraphicsScene>
#include <QList>
#include <QMainWindow>
#include <QMouseEvent>
#include <QQueue>
#include <QTimer>
#include <QtMath>

namespace Ui{class MainWindow;}

class MainWindow:
public QMainWindow
{

    Q_OBJECT

    public:

        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void showEvent(QShowEvent *);
        void mousePressEvent(QMouseEvent *);
        void closeEvent();
        bool eventFilter(QObject *, QEvent *);

        enum{lv0 , accelerator};

    private:

        Ui::MainWindow *ui;

        b2World *dim;
        Bird *bird;
        CollisionContecter *sonar;
        QGraphicsScene *scene;
        QList<Land *> land;
        QList<Piggie *> pig;
        QList<QGraphicsPixmapItem *> image;
        QList<Object *> object;
        QPointF launcher;
        QQueue<int> birdType;
        QTimer *timer;

        void genBird();

    signals:

        void quitGame();

    private slots:

        void tick();

};

#endif // MAINWINDOW_H
