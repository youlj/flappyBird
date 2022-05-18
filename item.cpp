#include "item.h"

#include<QGraphicsScene>
#include<QTimer>
#include<QPainter>
#include<QPropertyAnimation>

static const int birdSize=45;
static const int flyOffset=200;
static const int imgCount=3;
static const int downInterval=3000;
static const int upInterval=300;
static const char* birdImg=":/src/image/bird%1.png";

Item::Item(QGraphicsScene*scene)
{
    scene->addItem(this);
    scene_=scene;
    flyTimer_=new QTimer(this);
    connect(flyTimer_,&QTimer::timeout,[this]()
    {
         curImg_=(curImg_+1)%imgCount;//0,1,2
         update();//刷新绘图
    });
    flyTimer_->start(flyOffset);
    ani_=new QPropertyAnimation(this,"pos",this);//位置改变动画
    connect(ani_,&QPropertyAnimation::finished,this,&Item::flyFinished);
}

QRectF Item::boundingRect() const
{
    return QRectF(0,scene_->height()/2-birdSize/2,birdSize,birdSize);
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(boundingRect(),QImage(QString(birdImg).arg(curImg_)));
}

bool Item::isCollide()
{
    if(!collidingItems().isEmpty())
    {
        return true;
    }
    return false;
}

void Item::reset()
{
    setPos(0,0);
}

void Item::flyFinished()
{
    ani_->stop();
    ani_->setDuration(downInterval);
    ani_->setEndValue(QPoint(pos().x(),scene_->height()));
    ani_->setEasingCurve(QEasingCurve::InQuad);
    ani_->start();
}

void Item::fly()
{
    ani_->stop();
    ani_->setDuration(upInterval);
    if(pos().y()<=-(scene_->height()/2-birdSize/2))//到达最上端(刚开始pos().y()为0,往上递减)
    {
        ani_->setEndValue(pos());
    }
    else
    {
        ani_->setEndValue(QPoint(pos().x(),pos().y()-birdSize/2));
    }
    ani_->setEasingCurve(QEasingCurve::InQuad);
    ani_->start();
}
