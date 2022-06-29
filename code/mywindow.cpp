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
#include <QPropertyAnimation>
#include <boardwindow.h>
#include <cinemawindow.h>

Game * gameWindow=NULL;
QGraphicsView *view=NULL;
boardWindow *view2 =NULL;
myBtn *quitBtn=NULL;
myBtn *startBtn=NULL;
myBtn *cinemaBtn=NULL;
QGraphicsBlurEffect* ef=NULL;
QGraphicsBlurEffect* ef2=NULL;
pausewindow *pauseWindow =NULL;
newGameSetting *newgameWindow=NULL;
cinemaWindow *cinemamodewindow=NULL;
pressanykeywindow *pakWindow=NULL;
myLabel *startboard;
myLabel *cinemaboard;
myLabel *exitboard;
myLabel *duola;
myLabel *red;
myLabel *gametitle;
QTimer *duolatimer;
QPropertyAnimation *duolaani;



//哆啦A梦弹出
void duolajump(){
    duolaani = new QPropertyAnimation(duola,"geometry");
    duolaani->setDuration(800);
    duolaani->setStartValue(QRect(12,1001,duola->width(),duola->height()));
    duolaani->setEndValue(QRect(12,665,duola->width(),duola->height()));
    duolaani->setEasingCurve(QEasingCurve::OutBounce);
    duolaani->start();
}


//哆啦A梦上下移动
void duolamoving(){

    static int dy=1;
    QTimer::singleShot(800,duola,[=](){
        duolatimer = new QTimer(duola);
        QWidget::connect(duolatimer,&QTimer::timeout,[=](){
            duola->move(duola->x(),duola->y()+dy);
            if(duola->y()>=675) dy=-1;
            else if (duola->y()<=665) dy=1;
        });
        duolatimer->start(90);
    });


}


//控件进入画面的动画
void allmovein(){
    QPropertyAnimation *ani1 = new QPropertyAnimation(startboard,"geometry");
    ani1->setDuration(300);
    ani1->setStartValue(QRect(450,1001,startboard->width(),startboard->height()));
    ani1->setEndValue(QRect(450,750,startboard->width(),startboard->height()));

    QPropertyAnimation *ani2 = new QPropertyAnimation(cinemaboard,"geometry");
    ani2->setDuration(300);
    ani2->setStartValue(QRect(700,1001,cinemaboard->width(),cinemaboard->height()));
    ani2->setEndValue(QRect(700,750,cinemaboard->width(),cinemaboard->height()));

    QPropertyAnimation *ani3 = new QPropertyAnimation(exitboard,"geometry");
    ani3->setDuration(300);
    ani3->setStartValue(QRect(950,1001,exitboard->width(),exitboard->height()));
    ani3->setEndValue(QRect(950,750,exitboard->width(),exitboard->height()));

    QPropertyAnimation *ani4 = new QPropertyAnimation(startBtn,"geometry");
    ani4->setDuration(400);
    ani4->setStartValue(QRect(480,1001,startBtn->width(),startBtn->height()));
    ani4->setEndValue(QRect(480,802,startBtn->width(),startBtn->height()));
    ani4->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation *ani5 = new QPropertyAnimation(cinemaBtn,"geometry");
    ani5->setDuration(400);
    ani5->setStartValue(QRect(724,1001,cinemaBtn->width(),cinemaBtn->height()));
    ani5->setEndValue(QRect(724,797,cinemaBtn->width(),cinemaBtn->height()));
    ani5->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation *ani6 = new QPropertyAnimation(quitBtn,"geometry");
    ani6->setDuration(400);
    ani6->setStartValue(QRect(983,1001,quitBtn->width(),quitBtn->height()));
    ani6->setEndValue(QRect(983,804,quitBtn->width(),quitBtn->height()));
    ani6->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation *ani7 = new QPropertyAnimation(red,"geometry");
    ani7->setDuration(300);
    ani7->setStartValue(QRect(78,0-red->height(),red->width(),red->height()));
    ani7->setEndValue(QRect(78,150,red->width(),red->height()));

    QPropertyAnimation *ani8 = new QPropertyAnimation(gametitle,"geometry");
    ani8->setDuration(400);
    ani8->setStartValue(QRect(335,0-gametitle->height(),gametitle->width(),gametitle->height()));
    ani8->setEndValue(QRect(335,36,gametitle->width(),gametitle->height()));
    ani8->setEasingCurve(QEasingCurve::OutBounce);


    ani1->start();
    ani2->start();
    ani3->start();
    ani4->start();
    ani5->start();
    ani6->start();
    ani7->start();
    ani8->start();
    duolajump();
    duolamoving();

}




void continueGame(){
    duola->hide();
    duola->move(12,1001);
    pauseWindow->hide();    
    gameWindow->continueGame();
    ef->setBlurRadius(0);
    ef->setBlurHints(QGraphicsBlurEffect::AnimationHint);
    ef2->setBlurRadius(0);
    ef2->setBlurHints(QGraphicsBlurEffect::AnimationHint);
}

void backtoMain(){
    newgameWindow->hide();
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
    cinemaBtn->show();
    startboard->show();
    cinemaboard->show();
    exitboard->show();    
    red->show();
    gametitle->show();
    duolatimer->start();
}

void backtoMainfromsetting(){
    newgameWindow->hide();
    startBtn->show();
    quitBtn->show();
    cinemaBtn->show();
    startboard->show();
    cinemaboard->show();
    exitboard->show();
    red->show();
    gametitle->show();
}

void backtoMainfromcinema(){
    cinemamodewindow->hide();
    startBtn->show();
    quitBtn->show();
    cinemaBtn->show();
    startboard->show();
    cinemaboard->show();
    exitboard->show();
    red->show();
    gametitle->show();
}


void tonewgameWindow(){
    startBtn->hide();
    quitBtn->hide();
    cinemaBtn->hide();
    startboard->hide();
    cinemaboard->hide();
    exitboard->hide();    
    red->hide();
    gametitle->hide();
    newgameWindow->show();
    newgameWindow->movein();
}

void tocinemaWindow(){
    startBtn->hide();
    quitBtn->hide();
    cinemaBtn->hide();
    startboard->hide();
    cinemaboard->hide();
    exitboard->hide();
    red->hide();
    gametitle->hide();
    cinemamodewindow->init();
    cinemamodewindow->show();
    cinemamodewindow->movein();
}

void startgame(){
    duola->hide();
    duolatimer->stop();
    duola->move(12,1001);
    view2->init();
    view->show();
    newgameWindow->hide();
    gameWindow->setGlobalVars(newgameWindow->player1Type,newgameWindow->player2Type,
                              newgameWindow->gameFormat,newgameWindow->playerSpeed,
                              newgameWindow->enemyMode);
    gameWindow->start();
    view2->show();
}

void startreview(QString pathstr){
    gameWindow->setRecSrc(pathstr);
    cinemamodewindow->hide();
    view2->init();
    startBtn->hide();
    quitBtn->hide();
    cinemaBtn->hide();
    startboard->hide();
    cinemaboard->hide();
    exitboard->hide();
    duola->hide();
    duolatimer->stop();
    duola->move(12,1001);
    red->hide();
    gametitle->hide();
    view2->show();
    view->show();
    gameWindow->start(true);
}

void endingthegame(int winner){
    gameWindow->saveRecord();
    pauseWindow->init();
    if(winner==1){
        pauseWindow->winmode1();
    }
    else{
        pauseWindow->winmode2();
    }
    pauseWindow->show();

    ef->setBlurRadius(20);
    ef->setBlurHints(QGraphicsBlurEffect::AnimationHint);
    ef2->setBlurRadius(20);
    ef2->setBlurHints(QGraphicsBlurEffect::AnimationHint);
    view->setGraphicsEffect(ef);
    view2->setGraphicsEffect(ef2);

    //qDebug()<<"出现";

    duola->raise();
    duola->show();
    duolajump();
}


myWindow::myWindow(QWidget *parent) : QWidget(parent)
{

    startboard=new myLabel(":/art/button_board.png",this);
    startboard->move(450,1001);
    cinemaboard=new myLabel(":/art/button_board.png",this);
    cinemaboard->move(700,1001);
    exitboard=new myLabel(":/art/button_board.png",this);
    exitboard->move(950,1001);
    red=new myLabel(":/art/red.png",this);
    red->move(78,0-red->height());
    gametitle=new myLabel(":/art/title.png",this);
    gametitle->move(335,0-gametitle->height());


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
//    splash.finish(view);
//    view->move(-11,-45);
    view->move(0,190);
    view->setParent(this);
//    view->show();
    //第二个view
    view2 = new boardWindow(this);
    view2->setFixedSize(1290,1000);
    view2->move(0,0);
    view2->setFocusPolicy(Qt::NoFocus);
    //先不显示
    view->hide();
    view2->hide();

    //game和board的connect
    connect(gameWindow,&Game::updateBigScore,view2,&boardWindow::addscore);
    connect(gameWindow,&Game::updateSmallScore,view2,&boardWindow::addsoccer);
    connect(gameWindow,&Game::updatePlayer1Health,view2,&boardWindow::changehealth1);
    connect(gameWindow,&Game::updatePlayer2Health,view2,&boardWindow::changehealth2);
    connect(gameWindow,&Game::updatePlayer1Power,view2,&boardWindow::changepower1);
    connect(gameWindow,&Game::updatePlayer2Power,view2,&boardWindow::changepower2);
    connect(gameWindow,&Game::addPlayer1Buff,view2,&boardWindow::addbuff1);
    connect(gameWindow,&Game::addPlayer2Buff,view2,&boardWindow::addbuff2);
    connect(gameWindow,&Game::removePlayer1Buff,view2,&boardWindow::removebuff1);
    connect(gameWindow,&Game::removePlayer2Buff,view2,&boardWindow::removebuff2);
    connect(gameWindow,&Game::refreshBoard,view2,&boardWindow::refresh);


    //quit button

    quitBtn = new myBtn("://art/Exit_Btn.png",this);
    quitBtn->move(983,1001);
    quitBtn->sety(804);
    connect(quitBtn, &myBtn::btnClicked, [=](){
        int res = QMessageBox::question(nullptr,"WARNING","Are you sure to exit？", QMessageBox::Yes|QMessageBox::No, QMessageBox::NoButton);
        if(res == QMessageBox::Yes){
            this->close();
        }
    });


    //cinemabutton
    cinemaBtn = new myBtn(":/art/Cinema_Btn.png",this);
    cinemaBtn->move(724,1001);
    cinemaBtn->sety(797);
    connect(cinemaBtn, &myBtn::btnClicked,&tocinemaWindow);


    //start button
    startBtn=new myBtn(":/art/Start_Btn.png",this);
    startBtn->move(480,1001);
    startBtn->sety(802);
    connect(startBtn, &myBtn::btnClicked,&tonewgameWindow);


    //主窗口界面大小
    setFixedSize(1290,1000);


    //暂停时的界面
    pauseWindow=new pausewindow;
    pauseWindow->setFixedSize(this->size());
    pauseWindow->move(0,0);
    pauseWindow->setParent(this);
    pauseWindow->hide();

    //放映厅界面
    cinemamodewindow=new cinemaWindow;
    cinemamodewindow->setFixedSize(this->size());
    cinemamodewindow->move(0,0);
    cinemamodewindow->setParent(this);
    cinemamodewindow->hide();
    connect(cinemamodewindow,&cinemaWindow::backtomain,&backtoMainfromcinema);
    connect(cinemamodewindow,&cinemaWindow::startreview,&startreview);



    //设置esc的connect
    connect(gameWindow,&Game::gameispause,[=](){

        pauseWindow->init();
        pauseWindow->pausemode();
        pauseWindow->show();

        ef->setBlurRadius(20);
        ef->setBlurHints(QGraphicsBlurEffect::AnimationHint);
        ef2->setBlurRadius(20);
        ef2->setBlurHints(QGraphicsBlurEffect::AnimationHint);
        view->setGraphicsEffect(ef);
        view2->setGraphicsEffect(ef2);

        //qDebug()<<"出现";

        duola->raise();
        duola->show();
        duolajump();

    });

    //游戏结束的connect
    connect(gameWindow,&Game::gameOver,&endingthegame);

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
    connect(newgameWindow,&newGameSetting::backtomain,&backtoMainfromsetting);


    //哆啦A梦
    duola = new myLabel("://art/Doraemon_with_PKU.png",this);
    duola->move(12,1001);
    duola->setFocusPolicy(Qt::NoFocus);

    //按任意键继续
    pakWindow=new pressanykeywindow();
    pakWindow->setFixedSize(this->size());
    pakWindow->move(0,0);
    pakWindow->setParent(this);
    pakWindow->setFocus();
    connect(pakWindow,&pressanykeywindow::isclosed,[=](){
        pakWindow->close();
        allmovein();
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
