#include "mylabel.h"






myLabel::myLabel (QString Img,QWidget *parent){
    QImage image(Img);
    setPixmap(QPixmap::fromImage(image));
    setGeometry(0,0,image.width(),image.height());
    setParent(parent);
}

myLabel::myLabel (QWidget *parent){
    setParent(parent);
}

void myLabel::changeImg(QString Img){
    QImage image(Img);
    setPixmap(QPixmap::fromImage(image));
}

