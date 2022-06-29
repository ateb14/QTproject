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
    cinema->move(880,95);

    cinemaback=new myBtn(":/art/fanhui.png",this);
    cinemaback->move(950,900);
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
        filename[i]->move(785,210+i*105);
        choosebtn[i]=new myBtn(":/art/play.png",this);
        choosebtn[i]->move(1060,250+i*105);
        choosebtn[i]->sety(250+i*105);
        connect(choosebtn[i],&myBtn::btnClicked,[=](){
            emit startreview(filename[i]->text());
            //qDebug()<<filename[i]->text();
        });
        filename[i]->hide();
        choosebtn[i]->hide();

    }

    connect(cinemaback,&myBtn::btnClicked,[=](){
            emit backtomain();
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
