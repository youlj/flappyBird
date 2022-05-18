#include "roadItem.h"

#include<QGraphicsScene>
#include<QPainter>
#include<QPropertyAnimation>

extern const int roadHeight=64;
static const int roadWidth=384;
static const int roadMoveInterval=6000;
extern const int winHeight;
extern const int winWidth;
static const char* roadImg=":/src/image/road.png";

RoadItem::RoadItem(QGraphicsScene*scene)
{
    scene->addItem(this);
    move();
}

QRectF RoadItem::boundingRect() const
{
    return QRectF(0,winHeight-roadHeight,winWidth,roadHeight);
}

void RoadItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //需要画两段马路,这样地面移动的时候不会有空出来的位置

    //第一段马路
    painter->drawPixmap(0,winHeight-roadHeight,QPixmap(roadImg),0,0,roadWidth,roadHeight);
    painter->drawPixmap(roadWidth,winHeight-roadHeight,QPixmap(roadImg),0,0,winWidth-roadWidth,roadHeight);

    //第二段马路
    painter->drawPixmap(winWidth,winHeight-roadHeight,QPixmap(roadImg),
                        0,0,roadWidth,roadHeight);
    painter->drawPixmap(winWidth+roadWidth,winHeight-roadHeight,QPixmap(roadImg),
                        0,0,winWidth-roadWidth,roadHeight);
}

void RoadItem::move()
{
    QPropertyAnimation*ani=new QPropertyAnimation(this,"pos",this);
    ani->setLoopCount(-1);//repeat forever
    ani->setDuration(roadMoveInterval);
    ani->setStartValue(QPoint(0,pos().y()));
    ani->setEndValue(QPoint(-winWidth,pos().y()));
    ani->setEasingCurve(QEasingCurve::Linear);
    ani->start();
}
