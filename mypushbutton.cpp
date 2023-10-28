#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
MyPushButton::MyPushButton(QString normalImg,QString pressImag)//类的声明带默认参数，实现不带，否则报no matching function for call to
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImag;

    QPixmap pix;//拿到一张图片
    bool ret = pix.load(normalImg);//加载一张图,图的地址为normalImg
    if(!ret){qDebug()<<"图片加载失败"; return;}

    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());//固定大小为pix原来的宽高

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");//尽量记住这一行,border是边框,0px是0像素

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

//向上跳
void MyPushButton::zoom1()
{
    //创建动态对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");

    //设置动画事件间隔
    animation->setDuration(200);//200毫秒间隔

    //起始位置
    animation->setStartValue(QRect( this->x(),this->y(),this->width(),this->height()  ));

    //结束位置
    animation->setEndValue(QRect( this->x(),this->y()+10,this->width(),this->height()  ));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();

}

//向下跳
void MyPushButton::zoom2()
{
    //创建动态对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");

    //设置动画事件间隔
    animation->setDuration(200);//200毫秒间隔

    //起始位置
    animation->setStartValue(QRect( this->x(),this->y()+10,this->width(),this->height()  ));

    //结束位置
    animation->setEndValue(QRect( this->x(),this->y(),this->width(),this->height()  ));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}


//重写按钮的 按下和释放 事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(pressImgPath!="")//传入的按下图片不为空,说明需要有按下状态,需要切换图片
    {
        QPixmap pix;//拿到一张图片
        bool ret = pix.load(this->pressImgPath);//加载一张图
        if(!ret){qDebug()<<"图片加载失败"; return;}

        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());//固定大小为pix原来的宽高

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");//尽量记住这一行,border是边框,0px是0像素

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}


void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(pressImgPath!="")//传入的按下图片不为空,说明需要有按下状态,需要为初始的第一个图片
    {
        QPixmap pix;//拿到一张图片
        bool ret = pix.load(this->normalImgPath);//加载一张图
        if(!ret){qDebug()<<"图片加载失败"; return;}

        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());//固定大小为pix原来的宽高

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");//尽量记住这一行,border是边框,0px是0像素

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);
}





