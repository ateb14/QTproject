#ifndef NEWGAMESETTING_H
#define NEWGAMESETTING_H

#include <QWidget>

class newGameSetting : public QWidget
{
    Q_OBJECT
public:
    explicit newGameSetting(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

signals:
    void startgame();
public slots:
};

#endif // NEWGAMESETTING_H
