#include "mywindow.h"
#include "game.h"
#include <QSplashScreen>
#include <QGraphicsView>
#include "mybtn.h"
#include "pausewindow.h"
#include <QTimer>
#include <QPainter>
#include<QGraphicsEffect>

Game * gameWindow=NULL;
QGraphicsView *view=NULL;
QGraphicsView *view2 =NULL;
myBtn *quitBtn=NULL;
myBtn *startBtn=NULL;
QGraphicsBlurEffect* ef=NULL;
QGraphicsBlurEffect* ef2=NULL;
pausewindow *pauseWindow =NULL;

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

myWindow::myWindow(QWidget *parent) : QWidget(parent)
{
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

    quitBtn = new myBtn(":/art/quitgame.png",this);
    quitBtn->move((gameWindow->width()-100)/2,400);
    QObject::connect(quitBtn, &QPushButton::clicked, [=](){
        int res = QMessageBox::question(nullptr,"WARNING","Are you sure to exit？", QMessageBox::Yes|QMessageBox::No, QMessageBox::NoButton);
        if(res == QMessageBox::Yes){

            this->close();
        }

    });
    quitBtn->setParent(this);

    //start button
    startBtn=new myBtn("://art/startgame.png",this);
    startBtn->move((gameWindow->width()-100)/2,300);
    QObject::connect(startBtn, &myBtn::clicked, [=](){
        startBtn->move((gameWindow->width()-100)/2,300);
        QTimer::singleShot(100,this,[=](){
            startBtn->hide();
            quitBtn->hide();

            view2->show();
            view->show();
            gameWindow->start();

        });
    });
    startBtn->setParent(this);
    setFixedSize(1290,1000);


    //暂停时的界面
    pauseWindow=new pausewindow;
    pauseWindow->setFixedSize(this->size());
    pauseWindow->move(0,0);
    pauseWindow->setParent(this);
    pauseWindow->hide();

    //设置esc的connect
    QObject::connect(gameWindow,&Game::gameispause,[=](){
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
    connect(pauseWindow,&pausewindow::close,[=](){this->close();});
    //返回主窗口
    connect(pauseWindow,&pausewindow::back,&backtoMain);
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
    pix.load("://art/background.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}
