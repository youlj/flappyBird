#ifndef ROADITEM_H
#define ROADITEM_H

#include<QGraphicsObject>

//马路图元
class RoadItem : public QGraphicsObject
{
public:
    RoadItem(QGraphicsScene*scene);

    //重写
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void move();
};

#endif // ROADITEM_H
