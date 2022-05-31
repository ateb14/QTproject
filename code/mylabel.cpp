#include "mylabel.h"






myLabel::myLabel (QString Img,QWidget *parent){
    QImage *image= new QImage(Img);
    setPixmap(QPixmap::fromImage(*image));
    setFixedSize(image->size());
    setParent(parent);
}
