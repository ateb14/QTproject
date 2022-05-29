#include "pausewindow.h"
#include <QPainter>
#include "mybtn.h"

myBtn *backBtn=NULL;
myBtn *continueBtn = NULL;
myBtn *exitBtn=NULL;


pausewindow::pausewindow(QWidget *parent) : QWidget(parent)
{
    backBtn=new myBtn(":/art/back.png",this);
    continueBtn=new myBtn(":/art/continue.png",this);
    exitBtn= new myBtn(":/art/exit.png",this);
    backBtn->move(645-backBtn->width()/2,100);
    continueBtn->move(645-continueBtn->width()/2,400);
    exitBtn->move(645-exitBtn->width()/2,700);

}

void pausewindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load("://art/test.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
