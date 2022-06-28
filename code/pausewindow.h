#ifndef PAUSEWINDOW_H
#define PAUSEWINDOW_H

#include <QWidget>


class pausewindow : public QWidget
{
    Q_OBJECT
public:
    explicit pausewindow(QWidget *parent = 0);

signals:
    void close();
    void gamecontinue();
    void back();
public slots:
};

#endif // PAUSEWINDOW_H
