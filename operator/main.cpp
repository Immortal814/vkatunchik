#include "mainwindow.hpp"

#include <QApplication>

int main( int argc, char* argv[] ) {

	qDebug() << "OPERATOR";
	QApplication a( argc, argv );
	MainWindow w;
	w.show();
	return a.exec();
}
