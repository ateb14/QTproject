#include "cinemawindow.h"
#include "mybtn.h"
#include "mylabel.h"
#include <QTimer>
#include <QPropertyAnimation>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFont>
#include <QPalette>

myLabel *cinemabg;
myLabel *filename[6];
myLabel *choosevideo;
myLabel *novideo;
myLabel *cinema;
myBtn *cinemaback;
myBtn *choosebtn[6];



cinemaWindow::cinemaWindow(QWidget *parent) : QWidget(parent)
{

    cinemabg=new myLabel(":/art/dark.png",this);
    cinemabg->move(0,0);
    choosevideo=new myLabel(":/art/choosevideo.png",this);
    choosevideo->move(100,250);
    novideo=new myLabel(":/art/novideo.png",this);
    novideo->move(100,250);
    cinema=new myLabel(":/art/cinema.png",this);
    cinema->move(1290,95);

    cinemaback=new myBtn(":/art/fanhui.png",this);
    cinemaback->move(950,1000);
    cinemaback->sety(900);

    QFont font;
    font.setPointSize(18);
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::white);

    for(int i=0;i<6;++i){
        filename[i]=new myLabel(this);
        filename[i]->setText("yy-MM-dd_hh-mm-ss");
        filename[i]->setFont(font);
        filename[i]->setPalette(palette);
        filename[i]->move(1290,210+i*105);
        choosebtn[i]=new myBtn(":/art/play.png",this);
        choosebtn[i]->move(1490,250+i*105);
        choosebtn[i]->sety(250+i*105);
        connect(choosebtn[i],&myBtn::btnClicked,[=](){
            emit startreview(filename[i]->text());
             moveout();
            //qDebug()<<filename[i]->text();
        });
        filename[i]->hide();
        choosebtn[i]->hide();

    }

    connect(cinemaback,&myBtn::btnClicked,[=](){
            emit backtomain();
             moveout();
    });



}

void cinemaWindow::init(){

    choosevideo->hide();
    novideo->hide();
    for(int i=0;i<6;++i){

        filename[i]->hide();
        choosebtn[i]->hide();
    }
    //"C:\Users\11438\Desktop\TEST"
    QString dirTemp = "C:/Users/11438/Desktop/TEST";
    QDir dirt(dirTemp);

    QStringList filterst;
    filterst << QString("*.dat") << QString("*.DAT");
    QFileInfoList file_list = dirt.entryInfoList(filterst, QDir::Files | QDir::NoSymLinks);

    if (file_list.size()>0)
    {
        choosevideo->show();
        for (int i = 0; i < file_list.size();++i)
        {
            filename[i]->setText(file_list[i].baseName());
            filename[i]->show();
            choosebtn[i]->show();
        }
    }
    else{
        novideo->show();
    }


}

void cinemaWindow::movein(){
    QPropertyAnimation *aniback = new QPropertyAnimation(cinemaback,"geometry");
    aniback->setDuration(100);
    aniback->setStartValue(QRect(950,1000,cinemaback->width(),cinemaback->height()));
    aniback->setEndValue(QRect(950,900,cinemaback->width(),cinemaback->height()));

    QPropertyAnimation *anicinema = new QPropertyAnimation(cinema,"geometry");
    anicinema->setDuration(100);
    anicinema->setStartValue(QRect(1290,95,cinema->width(),cinema->height()));
    anicinema->setEndValue(QRect(880,95,cinema->width(),cinema->height()));

    QPropertyAnimation *aniname[6];
    for(int i=0;i<6;++i){
        aniname[i] = new QPropertyAnimation(filename[i],"geometry");
        aniname[i]->setDuration(100);
        aniname[i]->setStartValue(QRect(1290,210+i*105,filename[i]->width(),filename[i]->height()));
        aniname[i]->setEndValue(QRect(785,210+i*105,filename[i]->width(),filename[i]->height()));
    }
    QPropertyAnimation *aniplay[6];
    for(int i=0;i<6;++i){
        aniplay[i] = new QPropertyAnimation(choosebtn[i],"geometry");
        aniplay[i]->setDuration(100);
        aniplay[i]->setStartValue(QRect(1490,250+i*105,choosebtn[i]->width(),choosebtn[i]->height()));
        aniplay[i]->setEndValue(QRect(1060,250+i*105,choosebtn[i]->width(),choosebtn[i]->height()));
    }

    aniback->start();
    anicinema->start();
    for(int i=0;i<6;++i){
        aniname[i]->start();
        aniplay[i]->start();
    }
}

void cinemaWindow::moveout(){
    cinema->move(1290,95);
    cinemaback->move(950,1000);
    for(int i=0;i<6;++i){
        filename[i]->move(1290,210+i*105);
        choosebtn[i]->move(1490,250+i*105);
    }
}
