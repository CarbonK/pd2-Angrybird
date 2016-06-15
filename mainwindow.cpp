#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bird_red.h"
#include "land.h"

#include <new>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent):
QMainWindow(parent) , ui(new Ui::MainWindow)
{ui->setupUi(this);}

MainWindow::~MainWindow(){

    delete scene;
    delete dim;
    delete ui;

}

void MainWindow::showEvent(QShowEvent *){

    dim = new b2World(b2Vec2(0.0f , -9.8f));

    scene = new QGraphicsScene(0 , 0 , 800 , 600);
    ui->graphicsView->setScene(scene);

    Item::setUnit(80 , 60 , size().width() , size().height());

    object.push_back(new Land(dim , QRectF(0 , 480 , 800 , 120) , QPixmap(":/Resource/PIGLANTIS_GROUND.png") , scene));

    timer = new QTimer;
    timer->start(1000 / 60);
    connect(timer , SIGNAL(timeout()) , this , SLOT(tick()));

}

void MainWindow::mousePressEvent(QMouseEvent *e){

    qDebug() << e->x() << ',' << e->y();

    object.push_back(new Bird_red(dim , e->x() , e->y() , scene));
    connect(timer , SIGNAL(timeout()) , object.back() , SLOT(paint()));

}

void MainWindow::closeEvent(){emit quitGame();}

void MainWindow::tick(){

    dim->Step(1.0f/60.0f , 6 , 2);
    scene->update();

}
