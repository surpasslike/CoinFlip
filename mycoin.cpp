#include "mycoin.h"
#include <QDebug>
MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret= pix.load(btnImg);
    if(!ret)
    {
        QString str=QString("图片 %1 加载失败").arg(btnImg);
        qDebug()<<str;
        return;
    }

    //设置翻转的金币图形大小
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");//尽量记住这一行,border是边框,0px是0像素
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化一下定时器
    timer1=new QTimer(this);
    timer2=new QTimer(this);

    //监听正面翻反面的信号,并且翻转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        //设置翻转的金币图形大小
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");//尽量记住这一行,border是边框,0px是0像素
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断:如果翻完了,将min重置为1
        if(this->min>this->max)
        {
            this->min=1;
            isAnimation=false;
            timer1->stop();
        }
    });

    //监听反面翻正面的信号,并且翻转金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        //设置翻转的金币图形大小
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");//尽量记住这一行,border是边框,0px是0像素
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断:如果翻完了,将min重置为1
        if(this->max<this->min)
        {
            this->max=8;
            isAnimation=false;
            timer2->stop();
        }
    });
}

//重写按下状态,防止狂点
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}

//改变标志的方法
void MyCoin::changeFlag()
{
    //如果是正面,翻成反面
    if(this->flag)
    {
        timer1->start(30);//每隔30毫秒一发送
        isAnimation=true;//开始做动画了
        this->flag=false;
    }

    //如果是反面,翻成正面
    else
    {
        timer2->start(30);//每隔30毫秒一发送
        isAnimation=true;//开始做动画了
        this->flag=true;
    }
}
