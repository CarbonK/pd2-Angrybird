#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bird_red.h"
#include "item.h"
#include "land.h"

#include <Box2D/Box2D.h>
#include <QGraphicsScene>
#include <QList>
#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>

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

    private:

        Ui::MainWindow *ui;

        b2World *dim;
        QGraphicsScene *scene;
        QList<Item *> object;
        QTimer *timer;
        Land *land;

    signals:

        void quitGame();

    private slots:

        void tick();

};

#endif // MAINWINDOW_H
