#ifndef MYCOIN_H
#define MYCOIN_H
#include <QTimer>
#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);//btnImg代表传入的是金币路径还是银币路径

    //金币的属性
    int posX;//x坐标位置
    int posY;//y坐标位置
    bool flag;//正反标识

    //改变标志的方法
    void changeFlag();
    QTimer *timer1;//正面翻反面的定时器
    QTimer *timer2;//反面翻正面的定时器
    int min=1;
    int max=8;

    //执行动画的标志,防止狂点
    bool isAnimation=false;

    //重写按下状态,防止狂点
    void mousePressEvent(QMouseEvent *e);

    //是否胜利的标志
    bool isWin=true;


signals:

};

#endif // MYCOIN_H
