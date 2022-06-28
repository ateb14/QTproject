#include "newgamesetting.h"
#include <QPainter>
#include "mybtn.h"
#include "mylabel.h"
#include <QTimer>
#include <QPropertyAnimation>

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

    setting->move(615,60);

    love1->move(650,620);
    love1->sety(620);
    santa1->move(800,620);
    santa1->sety(620);
    angry1->move(950,620);
    angry1->sety(620);
    guoshen1->move(1100,620);
    guoshen1->sety(620);

    love2->move(650,780);
    love2->sety(780);
    santa2->move(800,780);
    santa2->sety(780);
    angry2->move(950,780);
    angry2->sety(780);
    guoshen2->move(1100,780);
    guoshen2->sety(780);

    start->move(1030,900);
    start->sety(900);
    back->move(720,900);
    back->sety(900);

    format->move(850,215);
    format->sety(215);
    speed->move(890,327);
    speed->sety(327);
    enemy->move(922,433);
    enemy->sety(433);

    player1->move(820,534);
    player2->move(820,704);

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

}

void newGameSetting::movein(){

    choosecharacter->changeImg(":/art/choosecharacter.png");

}


void newGameSetting::moveout(){

}

