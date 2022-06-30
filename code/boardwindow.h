#ifndef BOARDWINDOW_H
#define BOARDWINDOW_H

#include <QWidget>
#include "config.h"
#include <QPropertyAnimation>

class boardWindow : public QWidget
{
    Q_OBJECT
public:
    explicit boardWindow(QWidget *parent = 0);
    ~boardWindow();
    int score1,score2;//大分
    int soccer1,soccer2;//小分
    double health1,health2;
    double power1,power2;
    int buff1[4],buff2[4];//记录某个buff的显示位置，-1为不显示
    bool buffloc1[3],buffloc2[3];//记录某个位置有没有显示buff
    QPropertyAnimation *anihealth1;
    QPropertyAnimation *anihealth2;
    QPropertyAnimation *anipower1;
    QPropertyAnimation *anipower2;
    void init();//初始化大比分

signals:

public slots:
    void refresh(PlayerType p1,PlayerType p2);
    void addscore(int winner);
    void addsoccer(int winner);
    void changehealth1(double rate);
    void changepower1(double rate);
    void changehealth2(double rate);
    void changepower2(double rate);
    void addbuff1(int num);
    void removebuff1(int num);
    void addbuff2(int num);
    void removebuff2(int num);

};

#endif // BOARDWINDOW_H
