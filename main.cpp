#include "mainwindow.h"

#include <QApplication>

#include <time.h>
#include <signal.h>
//#include <sys/wait.h>
#include <errno.h>
#include "qtpcr.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
