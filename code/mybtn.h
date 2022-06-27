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
    void changeImg(QString Img);
    QString ImgPath;
    //特效
    void press();
    void release();
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void sety(int yy);
    int posy;
    int posy_dy;
signals:
    void btnClicked();
public slots:
};

#endif // MYBTN_H
