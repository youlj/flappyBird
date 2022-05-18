#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Item;
class PipeItem;
class RoadItem;
class QGraphicsScene;
class QPushButton;
class QMediaPlayer;
class QMediaPlaylist;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    //重写
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void startGame();

private:
    QGraphicsScene*scene_=nullptr;
    QPushButton*startBtn=nullptr;
    QMediaPlayer*player=nullptr;
    QMediaPlaylist*playList=nullptr;
    Item*birdItem=nullptr;//图元(小鸟)
    PipeItem*pipeItem=nullptr;//柱子
    RoadItem*roadItem=nullptr;//马路
    bool isStart=false;//是否开始游戏
    QTimer*collideTimer=nullptr;//检测碰撞
    int bgCurPos=0;//背景图片当前游标
    QTimer* bgMoveTimer=nullptr;//管理背景图片移动
};
#endif // WIDGET_H
