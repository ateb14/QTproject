#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    myLabel (QString Img,QWidget *parent);
    void changeImg(QString Img);

signals:

public slots:
};

#endif // MYLABEL_H
