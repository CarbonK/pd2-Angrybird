#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "lv0.h"

#include <new>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent):
QMainWindow(parent) , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    qApp->installEventFilter(this);

}

MainWindow::~MainWindow(){

    delete scene;
    delete dim;
    delete ui;

}

void MainWindow::showEvent(QShowEvent *){

    dim = new b2World(b2Vec2(0.0f , -9.8f));

    sonar = new CollisionContecter;
    dim->SetContactListener(sonar);

    scene = new QGraphicsScene(0 , 0 , 1280 , 720);
    ui->graphicsView->setScene(scene);

    image.push_back(new QGraphicsPixmapItem(QPixmap(":/Resource/SLING_SHOT_01_BACK.png")));
    image.back()->setPos(150 , 460);
    image.back()->setZValue(1);
    image.push_back(new QGraphicsPixmapItem(QPixmap(":/Resource/SLING_SHOT_01_FRONT.png")));
    image.back()->setPos(122 , 460);
    image.back()->setZValue(3);
    for(QGraphicsPixmapItem *&i : image){scene->addItem(i);}

    Item::setUnit(128 , 72 , size().width() , size().height());

    land.push_back(new Land(dim , QRectF(0 , 600 , 1280 , 120) , QPixmap(":/Resource/PIGLANTIS_GROUND.png") , scene));

    timer = new QTimer;
    timer->start(1000 / 60);
    connect(timer , SIGNAL(timeout()) , this , SLOT(tick()));

    object.push_back(new Object(dim , QRectF(600 , 580 , 80 , 80) , QPixmap(":/Resource/BLOCK_WOOD_4X4_1.png") , scene , timer));
    object.push_back(new Object(dim , QRectF(600 , 500 , 80 , 80) , QPixmap(":/Resource/BLOCK_WOOD_4X4_1.png") , scene , timer));
    object.push_back(new Object(dim , QRectF(800 , 580 , 80 , 80) , QPixmap(":/Resource/BLOCK_WOOD_4X4_1.png") , scene , timer));
    object.push_back(new Object(dim , QRectF(800 , 500 , 80 , 80) , QPixmap(":/Resource/BLOCK_WOOD_4X4_1.png") , scene , timer));
    object.push_back(new Object(dim , QRectF(640 , 480 , 200 , 20) , QPixmap(":/Resource/BLOCK_WOOD_10X1_1.png") , scene , timer));
    object.push_back(new Object(dim , QRectF(600 , 480 , 40 , 20) , QPixmap(":/Resource/BLOCK_WOOD_1_2.png") , scene , timer));
    object.push_back(new Object(dim , QRectF(840 , 480 , 40 , 20) , QPixmap(":/Resource/BLOCK_WOOD_1_2.png") , scene , timer));

    pig.push_back(new Piggie(dim , 690 , 580 , 50 , Piggie::king , scene , timer));

    bird.push_back(new LV0(dim , 145 , 480 , scene , timer));

}

void MainWindow::mousePressEvent(QMouseEvent *event){launcher = event->pos();}

void MainWindow::closeEvent(){emit quitGame();}

bool MainWindow::eventFilter(QObject *, QEvent *event){

    if(event->type() == QEvent::MouseButtonRelease){

        QMouseEvent *e = static_cast<QMouseEvent *>(event);

        float speedMag = 0.3;
        float dis = qSqrt(qPow(e->x() - launcher.x() , 2) + qPow(e->y() - launcher.y() , 2));

        if(dis < 150.0f) bird.front()->setVelocity((launcher.x() - e->x()) * speedMag , (e->y() - launcher.y()) * speedMag);
        else bird.front()->setVelocity(150 * speedMag * (launcher.x() - e->x()) / dis , 150 * speedMag * (e->y() - launcher.y()) / dis);

        bird.front()->setGscale(1);

    }

    return false;

}

void MainWindow::tick(){

    dim->Step(1.0f/60.0f , 6 , 2);
    scene->update();

    for(Object *&i : object){

        if(i != NULL && i->getBody()->IsAwake() && i->getDeathflag()){

            dim->DestroyBody(i->getBody());
            scene->removeItem(i->getExterior());
            delete i;
            i = NULL;

        }

    }

    object.removeAll(NULL);

    for(Piggie *&i :pig){

        if(i != NULL && i->getBody()->IsAwake() && i->getDeathflag()){

            dim->DestroyBody(i->getBody());
            scene->removeItem(i->getExterior());
            delete i;
            i = NULL;

        }

    }

    pig.removeAll(NULL);

    if(bird.front()->getBody()->IsAwake()){

        if(bird.front()->getExterior()->pos().x() < -40 || 1280 < bird.front()->getExterior()->pos().x()){

            dim->DestroyBody(bird.front()->getBody());
            scene->removeItem(bird.front()->getExterior());
            delete bird.front();
            bird.pop_front();
            bird.push_back(new LV0(dim , 145 , 480 , scene , timer));

        }
        else if(bird.front()->getExterior()->pos() != QPointF(145 , 480) && (int)bird.front()->getVelocity().x == 0 && (int)bird.front()->getVelocity().y == 0){

            dim->DestroyBody(bird.front()->getBody());
            scene->removeItem(bird.front()->getExterior());
            delete bird.front();
            bird.pop_front();
            bird.push_back(new LV0(dim , 145 , 480 , scene , timer));

        }

    }

}
