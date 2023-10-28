#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置固定大小
    setFixedSize(320,588);

    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币小游戏");

    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //开始按钮实现
    MyPushButton *startBtn=new MyPushButton(":/res/MenuSceneStartButton.png","");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //实例化一个选择关卡场景
    chooseScene =new ChooseLevelScene;//*****************************************************************

    //监听返回按钮的信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        chooseScene->hide();//将选择关卡隐藏
        this->show();//重新显示主场景
    });

    connect(startBtn,&MyPushButton::clicked,[=](){//******************************************************
        qDebug()<<"点击了开始";

        //做一个弹起的特效
        startBtn->zoom1();
        startBtn->zoom2();

        //"延时"500毫秒进入到选择关卡场景
        QTimer::singleShot(500,this,[=](){
            //首先隐藏自身(也就是第一页)
            this->hide();//*******************************************************************************
            //显示选择关卡场景
            chooseScene->show();//************************************************************************
        });
    });
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//设置画家
    QPixmap pix;//设置画板
    pix.load(":/res/PlayLevelSceneBg.png");//加载本地图片
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//0,0是插入的位置,this->是为了适配为的本窗口大小

    //画一个背景上面的图标
    pix.load(":/res/Title.png");
    //缩放一下这个图标
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);

}

MainScene::~MainScene()
{
    delete ui;
}

