#include "mywindow.h"
#include "game.h"
#include <QSplashScreen>
#include <QGraphicsView>
#include "mybtn.h"
#include "pausewindow.h"
#include <QTimer>
#include <QPainter>
#include<QGraphicsEffect>
#include "newgamesetting.h"
#include "pressanykeywindow.h"
#include "mylabel.h"

Game * gameWindow=NULL;
QGraphicsView *view=NULL;
QGraphicsView *view2 =NULL;
myBtn *quitBtn=NULL;
myBtn *startBtn=NULL;
myBtn *cinemaBtn=NULL;
QGraphicsBlurEffect* ef=NULL;
QGraphicsBlurEffect* ef2=NULL;
pausewindow *pauseWindow =NULL;
newGameSetting *newgameWindow=NULL;
pressanykeywindow *pakWindow=NULL;
myLabel *startboard;
myLabel *cinemaboard;
myLabel *exitboard;
myLabel *duola;
myLabel *red;
myLabel *gametitle;


void continueGame(){
    pauseWindow->hide();
    gameWindow->continueGame();
    ef->setBlurRadius(0);
    ef->setBlurHints(QGraphicsBlurEffect::AnimationHint);
    ef2->setBlurRadius(0);
    ef2->setBlurHints(QGraphicsBlurEffect::AnimationHint);
}

void backtoMain(){
    pauseWindow->hide();
    gameWindow->endGame();
    ef->setBlurRadius(0);
    ef->setBlurHints(QGraphicsBlurEffect::AnimationHint);
    ef2->setBlurRadius(0);
    ef2->setBlurHints(QGraphicsBlurEffect::AnimationHint);
    view->hide();
    view2->hide();
    startBtn->show();
    quitBtn->show();
}

void tonewgameWindow(){
    startBtn->hide();
    quitBtn->hide();
    newgameWindow->show();
}

void startgame(){

    view2->show();
    view->show();
    newgameWindow->hide();
    gameWindow->start();
}


myWindow::myWindow(QWidget *parent) : QWidget(parent)
{
    duola = new myLabel("://art/Doraemon_with_PKU.png",this);
    duola->move(12,665);
    startboard=new myLabel(":/art/button_board.png",this);
    startboard->move(450,750);
    cinemaboard=new myLabel(":/art/button_board.png",this);
    cinemaboard->move(700,750);
    exitboard=new myLabel(":/art/button_board.png",this);
    exitboard->move(950,750);
    red=new myLabel(":/art/red.png",this);
    red->move(78,150);
    gametitle=new myLabel(":/art/title.png",this);
    gametitle->move(335,36);






    setWindowTitle("Game");
    ef = new QGraphicsBlurEffect;
    ef2 = new QGraphicsBlurEffect;
    /* Start */
    QPixmap start(startPNG);
    QSplashScreen splash(start);
    splash.resize(start.size());
    splash.show();

    /* Welcome */
    gameWindow = new Game;

    view = new QGraphicsView;
    view->resize(1290,810);
    view->setScene(gameWindow);
    //view->setWindowTitle("Game");
    view->setBackgroundBrush(QBrush(QPixmap(backgroundPNG)));
    splash.finish(view);
    view->move(-11,-45);
    view->setParent(this);
//    view->show();
    //第二个view
    view2 = new QGraphicsView;
    view2->resize(1290,190);
    view2->setScene(gameWindow->getBoard());
    view2->move(0,810);
    view2->setParent(this);
    view2->setFocusPolicy(Qt::NoFocus);
    //先不显示
    view->hide();
    view2->hide();


    //quit button

    quitBtn = new myBtn("://art/Exit_Btn.png",this);
    quitBtn->move(983,804);
    connect(quitBtn, &myBtn::btnClicked, [=](){
        int res = QMessageBox::question(nullptr,"WARNING","Are you sure to exit？", QMessageBox::Yes|QMessageBox::No, QMessageBox::NoButton);
        if(res == QMessageBox::Yes){
            this->close();
        }
    });
    quitBtn->setParent(this);


    //cinemabutton
    cinemaBtn = new myBtn(":/art/Cinema_Btn.png",this);
    cinemaBtn->move(724,797);

    //start button
    startBtn=new myBtn(":/art/Start_Btn.png",this);
    startBtn->move(480,802);
    connect(startBtn, &myBtn::btnClicked,&tonewgameWindow);
    startBtn->setParent(this);


    //主窗口界面大小
    setFixedSize(1290,1000);


    //暂停时的界面
    pauseWindow=new pausewindow;
    pauseWindow->setFixedSize(this->size());
    pauseWindow->move(0,0);
    pauseWindow->setParent(this);
    pauseWindow->hide();

    //设置esc的connect
    connect(gameWindow,&Game::gameispause,[=](){
        ef->setBlurRadius(20);
        ef->setBlurHints(QGraphicsBlurEffect::AnimationHint);
        ef2->setBlurRadius(20);
        ef2->setBlurHints(QGraphicsBlurEffect::AnimationHint);
        view->setGraphicsEffect(ef);
        view2->setGraphicsEffect(ef2);
        pauseWindow->show();
    });

    //游戏继续
    connect(pauseWindow,&pausewindow::gamecontinue,&continueGame);
    connect(gameWindow,&Game::gamecontinue,&continueGame);
    //游戏退出
    connect(pauseWindow,&pausewindow::close,[=](){
        int res = QMessageBox::question(nullptr,"WARNING","Are you sure to exit？", QMessageBox::Yes|QMessageBox::No, QMessageBox::NoButton);
        if(res == QMessageBox::Yes){
            this->close();
        }
    });
    //返回主窗口
    connect(pauseWindow,&pausewindow::back,&backtoMain);

    //新游戏设置
    newgameWindow=new newGameSetting();
    newgameWindow->setFixedSize(this->size());
    newgameWindow->move(0,0);
    newgameWindow->setParent(this);
    newgameWindow->hide();
    connect(newgameWindow,&newGameSetting::startgame,&startgame);

    //按任意键继续
    pakWindow=new pressanykeywindow();
    pakWindow->setFixedSize(this->size());
    pakWindow->move(0,0);
    pakWindow->setParent(this);
    pakWindow->setFocus();
    connect(pakWindow,&pressanykeywindow::isclosed,[=](){
        pakWindow->close();
        setFocus();
    });


}


void myWindow::keyPressEvent(QKeyEvent *event){
//    qDebug()<<event->key();

    gameWindow->keyPressEvent(event);
}

void myWindow::keyReleaseEvent(QKeyEvent *event){
    gameWindow->keyReleaseEvent(event);
}


void myWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load("://art/main_backgroud.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}
