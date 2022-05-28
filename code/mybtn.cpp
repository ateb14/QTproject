#include "mybtn.h"
#include <QPropertyAnimation>
#include <QMouseEvent>

//myBtn::myBtn(QWidget *parent) : QPushButton(parent)
//{

//}
int posx;
int posy;

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
    posx=x();
    posy=y();
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
    ani->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    ani->setEndValue(QRect(this->x(),this->y()-10,this->width(),this->height()));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();

}

//点击事件
void myBtn::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
       zoom1();

    }
    //让父类去处理其他点击事件
    return QPushButton::mousePressEvent(ev);

}

//释放事件
void myBtn::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
       zoom2();
       move(posx,posy);
    }

    return QPushButton::mouseReleaseEvent(ev);
}



