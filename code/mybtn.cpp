#include "mybtn.h"
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QSound>
#include <QTimer>

//myBtn::myBtn(QWidget *parent) : QPushButton(parent)
//{

//}
int posx;
int posy;
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

void myBtn::press(){
    presssound->play();
    posx=x();
    posy=y();
    QPropertyAnimation *ani = new QPropertyAnimation(this,"geometry");
    ani->setDuration(200);
    ani->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    ani->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();

}

void myBtn::release(){
    releasesound->play();
    QPropertyAnimation *ani = new QPropertyAnimation(this,"geometry");
    ani->setDuration(200);
    ani->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    ani->setEndValue(QRect(posx,posy,this->width(),this->height()));
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



