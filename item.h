#ifndef ITEM_H
#define ITEM_H

#include<QGraphicsObject>

class QPropertyAnimation;

//小鸟图元
class Item : public QGraphicsObject
{
    Q_OBJECT
public:
    Item(QGraphicsScene*scene);

    //重写
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    bool isCollide();//碰撞检测
    void reset();

public slots:
    void flyFinished();//下降
    void fly();//上升

private:
    QGraphicsScene*scene_=nullptr;//图元(小鸟)所在的场景
    QTimer* flyTimer_=nullptr;//切换小鸟图片,产生小鸟在动的错觉
    QPropertyAnimation* ani_=nullptr;//飞行动画
    int curImg_=0;//当前小鸟图片序号

//public:
//    QMetaObject::Connection flyConnect;//小鸟飞行用
};

#endif // ITEM_H
