#include "boardwindow.h"
#include "mylabel.h"
#include <QPropertyAnimation>

myLabel *boardbg;
myLabel *player1name;
myLabel *player2name;
myLabel *player1bigscore;
myLabel *player2bigscore;
myLabel *player1soccer[3];
myLabel *player2soccer[3];
myLabel *player1pic;
myLabel *player2pic;
myLabel *player1health;
myLabel *player1power;
myLabel *player2health;
myLabel *player2power;
myLabel *player1buff[3];
myLabel *player2buff[3];
QPropertyAnimation *anihealth1;
QPropertyAnimation *anihealth2;
QPropertyAnimation *anipower1;
QPropertyAnimation *anipower2;
QString scorepic[6]={":/art/zero.png",":/art/one.png",":/art/two.png",":/art/three.png",":/art/four.png",":/art/five.png"};
QString buffpic[4]={":/art/speedsmall.png",":/art/freezesmall.png",":/art/magnetsmall.png",":/art/ragesmall.png"};



boardWindow::boardWindow(QWidget *parent) : QWidget(parent)
{
    boardbg=new myLabel(":/art/boardwindow.png",this);
    boardbg->move(0,0);

    player1name=new myLabel(":/art/playerlove.png",this);
    player1name->move(437,5);

    player1bigscore=new myLabel(":/art/zero.png",this);
    player1bigscore->move(420,15);

    player2name=new myLabel(":/art/playerlove.png",this);
    player2name->move(648,5);

    player2bigscore=new myLabel(":/art/zero.png",this);
    player2bigscore->move(625,15);

    player1soccer[0]=new myLabel(":/art/soccerfalse.png",this);
    player1soccer[0]->move(37,100);

    player1soccer[1]=new myLabel(":/art/soccerfalse.png",this);
    player1soccer[1]->move(83,100);

    player1soccer[2]=new myLabel(":/art/soccerfalse.png",this);
    player1soccer[2]->move(130,100);

    player2soccer[0]=new myLabel(":/art/soccerfalse.png",this);
    player2soccer[0]->move(1218,100);

    player2soccer[1]=new myLabel(":/art/soccerfalse.png",this);
    player2soccer[1]->move(1172,100);

    player2soccer[2]=new myLabel(":/art/soccerfalse.png",this);
    player2soccer[2]->move(1125,100);

    player1pic=new myLabel(":/art/love.png",this);
    player1pic->move(65,17);

    player2pic=new myLabel(":/art/love.png",this);
    player2pic->move(1153,17);


    player1health=new myLabel(":/art/health.png",this);
    player1health->move(203,68);

    player1power=new myLabel(":/art/power.png",this);
    player1power->move(202,150);

    player2health=new myLabel(":/art/health.png",this);
    player2health->move(850,69);

    player2power=new myLabel(":/art/power.png",this);
    player2power->move(849,151);

    player1buff[0]=new myLabel(":/art/speedsmall.png",this);
    player1buff[0]->move(39,146);

    player1buff[1]=new myLabel(":/art/freezesmall.png",this);
    player1buff[1]->move(85,146);

    player1buff[2]=new myLabel(":/art/magnetsmall.png",this);
    player1buff[2]->move(131,146);

    player2buff[0]=new myLabel(":/art/ragesmall.png",this);
    player2buff[0]->move(1220,147);

    player2buff[1]=new myLabel(":/art/magnetsmall.png",this);
    player2buff[1]->move(1173,147);

    player2buff[2]=new myLabel(":/art/speedsmall.png",this);
    player2buff[2]->move(1126,147);

    anihealth1 = new QPropertyAnimation(player1health,"geometry");
    anihealth2 = new QPropertyAnimation(player2health,"geometry");
    anipower1 = new QPropertyAnimation(player1power,"geometry");
    anipower2 = new QPropertyAnimation(player2power,"geometry");
    anihealth1->setDuration(100);
    anihealth2->setDuration(100);
    anipower1->setDuration(100);
    anipower2->setDuration(100);


}

void boardWindow::init(){
    score1=0;score2=0;
    player1bigscore->changeImg(":/art/zero.png");
    player2bigscore->changeImg(":/art/zero.png");
    health1=1;health2=1;
    power1=0;power2=0;


    anihealth1->setDuration(10);
    anihealth2->setDuration(10);
    anipower1->setDuration(10);
    anipower2->setDuration(10);

    anihealth1->setStartValue(QRect(203,68,player1health->width(),player1health->height()));
    anihealth1->setEndValue(QRect(203,68,int(237*health1),player1health->height()));
    anihealth1->start();


    anihealth2->setStartValue(QRect(player2health->x(),69,player2health->width(),player2health->height()));
    anihealth2->setEndValue(QRect(850+237-int(237*health2),69,int(237*health2),player2health->height()));
    anihealth2->start();


    anipower1->setStartValue(QRect(202,150,player1power->width(),player1power->height()));
    anipower1->setEndValue(QRect(202,150,int(237*power1),player1power->height()));
    anipower1->start();


    anipower2->setStartValue(QRect(player2power->x(),151,player2power->width(),player2power->height()));
    anipower2->setEndValue(QRect(849+237-int(237*power2),151,int(237*power2),player2power->height()));
    anipower2->start();

    anihealth1->setDuration(100);
    anihealth2->setDuration(100);
    anipower1->setDuration(100);
    anipower2->setDuration(100);

}

void boardWindow::refresh(PlayerType p1,PlayerType p2){
    switch(p1){
    case 0:
        player1name->changeImg(":/art/playerlove.png");
        player1pic->changeImg(":/art/love.png");
        break;
    case 1:
        player1name->changeImg(":/art/playersanta.png");
        player1pic->changeImg(":/art/santa.png");
        break;
    case 2:
        player1name->changeImg(":/art/playerguoshen.png");
        player1pic->changeImg(":/art/gls.png");
        break;
    case 3:
        player1name->changeImg(":/art/playerangry.png");
        player1pic->changeImg(":/art/angry.png");
        break;
    }
    switch(p2){
    case 0:
        player2name->changeImg(":/art/playerlove.png");
        player2pic->changeImg(":/art/love.png");
        break;
    case 1:
        player2name->changeImg(":/art/playersanta.png");
        player2pic->changeImg(":/art/santa.png");
        break;
    case 2:
        player2name->changeImg(":/art/playerguoshen.png");
        player2pic->changeImg(":/art/gls.png");
        break;
    case 3:
        player2name->changeImg(":/art/playerangry.png");
        player2pic->changeImg(":/art/angry.png");
        break;
    }
    soccer1=-1;soccer2=-1;
    for(int i=0;i<3;++i){
        player1soccer[i]->changeImg(":/art/soccerfalse.png");
        player2soccer[i]->changeImg(":/art/soccerfalse.png");
        player1buff[i]->hide();
        player2buff[i]->hide();
    }
    health1=1;health2=1;
    power1=0;power2=0;


    anihealth1->setStartValue(QRect(203,68,player1health->width(),player1health->height()));
    anihealth1->setEndValue(QRect(203,68,int(237*health1),player1health->height()));
    anihealth1->start();


    anihealth2->setStartValue(QRect(player2health->x(),69,player2health->width(),player2health->height()));
    anihealth2->setEndValue(QRect(850+237-int(237*health2),69,int(237*health2),player2health->height()));
    anihealth2->start();


    anipower1->setStartValue(QRect(202,150,player1power->width(),player1power->height()));
    anipower1->setEndValue(QRect(202,150,int(237*power1),player1power->height()));
    anipower1->start();


    anipower2->setStartValue(QRect(player2power->x(),151,player2power->width(),player2power->height()));
    anipower2->setEndValue(QRect(849+237-int(237*power2),151,int(237*power2),player2power->height()));
    anipower2->start();


    for(int i=0;i<4;++i) {
        buff1[i]=-1;
        buff2[i]=-1;
    }
    for(int i=0;i<3;++i){
        buffloc1[i]=0;
        buffloc2[i]=0;
    }

}

void boardWindow::addscore(int winner){
    if(winner==1){
        score1++;
        player1bigscore->changeImg(scorepic[score1]);
    }
    else{
        score2++;
        player2bigscore->changeImg(scorepic[score2]);
    }
}

void boardWindow::addsoccer(int winner){
    if(winner==1){
        soccer1++;
        player1soccer[soccer1]->changeImg(":/art/soccertrue.png");
    }
    else{
        soccer2++;
        player2soccer[soccer2]->changeImg(":/art/soccertrue.png");
    }
}

void boardWindow::changehealth1(double rate){
    health1=rate;
    anihealth1->setStartValue(QRect(203,68,player1health->width(),player1health->height()));
    anihealth1->setEndValue(QRect(203,68,int(237*health1),player1health->height()));
    anihealth1->start();
}

void boardWindow::changepower1(double rate){
    power1=rate;
    anipower1->setStartValue(QRect(202,150,player1power->width(),player1power->height()));
    anipower1->setEndValue(QRect(202,150,int(237*power1),player1power->height()));
    anipower1->start();
}

void boardWindow::changehealth2(double rate){
    health2=rate;
    anihealth2->setStartValue(QRect(player2health->x(),69,player2health->width(),player2health->height()));
    anihealth2->setEndValue(QRect(850+237-int(237*health2),69,int(237*health2),player2health->height()));
    anihealth2->start();
}

void boardWindow::changepower2(double rate){
    power2=rate;
    anipower2->setStartValue(QRect(player2power->x(),151,player2power->width(),player2power->height()));
    anipower2->setEndValue(QRect(849+237-int(237*power2),151,int(237*power2),player2power->height()));
    anipower2->start();
}

void boardWindow::addbuff1(int num){
    if(buff1[num]==-1){
        for(int i=0;i<3;++i){
            if(!buffloc1[i]){
                buffloc1[i]=1;
                buff1[num]=i;
                player1buff[i]->changeImg(buffpic[num]);
                player1buff[i]->show();
                break;
            }
        }
    }
}

void boardWindow::removebuff1(int num){
    if(buff1[num]>=0){
        player1buff[buff1[num]]->hide();
        buffloc1[buff1[num]]=0;
        buff1[num]=-1;
    }
}

void boardWindow::addbuff2(int num){
    if(buff2[num]==-1){
        for(int i=0;i<3;++i){
            if(!buffloc2[i]){
                buffloc2[i]=1;
                buff2[num]=i;
                player2buff[i]->changeImg(buffpic[num]);
                player2buff[i]->show();
                break;
            }
        }
    }
}

void boardWindow::removebuff2(int num){
    if(buff2[num]>=0){
        player2buff[buff2[num]]->hide();
        buffloc2[buff2[num]]=0;
        buff2[num]=-1;
    }
}

