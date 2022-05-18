#include "widget.h"
#include"item.h"
#include"roadItem.h"
#include"pipeItem.h"

#include<QGraphicsScene>
#include<QGraphicsView>
#include<QPushButton>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QKeyEvent>
#include<QTimer>

extern const int winHeight=448;
extern const int winWidth=600;
static const int btnWidth=104;
static const int btnHeight=58;
static const int collideInterval=50;
static const int bgMoveSpeed=1;
static const int bgImgWidth=384;
static const int bgMoveInterval=10;
static const char* startBtnImg=":/src/image/startButton.png";
static const char* startMusic=":/src/sound/welcome.mp3";
static const char* overMusic=":/src/sound/gameover.wav";
static const char* gameMusic=":/src/sound/background.mp3";
static const char* bgImg=":/src/image/background.png";

//借助图形视图框架 QGraphicsView(视图)、QGraphicsScene(场景)、QGraphicsItem(图元)

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(winWidth,winHeight);

    scene_=new QGraphicsScene(0,0,width(),height(),this);
    QGraphicsView*view=new QGraphicsView(scene_,this);
    view->setStyleSheet("background:transparent;");

    startBtn=new QPushButton(this);
    startBtn->move(winWidth/2-btnWidth/2,winHeight/2-btnHeight/2);
    startBtn->setIcon(QIcon(startBtnImg));
    startBtn->setIconSize(QSize(btnWidth,btnHeight));
    startBtn->setStyleSheet("border:none;");
    connect(startBtn,&QPushButton::clicked,[this]()
    {
        startBtn->hide();
        startGame();
    });

    player=new QMediaPlayer(this);
    //player->setMedia(QUrl(QString("qrc%1").arg(startMusic)));
    playList=new QMediaPlaylist(this);
    playList->addMedia(QUrl(QString("qrc%1").arg(startMusic)));
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playList);
    player->play();

    collideTimer=new QTimer(this);
    collideTimer->setInterval(collideInterval);
    connect(collideTimer,&QTimer::timeout,[this]()
    {
        if(birdItem->isCollide())
        {
            player->stop();
            playList->clear();
            playList->addMedia(QUrl(QString("qrc%1").arg(overMusic)));
            player->play();

            //birdItem->disconnect(birdItem->flyConnect);//断开信号与槽,这样小鸟就不会持续下落
            birdItem->hide();//隐藏小鸟
            startBtn->show();
            isStart=false;
            collideTimer->stop();
        }
    });

    bgMoveTimer=new QTimer(this);
    connect(bgMoveTimer,&QTimer::timeout,[this]()
    {
       update();//调用paintEvent,移动背景图片
    });
    bgMoveTimer->start(bgMoveInterval);

    birdItem=new Item(scene_);
    pipeItem=new PipeItem(scene_);
    roadItem=new RoadItem(scene_);
}

Widget::~Widget()
{
    delete birdItem;
    birdItem=nullptr;
    delete pipeItem;
    pipeItem=nullptr;
    delete roadItem;
    roadItem=nullptr;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(isStart&&event->key()==Qt::Key_Space&&birdItem)
    {
        birdItem->fly();
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(QRect(0,0,winWidth,winHeight),QPixmap(bgImg),QRect(bgCurPos,0,winWidth,winHeight));

    //待改进,如果窗体宽度很大,但是背景图片宽度很小,则仍有空白,应该整个while循环,暂时想不到
    if(bgImgWidth-bgCurPos<winWidth)//填补空白
    {
        painter.drawPixmap(QRect(bgImgWidth-bgCurPos,0,winWidth-(bgImgWidth-bgCurPos),winHeight),
                           QPixmap(bgImg),QRect(0,0,winWidth-(bgImgWidth-bgCurPos),winHeight));
        if(bgImgWidth<winWidth-(bgImgWidth-bgCurPos))//还有空白
        {
            painter.drawPixmap(QRect(bgImgWidth-bgCurPos+bgImgWidth,0,winWidth-(bgImgWidth-bgCurPos+bgImgWidth),winHeight),
                               QPixmap(bgImg),QRect(0,0,winWidth-(bgImgWidth-bgCurPos+bgImgWidth),winHeight));
        }
    }

    if((bgCurPos+=bgMoveSpeed)>=bgImgWidth)
    {
        bgCurPos=0;
    }
}

void Widget::startGame()
{
    isStart=true;
    player->stop();
    playList->clear();
    playList->addMedia(QUrl(QString("qrc%1").arg(gameMusic)));
    player->play();

    if(!birdItem->isVisible())//游戏结束后小鸟不可见,重新开始游戏时再显示小鸟
    {
        birdItem->reset();
        birdItem->show();
    }

    birdItem->flyFinished();//往下掉
    collideTimer->start();
}

