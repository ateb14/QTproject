#ifndef PRESSANYKEYWINDOW_H
#define PRESSANYKEYWINDOW_H

#include <QWidget>

class pressanykeywindow : public QWidget
{
    Q_OBJECT
public:
    explicit pressanykeywindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
signals:

public slots:
};

#endif // PRESSANYKEYWINDOW_H
