#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>

class myWindow : public QWidget
{
    Q_OBJECT
public:
    explicit myWindow(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:

public slots:
};

#endif // MYWINDOW_H
