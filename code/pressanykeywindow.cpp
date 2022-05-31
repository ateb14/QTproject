#include "pressanykeywindow.h"
#include <QPainter>

pressanykeywindow::pressanykeywindow(QWidget *parent) : QWidget(parent)
{

}

void pressanykeywindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load("://art/pressanykey.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void pressanykeywindow::keyPressEvent(QKeyEvent *event){
    emit isclosed();
}
