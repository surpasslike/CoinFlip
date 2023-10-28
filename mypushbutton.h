#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //构造函数 参数1正常显示的图片路径  参数2按下后显示的图片路径
    MyPushButton(QString normalImg,QString pressImag="");//pressImag默认为空

    //成员属性 保存用户传入的默认显示路径 以及按下后显示的图片路径
    QString normalImgPath;
    QString pressImgPath;

    //弹跳特效,向上跳和向下跳
    void zoom1();
    void zoom2();

    //重写按钮的 按下和释放 事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

};

#endif // MYPUSHBUTTON_H
