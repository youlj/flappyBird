#include "pipeItem.h"

#include<QGraphicsScene>
#include<QPainter>
#include<QPropertyAnimation>
#include<QTime>

static const int pipeWidth=70;
static const int pipeHeight=100;
static const int pipeImgHeight=250;
static const int pipeMoveInterval=3000;
static const int pipeHeightOffset=50;
static const char* pipeUpImg=":/src/image/tubeup.png";
static const char* pipeDownImg=":/src/image/tubedown.png";
extern const int winWidth;
extern const int winHeight;
extern const int roadHeight;

PipeItem::PipeItem(QGraphicsScene*scene):upHeight{pipeHeight},downHeight{pipeHeight}
{
    scene->addItem(this);
    scene_=scene;
    move();
}

QRectF PipeItem::boundingRect() const
{
    return QRectF(scene_->width(),0,pipeWidth,scene_->height()-roadHeight);
}

void PipeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(scene_->width(),0,QPixmap(pipeUpImg),0,pipeImgHeight-upHeight,pipeWidth,upHeight);
    painter->drawPixmap(scene_->width(),scene_->height()-roadHeight-downHeight,
                        QPixmap(pipeDownImg),0,0,pipeWidth,downHeight);
}

QPainterPath PipeItem::shape()const
{
    QPainterPath path;
    path.addRect(QRectF(scene_->width(),0,pipeWidth,upHeight));
    path.addRect(QRectF(scene_->width(),scene_->height()-roadHeight-downHeight,pipeWidth,downHeight));
    return path;
}

void PipeItem::move()
{
    QPropertyAnimation*ani=new QPropertyAnimation(this,"pos",this);
    ani->setDuration(pipeMoveInterval);
    ani->setLoopCount(-1);
    ani->setStartValue(QPoint(0,pos().y()));//参照于boundingRect()
    ani->setEndValue(QPoint(-scene_->width()-pipeWidth,pos().y()));
    ani->start();

    //每循环一次改变柱子高度
    qsrand(QTime::currentTime().msec());
    connect(ani,&QPropertyAnimation::currentLoopChanged,[this]()
    {
        upHeight=qrand()%pipeHeightOffset+pipeHeight;
        downHeight=qrand()%pipeHeightOffset+pipeHeight;
    });
}
