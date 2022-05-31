#include "newgamesetting.h"
#include <QPainter>
#include "mybtn.h"
#include <QTimer>

myBtn *start=NULL;

newGameSetting::newGameSetting(QWidget *parent) : QWidget(parent)
{
    start=new myBtn("://art/startgame.png",this);
    start->move((1290-100)/2,800);

    connect(start,&myBtn::btnClicked,[=](){
             emit startgame();
    });
}

void newGameSetting::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/art/welcome.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
