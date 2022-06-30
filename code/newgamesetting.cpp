#include "newgamesetting.h"
#include <QPainter>
#include "mybtn.h"
#include "mylabel.h"
#include <QTimer>


myLabel *bgr;
myBtn *start;
myBtn *back;
myLabel *setting;
myLabel *choosecharacter;
myBtn *format;
myBtn *speed;
myBtn *enemy;

myLabel *player1;
myLabel *player2;

myBtn *love1;
myBtn *santa1;
myBtn *angry1;
myBtn *guoshen1;
myBtn *love2;
myBtn *santa2;
myBtn *angry2;
myBtn *guoshen2;


newGameSetting::newGameSetting(QWidget *parent) : QWidget(parent)
{
    bgr=new myLabel(":/art/dark.png",this);
    bgr->move(0,0);
    setting=new myLabel(":/art/newgamesetting.png",this);
    start=new myBtn(":/art/jixu.png",this);
    back=new myBtn(":/art/fanhui.png",this);
    love1=new myBtn("://art/love.png",this);
    santa1=new myBtn(":/art/santa.png",this);
    angry1=new myBtn(":/art/angry.png",this);
    guoshen1=new myBtn(":/art/gls.png",this);
    love2=new myBtn("://art/love.png",this);
    santa2=new myBtn(":/art/santa.png",this);
    angry2=new myBtn(":/art/angry.png",this);
    guoshen2=new myBtn(":/art/gls.png",this);
    choosecharacter=new myLabel(":/art/choosecharacter.png",this);


    format=new myBtn("://art/32.png",this);
    gameFormat=TWO_THREE;

    speed=new myBtn(":/art/middle.png",this);
    playerSpeed=MIDDLE;

    enemy=new myBtn(":/art/no.png",this);
    enemyMode=false;

    player1=new myLabel(":/art/lovename.png",this);
    player1Type=LOVEMAN;

    player2=new myLabel(":/art/lovename.png",this);
    player2Type=LOVEMAN;


    choosecharacter->move(100,250);

    setting->move(1290,60);

        love1->move(1290,620);
        love1->sety(620);
        santa1->move(1290,620);
        santa1->sety(620);
        angry1->move(1290,620);
        angry1->sety(620);
        guoshen1->move(1290,620);
        guoshen1->sety(620);

        love2->move(1290,780);
        love2->sety(780);
        santa2->move(1290,780);
        santa2->sety(780);
        angry2->move(1290,780);
        angry2->sety(780);
        guoshen2->move(1290,780);
        guoshen2->sety(780);

        start->move(1030,1001);
        start->sety(900);
        back->move(720,1001);
        back->sety(900);

        format->move(1290,215);
        format->sety(215);
        speed->move(1290,327);
        speed->sety(327);
        enemy->move(1290,433);
        enemy->sety(433);

        player1->move(1290,534);
        player2->move(1290,704);

//恶心的connect开始啦
    connect(start,&myBtn::btnClicked,[=](){
            moveout();
            emit startgame();
    });

    connect(back,&myBtn::btnClicked,[=](){
            moveout();
            emit backtomain();
    });

    connect(format,&myBtn::btnClicked,[=](){
            switch(gameFormat){
               case TWO_THREE :
                format->changeImg(":/art/53.png");
                gameFormat=THREE_FIVE;
                break;
            case THREE_FIVE :
             format->changeImg(":/art/32.png");
             gameFormat=TWO_THREE;
             break;
            }
    });

    connect(speed,&myBtn::btnClicked,[=](){
            switch(playerSpeed){
               case LOW :
                speed->changeImg(":/art/middle.png");
                playerSpeed=MIDDLE;
                break;
            case MIDDLE :
             speed->changeImg(":/art/fast.png");
             playerSpeed=HIGH;
             break;
            case HIGH :
             speed->changeImg(":/art/slow.png");
             playerSpeed=LOW;
             break;
            }
    });

    connect(enemy,&myBtn::btnClicked,[=](){
            switch(enemyMode){
               case 1 :
                enemy->changeImg(":/art/no.png");
                enemyMode=false;
                break;
            case 0 :
             enemy->changeImg(":/art/yes.png");
             enemyMode=true;
             break;
            }
    });


    connect(love1,&myBtn::btnClicked,[=](){
            player1->changeImg(":/art/lovename.png");
            choosecharacter->changeImg(":/art/loveintro.png");
            player1Type=LOVEMAN;
    });

    connect(santa1,&myBtn::btnClicked,[=](){
            player1->changeImg(":/art/santaname.png");
            choosecharacter->changeImg(":/art/santaintro.png");
            player1Type=SANTA;
    });

    connect(angry1,&myBtn::btnClicked,[=](){
            player1->changeImg(":/art/angryname.png");
            choosecharacter->changeImg(":/art/angryintro.png");
            player1Type=ANGRYBRO;
    });

    connect(guoshen1,&myBtn::btnClicked,[=](){
            player1->changeImg(":/art/guoshenname.png");
            choosecharacter->changeImg(":/art/guoshenintro.png");
            player1Type=GUOSHEN;
    });

    connect(love2,&myBtn::btnClicked,[=](){
            player2->changeImg(":/art/lovename.png");
            choosecharacter->changeImg(":/art/loveintro.png");
            player2Type=LOVEMAN;
    });

    connect(santa2,&myBtn::btnClicked,[=](){
            player2->changeImg(":/art/santaname.png");
            choosecharacter->changeImg(":/art/santaintro.png");
            player2Type=SANTA;
    });

    connect(angry2,&myBtn::btnClicked,[=](){
            player2->changeImg(":/art/angryname.png");
            choosecharacter->changeImg(":/art/angryintro.png");
            player2Type=ANGRYBRO;
    });

    connect(guoshen2,&myBtn::btnClicked,[=](){
            player2->changeImg(":/art/guoshenname.png");
            choosecharacter->changeImg(":/art/guoshenintro.png");
            player2Type=GUOSHEN;
    });


    //设置动画
    ani1 = new QPropertyAnimation(setting,"geometry");
    ani1->setDuration(100);
    ani1->setStartValue(QRect(1290,60,setting->width(),setting->height()));
    ani1->setEndValue(QRect(615,60,setting->width(),setting->height()));

    ani2 = new QPropertyAnimation(love1,"geometry");
    ani2->setDuration(100);
    ani2->setStartValue(QRect(1290,620,love1->width(),love1->height()));
    ani2->setEndValue(QRect(650,620,love1->width(),love1->height()));

    ani3 = new QPropertyAnimation(santa1,"geometry");
    ani3->setDuration(100);
    ani3->setStartValue(QRect(1440,620,santa1->width(),santa1->height()));
    ani3->setEndValue(QRect(800,620,santa1->width(),santa1->height()));

    ani4 = new QPropertyAnimation(angry1,"geometry");
    ani4->setDuration(100);
    ani4->setStartValue(QRect(1590,620,santa1->width(),santa1->height()));
    ani4->setEndValue(QRect(950,620,santa1->width(),santa1->height()));

    ani5 = new QPropertyAnimation(guoshen1,"geometry");
    ani5->setDuration(100);
    ani5->setStartValue(QRect(1740,620,santa1->width(),santa1->height()));
    ani5->setEndValue(QRect(1100,620,santa1->width(),santa1->height()));
//

    ani6 = new QPropertyAnimation(love2,"geometry");
    ani6->setDuration(100);
    ani6->setStartValue(QRect(1290,780,love1->width(),love1->height()));
    ani6->setEndValue(QRect(650,780,love1->width(),love1->height()));

    ani7 = new QPropertyAnimation(santa2,"geometry");
    ani7->setDuration(100);
    ani7->setStartValue(QRect(1440,780,santa1->width(),santa1->height()));
    ani7->setEndValue(QRect(800,780,santa1->width(),santa1->height()));

    ani8 = new QPropertyAnimation(angry2,"geometry");
    ani8->setDuration(100);
    ani8->setStartValue(QRect(1590,780,santa1->width(),santa1->height()));
    ani8->setEndValue(QRect(950,780,santa1->width(),santa1->height()));

    ani9 = new QPropertyAnimation(guoshen2,"geometry");
    ani9->setDuration(100);
    ani9->setStartValue(QRect(1740,780,santa1->width(),santa1->height()));
    ani9->setEndValue(QRect(1100,780,santa1->width(),santa1->height()));

    ani10 = new QPropertyAnimation(start,"geometry");
    ani10->setDuration(100);
    ani10->setStartValue(QRect(1030,1001,start->width(),start->height()));
    ani10->setEndValue(QRect(1030,900,start->width(),start->height()));

    ani11 = new QPropertyAnimation(back,"geometry");
    ani11->setDuration(100);
    ani11->setStartValue(QRect(720,1001,back->width(),back->height()));
    ani11->setEndValue(QRect(720,900,back->width(),back->height()));

    ani12 = new QPropertyAnimation(format,"geometry");
    ani12->setDuration(100);
    ani12->setStartValue(QRect(1490,215,format->width(),format->height()));
    ani12->setEndValue(QRect(850,215,format->width(),format->height()));


    ani13 = new QPropertyAnimation(speed,"geometry");
    ani13->setDuration(100);
    ani13->setStartValue(QRect(1490,327,speed->width(),speed->height()));
    ani13->setEndValue(QRect(890,327,speed->width(),speed->height()));

    ani14 = new QPropertyAnimation(enemy,"geometry");
    ani14->setDuration(100);
    ani14->setStartValue(QRect(1490,433,enemy->width(),enemy->height()));
    ani14->setEndValue(QRect(922,433,enemy->width(),enemy->height()));

    ani15 = new QPropertyAnimation(player1,"geometry");
    ani15->setDuration(100);
    ani15->setStartValue(QRect(1490,534,player1->width(),player1->height()));
    ani15->setEndValue(QRect(820,534,player1->width(),player1->height()));


    ani16 = new QPropertyAnimation(player2,"geometry");
    ani16->setDuration(100);
    ani16->setStartValue(QRect(1490,704,player1->width(),player1->height()));
    ani16->setEndValue(QRect(820,704,player1->width(),player1->height()));

}

void newGameSetting::movein(){

    choosecharacter->changeImg(":/art/choosecharacter.png");



         ani1->start();
         ani2->start();
         ani3->start();
         ani4->start();
         ani5->start();
         ani6->start();
         ani7->start();
         ani8->start();
         ani9->start();
         ani10->start();
         ani11->start();
         ani12->start();
         ani13->start();
         ani14->start();
         ani15->start();
         ani16->start();

}


void newGameSetting::moveout(){
        setting->move(1290,60);

        love1->move(1290,620);

        santa1->move(1290,620);

        angry1->move(1290,620);

        guoshen1->move(1290,620);


        love2->move(1290,780);

        santa2->move(1290,780);

        angry2->move(1290,780);

        guoshen2->move(1290,780);


        start->move(1030,1001);

        back->move(720,1001);


        format->move(1290,215);

        speed->move(1290,327);

        enemy->move(1290,433);


        player1->move(1290,534);
        player2->move(1290,704);
}

newGameSetting::~newGameSetting(){
    delete ani1;
    delete ani2;
    delete ani3;
    delete ani4;
    delete ani5;
    delete ani6;
    delete ani7;
    delete ani8;
    delete ani9;
    delete ani10;
    delete ani11;
    delete ani12;
    delete ani13;
    delete ani14;
    delete ani15;
    delete ani16;
}
