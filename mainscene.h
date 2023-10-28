#ifndef MAINSCENE_H
#define MAINSCENE_H
#include "chooselevelscene.h"
#include <QMainWindow>
#include "mypushbutton.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //重写paintEvent事件,画出背景图
    void paintEvent(QPaintEvent *);//画画的第一步


    ChooseLevelScene *chooseScene;//选择关卡场景


private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
