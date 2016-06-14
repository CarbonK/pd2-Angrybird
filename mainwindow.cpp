#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bird.h"
#include "land.h"

#include <new>

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

    Item::setUnit(32 , 24 , size().width() , size().height());

    object.push_back(new Land(dim , QRectF(0 , 600 - 58 , 800 , 58) , QPixmap(":/Resource/BACKGROUND_10_LAYER_3_ITEM_1.png") , scene));

    timer = new QTimer;
    timer->start(1000 / 60);
    connect(timer , SIGNAL(timeout()) , this , SLOT(tick()));

    object.push_back(new Bird(dim , 400 , 300 , 25 , QPixmap(":/Resource/BIRD_RED.png") , scene));
    connect(timer , SIGNAL(timeout()) , object.back() , SLOT(paint()));

}

void MainWindow::tick(){

    dim->Step(1.0f/60.0f , 6 , 2);
    scene->update();

}
