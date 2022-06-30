#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include<QGraphicsEffect>
#include <QPropertyAnimation>

class myWindow : public QWidget
{
    Q_OBJECT
public:
    explicit myWindow(QWidget *parent = 0);
    ~myWindow();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);




signals:

public slots:
};

#endif // MYWINDOW_H
