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

    object.push_back(new Object(dim , QPointF(600 , 580) , Object::P4X4 , scene , timer));
    object.push_back(new Object(dim , QPointF(600 , 500) , Object::P4X4 , scene , timer));
    object.push_back(new Object(dim , QPointF(800 , 580) , Object::P4X4 , scene , timer));
    object.push_back(new Object(dim , QPointF(800 , 500) , Object::P4X4 , scene , timer));
    object.push_back(new Object(dim , QPointF(640 , 480) , Object::P10X1 , scene , timer));
    object.push_back(new Object(dim , QPointF(600 , 480) , Object::P2X1 , scene , timer));
    object.push_back(new Object(dim , QPointF(840 , 480) , Object::P2X1 , scene , timer));

    pig.push_back(new Piggie(dim , QPointF(690 , 580) , Piggie::king , scene , timer));

    birdType.push_back(lv0);
    birdType.push_back(accelerator);

    genBird();

}

void MainWindow::mousePressEvent(QMouseEvent *event){

    if(bird->getExterior()->pos() == QPointF(145 , 480)) launcher = event->pos();
    else if(!bird->getCD()) bird->feature();

}

void MainWindow::closeEvent(){emit quitGame();}

bool MainWindow::eventFilter(QObject *, QEvent *event){

    if(event->type() == QEvent::MouseButtonRelease){

        if(bird->getExterior()->pos() == QPointF(145 , 480)){

            QMouseEvent *e = static_cast<QMouseEvent *>(event);

            float speedMag = 0.3;
            float dis = qSqrt(qPow(e->x() - launcher.x() , 2) + qPow(e->y() - launcher.y() , 2));

            if(dis < 150.0f) bird->setVelocity((launcher.x() - e->x()) * speedMag , (e->y() - launcher.y()) * speedMag);
            else bird->setVelocity(150 * speedMag * (launcher.x() - e->x()) / dis , 150 * speedMag * (e->y() - launcher.y()) / dis);

            bird->setGscale(1);

        }

    }

    return false;

}

void MainWindow::genBird(){

    if(birdType.empty()) return;

    switch(birdType.front()){

        case lv0:

            bird = new LV0(dim , QPointF(145 , 480) , scene , timer);
            birdType.pop_front();
            break;

        case accelerator:

            bird = new Accelerator(dim , QPointF(145 , 480) , scene , timer);
            birdType.pop_front();
            break;

    }

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

    if(bird != NULL && bird->getBody()->IsAwake()){

        if(bird->getExterior()->pos().x() < -40 || 1280 < bird->getExterior()->pos().x()){

            dim->DestroyBody(bird->getBody());
            scene->removeItem(bird->getExterior());
            delete bird;
            bird = NULL;

        }
        else if(bird->getExterior()->pos() != QPointF(145 , 480) && (int)bird->getVelocity().x == 0 && (int)bird->getVelocity().y == 0){

            dim->DestroyBody(bird->getBody());
            scene->removeItem(bird->getExterior());
            delete bird;
            bird = NULL;

        }

    }
    else if(bird == NULL) genBird();

}
