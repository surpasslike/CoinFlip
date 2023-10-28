#include "playscene.h"

//PlayScene::PlayScene(QWidget *parent)
//    : QMainWindow{parent}
//{

//}
PlayScene::PlayScene(int levelNum)
{
    QString str=QString("进入了第%1关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex=levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle(str);

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
        qDebug()<<"游戏点击了返回按钮";

        //做一个延时的返回
        QTimer::singleShot(500,this,[=](){
            //告诉主场景,我返回了,主场景要监听ChooseLevelScene的返回按钮
            emit this->chooseSceneBack();;
        });

    });

    //显示当前第几关
    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font    ;
    font.setFamily("宋体");
    font.setPointSize(20);
    QString str1=QString("Level: %1").arg(this->levelIndex);
    //将字体设计到标签控件中
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30,this->height()-50,120,50);//一下子设置位置和大小,等价于move和setFixedSize

    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }

    //显示金币背景图案
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            //绘制背景图片
            QLabel* label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(57 + i*50,200+j*50);

            //创建金币
            QString str;
            if(this->gameArray[i][j]==1)
            {
                //显示金币
                str=":/res/Coin0001.png";
            }
            else
            {
                //显示金币
                str=":/res/Coin0008.png";
            }

            MyCoin *coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(59 + i*50,204+j*50);

            //给金币带属性赋值
            coin->posX=i;
            coin->posY=j;
            coin->flag=this->gameArray[i][j];//1是正面,2是反面

            //将金币放入金币的二维数组里面,以便于后期的维护
            coinBtn[i][j]=coin;

            //点击金币进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                coin->changeFlag();
                this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;

                //翻转周围的金币,延时翻转
                QTimer::singleShot(300,this,[=](){
                    //右侧翻转的条件
                    if(coin->posX+1<=3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY]=gameArray[coin->posX+1][coin->posY]==0?1:0;
                    }
                    //左侧翻转的条件
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY]=gameArray[coin->posX-1][coin->posY]==0?1:0;
                    }
                    //上侧翻转的条件
                    if(coin->posY+1<=3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1]=gameArray[coin->posX][coin->posY+1]==0?1:0;
                    }
                    //下侧翻转的条件
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1]=gameArray[coin->posX][coin->posY-1]==0?1:0;
                    }
                });
            });
        }
    }
}

//画背景和表头
void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
