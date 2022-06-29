#ifndef CINEMAWINDOW_H
#define CINEMAWINDOW_H

#include <QWidget>

class cinemaWindow : public QWidget
{
    Q_OBJECT
public:
    explicit cinemaWindow(QWidget *parent = 0);
    void init();
    void movein();
    void moveout();

signals:
    void startreview(QString cinemafilepath);
    void backtomain();
public slots:
};

#endif // CINEMAWINDOW_H
