#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QBitmap>
#include <QTimer>
#include <QDebug>
#include <QPen>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ballVelocity=new QPointF(5,3);
    scale=sqrt(5*5+3*3);
    *ballVelocity/=scale;
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ball = scene->addEllipse(50,50,20,20,QPen(Qt::black),QBrush(Qt::red));
    QPointF ballcenter=ball->pos() + QPointF(50,50);
    ballcenter.setX(ballcenter.x()+ball->boundingRect().width()/2);
    ballcenter.setY(ballcenter.y()+ball->boundingRect().width()/2);
    qDebug()<<"Ball center: "<<ballcenter.x()<<"\t"<<ballcenter.y();
    /*QPixmap pixCar("D:\\Qt\\Labs\\laba7\\car.png");
    car=scene->addPixmap(pixCar.scaled(300,250));
    car->setPos(100,100);
    car->setFlags(QGraphicsItem::ItemIsMovable);
    car->setZValue(1);
    car->setData(0,"Car");
    QPixmap pixMan("D:\\Qt\\Labs\\laba7\\man.png");
    man=scene->addPixmap(pixMan.scaled(100,75));
    man->setFlags(QGraphicsItem::ItemIsMovable);
    man->setPos(180,168);
    man->setData(0,"Man");*/
    wheel1 = scene->addEllipse(173,251,50,50,QPen(Qt::black),QBrush(Qt::black));
    wheel2 = scene->addEllipse(319,251,50,50,QPen(Qt::black),QBrush(Qt::black));
    wheel1->setFlags(QGraphicsItem::ItemIsMovable);
    wheel1->setData(0,"Wheel");
    wheel1->setData(1,"1");
    wheel2->setFlags(QGraphicsItem::ItemIsMovable);
    wheel2->setData(0,"Wheel");
    wheel2->setData(1,"2");

    float walls[4][4] = {{0,0,20,500},
                         {20,0,620,20},
                         {625,0,20,500},
                         {20,480,620,20}};
    QString dir[4]={"Left","Up","Right","Down"};
    for (int i =0; i < 4; i++){
        QGraphicsRectItem* pWall = scene->addRect(QRectF(walls[i][0],walls[i][1],walls[i][2],walls[i][3]),QPen(Qt::NoPen),QBrush(Qt::green));
        pWall->setData(0,dir[i]);
    }
    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(BallGo()));
    timer->start(20);
}

void MainWindow::BallGo(){
    //QPointF pos = ball->pos();
    ball->moveBy(ballVelocity->x()*scale,ballVelocity->y()*scale);
    QList<QGraphicsItem*> collisions = scene->collidingItems(ball);
    foreach (QGraphicsItem* it, collisions) {
        if(it==ball) continue;
        if(it->data(0)=="Left") ballVelocity->setX(-ballVelocity->x());
        else if(it->data(0)=="Up") ballVelocity->setY(-ballVelocity->y());
        else if(it->data(0)=="Right") ballVelocity->setX(-ballVelocity->x());
        else if(it->data(0)=="Down") ballVelocity->setY(-ballVelocity->y());
        /*else if(it->data(0)=="Car"){
            QPointF ballpos=ball->pos();
            QPointF carpos=car->pos();
            if(ballpos.x()<carpos.y()) dx=-dx;

        }*/
        else if(it->data(0)=="Wheel"){
            ball->moveBy(-ballVelocity->x()*scale,-ballVelocity->y()*scale);
            QPointF wheelcenter;
            QPointF ballcenter=ball->pos() + QPointF(50,50);
            ballcenter.setX(ballcenter.x()+ball->boundingRect().width()/2);
            ballcenter.setY(ballcenter.y()+ball->boundingRect().width()/2);
            //qDebug()<<"Ball center: "<<ballcenter.x()<<"\t"<<ballcenter.y();
            if(it->data(1)=="1"){
                wheelcenter=wheel1->pos() + QPointF(173,251);
                wheelcenter.setX(wheelcenter.x()+wheel1->boundingRect().width()/2);
                wheelcenter.setY(wheelcenter.y()+wheel1->boundingRect().width()/2);
                scene->addEllipse(wheelcenter.x()-5,wheelcenter.y()-5,10,10,QPen(Qt::NoPen),QBrush(Qt::green));
                //qDebug()<<"Wheel center: "<<wheelcenter.x()<<"\t"<<wheelcenter.y();
            }
            else if(it->data(1)=="2"){
                wheelcenter=wheel2->pos() + QPointF(319,251);
                wheelcenter.setX(wheelcenter.x()+wheel2->boundingRect().width()/2);
                wheelcenter.setY(wheelcenter.y()+wheel2->boundingRect().width()/2);
                scene->addEllipse(wheelcenter.x()-5,wheelcenter.y()-5,10,10,QPen(Qt::NoPen),QBrush(Qt::green));
            }
            QPointF centerVec = ballcenter-wheelcenter;
            qDebug()<<"Center vector: "<<centerVec.x()<<"\t"<<centerVec.y()<<"\n";
            qreal dot = QPointF::dotProduct(*ballVelocity,centerVec);
            qDebug()<<"Dot product: "<<dot;
            qreal len = centerVec.x()*centerVec.x() + centerVec.y()*centerVec.y();
            qDebug()<<"Length squared: "<<len;
            QPointF newVel = *ballVelocity - centerVec * (dot / len);
            qDebug()<<"Old velocity: "<<ballVelocity->x()<<"\t"<<ballVelocity->y()<<"\n";
            qDebug()<<"New velocity: "<<newVel.x()<<"\t"<<newVel.y()<<"\n";
            //qDebug()<<"New velocity length: "<<sqrt(newVel.x()*newVel.x()+newVel.y()*newVel.y());
            *ballVelocity = newVel;
            ball->moveBy(ballVelocity->x()*scale,ballVelocity->y()*scale);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
