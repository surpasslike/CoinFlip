#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include <QMainWindow>
#include <QPixmap>
#include <QDebug>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);
    int levelIndex;//内部成员属性,记录所选关卡

    //重写paintEvent事件
    void paintEvent(QPaintEvent *);

    //二维数组,维护每个关卡的具体数据
    int gameArray[4][4];

    MyCoin *coinBtn[4][4];

signals:
    void chooseSceneBack();//返回信号

};

#endif // PLAYSCENE_H
