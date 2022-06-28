#include "pausewindow.h"
#include <QPainter>
#include "mybtn.h"
#include "mylabel.h"
#include<QTimer>

myBtn *backBtn=NULL;
myBtn *continueBtn = NULL;
myBtn *exitBtn=NULL;
myLabel *pausebg;
myLabel *duolapause;
myLabel *duolaend;
myLabel *p1win;
myLabel *p2win;

pausewindow::pausewindow(QWidget *parent) : QWidget(parent)
{
    pausebg=new myLabel("://art/test.png",this);
    pausebg->move(0,0);

    p1win = new myLabel("://art/player1win.png",this);
    p1win->move(520,125);
    p2win = new myLabel("://art/player2win.png",this);
    p2win->move(520,125);

    backBtn=new myBtn(":/art/back.png",this);
    continueBtn=new myBtn(":/art/continue.png",this);
    exitBtn= new myBtn(":/art/exit.png",this);
    duolapause = new myLabel("://art/gamepause.png",this);
    duolapause->move(100,250);
    duolaend = new myLabel("://art/end.png",this);
    duolaend->move(100,250);



    connect(continueBtn,&myBtn::btnClicked,[=](){
        emit gamecontinue();
        init();
    });

    connect(exitBtn,&myBtn::btnClicked,[=](){
        emit close();
    });

    connect(backBtn,&myBtn::btnClicked,[=](){
        emit back();
        init();
    });

    init();

}

void pausewindow::init(){
    backBtn->hide();
    continueBtn->hide();
    exitBtn->hide();
    duolapause->hide();
    duolaend->hide();
    p1win->hide();
    p2win->hide();

}

void pausewindow::winmode1(){
    p1win->show();
    backBtn->move(747,620);
    backBtn->sety(620);
    exitBtn->move(745,770);
    exitBtn->sety(770);
    backBtn->show();
    exitBtn->show();
    QTimer::singleShot(500,this,[=](){
        duolaend->show();
    });
}

void pausewindow::winmode2(){
    p2win->show();
    backBtn->move(747,620);
    backBtn->sety(620);
    exitBtn->move(745,770);
    exitBtn->sety(770);
    backBtn->show();
    exitBtn->show();
    QTimer::singleShot(500,this,[=](){
        duolaend->show();
    });
}

void pausewindow::pausemode(){
    backBtn->move(745,450);
    backBtn->sety(450);
    continueBtn->move(745,250);
    continueBtn->sety(250);
    exitBtn->move(745,650);
    exitBtn->sety(650);
    backBtn->show();
    continueBtn->show();
    exitBtn->show();
    QTimer::singleShot(500,this,[=](){
        duolapause->show();
    });
}
