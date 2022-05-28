#include <QApplication>
#include "mywindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    myWindow allWindow;

    allWindow.show();

    return a.exec();
}
