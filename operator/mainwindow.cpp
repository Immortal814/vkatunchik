#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget* parent ): QMainWindow( parent ), ui( new Ui::MainWindow ) {

	ui->setupUi( this );
	udp_socket.bind( QHostAddress::LocalHost, constant::port_consumer_operator );
	// Обычные кнопки
	ui->pb_card->setProperty( "value", CARD );
	ui->pb_credit->setProperty( "value", CREDIT );
	ui->pb_kassa->setProperty( "value", KASSA );
	ui->pb_payment->setProperty( "value", PAYMENT );

	connect( ui->pb_credit, &QPushButton::clicked, this, &MainWindow::slot_request_client );
	connect( ui->pb_kassa, &QPushButton::clicked, this, &MainWindow::slot_request_client );
	connect( ui->pb_payment, &QPushButton::clicked, this, &MainWindow::slot_request_client );
	connect( ui->pb_card, &QPushButton::clicked, this, &MainWindow::slot_request_client );

	vec_cl_but.push_back( ui->pb_kassa );
	vec_cl_but.push_back( ui->pb_payment );
	vec_cl_but.push_back( ui->pb_credit );
	vec_cl_but.push_back( ui->pb_card );

	// Удаление клиента
	ui->pb_free_card->setProperty( "value", CARD );
	ui->pb_free_credit->setProperty( "value", CREDIT );
	ui->pb_free_kassa->setProperty( "value", KASSA );
	ui->pb_free_payment->setProperty( "value", PAYMENT );

	vec_but.push_back( ui->pb_free_card );
	vec_but.push_back( ui->pb_free_credit );
	vec_but.push_back( ui->pb_free_kassa );
	vec_but.push_back( ui->pb_free_payment );

	connect( ui->pb_free_card, &QPushButton::clicked, this, &MainWindow::slot_remove_client );
	connect( ui->pb_free_credit, &QPushButton::clicked, this, &MainWindow::slot_remove_client );
	connect( ui->pb_free_kassa, &QPushButton::clicked, this, &MainWindow::slot_remove_client );
	connect( ui->pb_free_payment, &QPushButton::clicked, this, &MainWindow::slot_remove_client );
}

void MainWindow::slot_request_client() {

	QPushButton* button = qobject_cast<QPushButton*>( sender() );
	quint8 kassa = button->property( "value" ).toInt();
	// Выключаем кнопку, чтобы не было очереди приема
	button->setEnabled( false );

	QByteArray data;
	data.append( C_REQUEST );
	//data.append( (char)0x00 );
	data.append( kassa );
	// Отправляем запрос на клиента
	udp_send.writeDatagram( data, QHostAddress::LocalHost, constant::port_operator_consumer );

	// Ожидание запроса от списка клиентов
	connect( &udp_socket, &QUdpSocket::readyRead, this, [ = ]( void ) {
		qDebug() << "IN LAMBDA";
		b_array[ kassa ].clear();
		if ( udp_socket.hasPendingDatagrams() ) {

			QHostAddress sender;
			quint16 senderPort;

			b_array[ kassa ].resize( udp_socket.pendingDatagramSize() );
			udp_socket.readDatagram( b_array[ kassa ].data(), b_array[ kassa ].size(), &sender, &senderPort );
			// +1 для просука переменной с командой
			std::memcpy( &data_struct + 1, b_array[ kassa ].data(), sizeof( command_s ) );
			qDebug() << "DATA FROM: " << sender.toString() << " PORT " << senderPort;
		}
		// Включаем кнопку удаление клиента
		for ( auto t : std::as_const( vec_but ) ) {

			if ( kassa == t->property( "value" ).toInt() ) {

				t->setEnabled( true );
			}
		} // for
	} ); // labda
	qDebug() << "as";
}

void MainWindow::slot_remove_client() {

	QPushButton* button = qobject_cast<QPushButton*>( sender() );
	quint8 kassa = button->property( "value" ).toInt();
	button->setEnabled( false );
	all_client_map.insert( data_struct.numer_que, data_struct.kassa );

	b_array[ kassa ].push_front( REMOVE );
	udp_send.writeDatagram( b_array[ kassa ], QHostAddress::LocalHost, constant::port_operator_consumer );

	for ( auto t : std::as_const( vec_cl_but ) ) {

		if ( kassa == t->property( "value" ).toInt() ) {

			t->setEnabled( true );
		}
	}

	qDebug() << "REMOVE";
}

MainWindow::~MainWindow() {
	delete ui;
}
