#include "mywindow.h"
#include "game.h"
#include <QSplashScreen>
#include <QGraphicsView>
#include "mybtn.h"
#include <QTimer>
#include <QPainter>


const int PATHLEN = 150;
const char startPNG[PATHLEN] = ":/art/start.png";
const char welcomePNG[PATHLEN] = ":/art/welcome.jpg";
const char backgroundPNG[PATHLEN] = ":/art/soccerField.png";
Game * gameWindow=NULL;
QGraphicsView *view=NULL;
QGraphicsView *view2 =NULL;
myBtn *quitBtn=NULL;
myBtn *startBtn=NULL;

myWindow::myWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Game");

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

    //设置esc的connect
    QObject::connect(gameWindow,&Game::gameispause,[=](){
        QMessageBox::information(this,"注意","游戏被暂停了");
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
    pix.load("://art/background.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}
