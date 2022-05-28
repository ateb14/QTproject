#include "mybtn.h"
#include <QPropertyAnimation>

//myBtn::myBtn(QWidget *parent) : QPushButton(parent)
//{

//}

myBtn::myBtn(QString Img,QWidget *parent){
    ImgPath=Img;
    QPixmap pix;
    pix.load(ImgPath);
    setFixedSize(pix.size());
    setStyleSheet("QPushButton{border:0px;}");
    setIcon(pix);
    setIconSize(pix.size());
    setParent(parent);
}

void myBtn::zoom1(){
    QPropertyAnimation *ani = new QPropertyAnimation(this,"geometry");
    ani->setDuration(200);
    ani->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    ani->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();
}

void myBtn::zoom2(){
    QPropertyAnimation *ani = new QPropertyAnimation(this,"geometry");
    ani->setDuration(200);
    ani->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    ani->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();
}


