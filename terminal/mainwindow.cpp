#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    qDebug() << "START";
    _send_cl = new send_class;
    // Property присваивает объекту определенный тип\значение. Принимает имя значения и само значение.
    ui->pb_credit->setProperty( "value", CREDIT );
    ui->pb_kassa->setProperty( "value", KASSA );
    ui->pb_payment->setProperty( "value", PAYMENT );
    ui->pb_card->setProperty( "value", CARD );

    connect( ui->pb_credit, &QPushButton::clicked, this, &MainWindow::slot_click );
    connect( ui->pb_kassa, &QPushButton::clicked, this, &MainWindow::slot_click );
    connect( ui->pb_payment, &QPushButton::clicked, this, &MainWindow::slot_click );
    connect( ui->pb_card, &QPushButton::clicked, this, &MainWindow::slot_click );

    // QWidget* ct = new QWidget( this );
    // QVBoxLayout* la = new QVBoxLayout( parent );
    // QPushButton* but = new QPushButton( "AAA", this );

    //setCentralWidget( ct );
}

void MainWindow::slot_click() {

	data_struct.kassa = sender()->property( "value" ).toInt();
	data_struct.numer_que++;
	_send_cl->send_command( &data_struct );
	// Sender возвращает указатель на объект, который вызвал слот

	//qDebug() << sig_obj->property( "value" ).toInt();
    //int aa = sig_obj->property( "value" ).toInt();

	//QObject *sig_obj = sender();
	//byte.append( static_cast<char>( sig_obj->property( "value" ).toInt() ) );
	// QByteArray byte;
	// byte.append( ++que_num );
	//byte.append( static_cast<char>( sender()->property( "value" ).toInt() ) );
	//_send_cl->send_command( byte );

	//qDebug() << "AAAAA: " << aa;
}

MainWindow::~MainWindow() {

    delete _send_cl;
    delete ui;
}
