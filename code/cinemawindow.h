#ifndef CINEMAWINDOW_H
#define CINEMAWINDOW_H

#include <QWidget>
#include <QPropertyAnimation>

class cinemaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit cinemaWindow(QWidget *parent = 0);
    ~cinemaWindow();
    void init();
    void movein();
    void moveout();
    QPropertyAnimation *aniback;
    QPropertyAnimation *anicinema;
    QPropertyAnimation *aniname[6];
    QPropertyAnimation *aniplay[6];

signals:
    void startreview(QString cinemafilepath);
    void backtomain();
public slots:
};

#endif // CINEMAWINDOW_H
