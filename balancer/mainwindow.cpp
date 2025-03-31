#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent ): QMainWindow( parent ), ui( new Ui::MainWindow ) {

	ui->setupUi( this );
	producer = new producer_cl;
}

MainWindow::~MainWindow() {
    delete producer;
    delete ui;
}
