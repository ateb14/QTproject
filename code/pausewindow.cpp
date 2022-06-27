#include "pausewindow.h"
#include <QPainter>
#include "mybtn.h"
#include<QTimer>

myBtn *backBtn=NULL;
myBtn *continueBtn = NULL;
myBtn *exitBtn=NULL;


pausewindow::pausewindow(QWidget *parent) : QWidget(parent)
{
    backBtn=new myBtn(":/art/back.png",this);
    continueBtn=new myBtn(":/art/continue.png",this);
    exitBtn= new myBtn(":/art/exit.png",this);
    backBtn->move(645-backBtn->width()/2,250);
    backBtn->sety(250);
    continueBtn->move(645-continueBtn->width()/2,450);
    continueBtn->sety(450);
    exitBtn->move(645-exitBtn->width()/2,650);
    exitBtn->sety(650);

    connect(continueBtn,&myBtn::btnClicked,[=](){
        emit gamecontinue();
    });

    connect(exitBtn,&myBtn::btnClicked,[=](){
        emit close();
    });

    connect(backBtn,&myBtn::btnClicked,[=](){
        emit back();
    });

}

void pausewindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load("://art/test.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
