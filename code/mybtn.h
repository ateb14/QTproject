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
    void press();
    void release();
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
signals:
    void btnClicked();
public slots:
};

#endif // MYBTN_H
