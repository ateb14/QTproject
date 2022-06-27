#include "mybtn.h"
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QSound>
#include <QTimer>

//myBtn::myBtn(QWidget *parent) : QPushButton(parent)
//{

//}
QSound *presssound=new  QSound(":/music/mousepress.wav");
QSound *releasesound=new  QSound(":/music/mouserelease.wav");
//音效来自网络

myBtn::myBtn(QString Img,QWidget *parent){
    ImgPath=Img;
    QPixmap pix;
    pix.load(ImgPath);
    setFixedSize(pix.size());
    setStyleSheet("QPushButton{border:0px;}");
    setIcon(pix);
    setIconSize(pix.size());
    setParent(parent);
    connect(this,&myBtn::clicked,[=](){
        QTimer::singleShot(100,this,[=](){
            emit btnClicked();
        });
    });
}

void myBtn::sety(int yy){
    posy=yy;
    posy_dy=yy+10;
}

void myBtn::changeImg(QString Img){
    ImgPath=Img;
    QPixmap pix;
    pix.load(ImgPath);
    setStyleSheet("QPushButton{border:0px;}");
    setIcon(pix);
    setIconSize(pix.size());
}

void myBtn::press(){
    presssound->play();
    QPropertyAnimation *ani = new QPropertyAnimation(this,"geometry");
    ani->setDuration(100);
    ani->setStartValue(QRect(this->x(),posy,this->width(),this->height()));
    ani->setEndValue(QRect(this->x(), posy_dy,this->width(),this->height()));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();

}

void myBtn::release(){
    releasesound->play();
    QPropertyAnimation *ani = new QPropertyAnimation(this,"geometry");
    ani->setDuration(100);
    ani->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    ani->setEndValue(QRect(this->x(),posy,this->width(),this->height()));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    QTimer::singleShot(100,this,[=](){
        ani->start();
    });


}

//点击事件
void myBtn::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
       press();
    }
    return QPushButton::mousePressEvent(ev);

}

//释放事件
void myBtn::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
       release();

    }

    return QPushButton::mouseReleaseEvent(ev);
}



