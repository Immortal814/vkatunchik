#include "mainwindow.hpp"
#include <QApplication>
#include <QDebug>
int main( int argc, char *argv[] ) {
    qDebug() << "PRODUCER";
    QApplication a( argc, argv );
    MainWindow w;
    //w.show();
    return a.exec();
}
