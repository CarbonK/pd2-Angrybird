#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "item.h"

#include <Box2D/Box2D.h>
#include <QGraphicsScene>
#include <QList>
#include <QMainWindow>
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

    private:

        Ui::MainWindow *ui;

        b2World *dim;
        QGraphicsScene *scene;
        QList<Item *> object;
        QTimer *timer;

    signals:

        void quitGame();

    private slots:

        void tick();

};

#endif // MAINWINDOW_H
