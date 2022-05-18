#ifndef PIPEITEM_H
#define PIPEITEM_H

#include<QGraphicsObject>

//柱子图元
class PipeItem : public QGraphicsObject
{
public:
    PipeItem(QGraphicsScene*scene);

    //重写
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QPainterPath shape()const override;//辅助碰撞检测

    void move();

private:
    QGraphicsScene*scene_=nullptr;
    int upHeight=0;//上边柱子高度
    int downHeight=0;//下边柱子高度
};

#endif // PIPEITEM_H
