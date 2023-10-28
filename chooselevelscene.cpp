#include "chooselevelscene.h"
#include <QPixmap>
#include <QMenuBar>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QString>
ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //配置选择关卡场景
    this->setFixedSize(320,588);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar *bar=menuBar();
    setMenuBar(bar);

    //创建菜单栏里面的开始菜单
    QMenu *startMenu= bar->addMenu("开始");

    //添加开始下面的退出功能
    QAction* quitAction= startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回按钮后
    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"点击了返回按钮";

        //做一个延时的返回
        QTimer::singleShot(500,this,[=](){
            //告诉主场景,我返回了,主场景要监听ChooseLevelScene的返回按钮
            emit this->chooseSceneBack();;
        });
    });

    //创建选择关卡按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton *menuBtn=new MyPushButton(":/res/LevelIcon.png","");
        menuBtn->setParent(this);
        menuBtn->move(i%4*70+25,i/4*70+130);

        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
            QString str=QString("您选择的是第%1关").arg(i+1);
            qDebug()<<str;

            //进入到这一关的游戏场景,也就是PlayScene类里面
            this->hide();//首先隐藏起来本界面(选择关卡界面)
            play=new PlayScene(i+1);//创建游戏的场景
            play->show();//显示游戏场景

            //监听play界面的返回按钮的信号
            connect(play,&PlayScene::chooseSceneBack,[=](){
                delete play;
                play=NULL;
                this->show();//重新显示选择场景
            });
        });

        //设置按钮格式
        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(i%4*70+25,i/4*70+130);

        //设置label上面文字的对齐方式
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        //设置让鼠标进行穿透  51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);//记住这一行
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//设置一个画家
    QPixmap pix;//设置一个画板,也就是这个界面
    pix.load(":/res/OtherSceneBg.png");//加载背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");//加载标题
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
