#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QPainter>
#include <QMainWindow>
#include <QPaintEvent>
#include "playscene.h"
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //游戏场景指针
    PlayScene *play;


signals:
    //写一个自定义的信号,告诉主场景点击了返回
    void chooseSceneBack();


};

#endif // CHOOSELEVELSCENE_H
