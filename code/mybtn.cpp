#include "mybtn.h"
#include <QMouseEvent>
#include <QSound>
#include <QTimer>

//myBtn::myBtn(QWidget *parent) : QPushButton(parent)
//{

//}
QSound presssound(":/music/mousepress.wav");
QSound releasesound(":/music/mouserelease.wav");


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
    ani1 = new QPropertyAnimation(this,"geometry");
    ani2 = new QPropertyAnimation(this,"geometry");
    ani1->setDuration(100);
    ani1->setEasingCurve(QEasingCurve::OutBounce);
    ani2->setDuration(100);
    ani2->setEasingCurve(QEasingCurve::OutBounce);
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
    presssound.play();
    ani1->setStartValue(QRect(this->x(),posy,this->width(),this->height()));
    ani1->setEndValue(QRect(this->x(), posy_dy,this->width(),this->height()));    
    ani1->start();

}

void myBtn::release(){
    releasesound.play();
    ani2->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    ani2->setEndValue(QRect(this->x(),posy,this->width(),this->height()));   
    QTimer::singleShot(100,this,[=](){
        ani2->start();
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

myBtn::~myBtn(){
    if(ani1) delete ani1;
    if(ani2) delete ani2;
}

