#ifndef MYBTN_H
#define MYBTN_H

#include <QWidget>
#include <QPushButton>

class myBtn : public QPushButton
{
    Q_OBJECT
public:
//    explicit myBtn(QWidget *parent = 0);
    myBtn(QString Img,QWidget *parent);
    QString ImgPath;
    //特效
    void zoom1();
    void zoom2();
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
signals:

public slots:
};

#endif // MYBTN_H
