#include "mainwindow.hpp"
#include "ui_mainwindow.h"

const static quint8 MAX_ROW = 10;

MainWindow::MainWindow( QWidget *parent ) : QMainWindow( parent ), ui( new Ui::MainWindow ) {

	ui->setupUi( this );
	cl_socket = new socket_class;
	// Установка кол-ва столбцов и строк
	ui->tableW->setRowCount( 10 );
	ui->tableW->setColumnCount( 2 );
	// Названия столбцов
	QStringList head_name{ "Клиент", "Окно" };
	ui->tableW->setHorizontalHeaderLabels( head_name );
	// Растягивание столбцов 50\50
	ui->tableW->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
	// Убираем номирацию строк
	ui->tableW->verticalHeader()->setVisible( false );

	// Создать все айтемы в конструкторе 10 штук
	// Очищаешь, берешь 0 строку\0 клиент. Просто удаляю, а потом заново записиваю

	// Создаем все айтемы
	for ( int i = 0; i < ui->tableW->rowCount(); i++ ) {
		for ( int k = 0; k < ui->tableW->columnCount(); k++ ) {

			qDebug() << "I: " << i << " K: " << k;
			//ui->tableW->setItem( i, k, new QTableWidgetItem( QString::number( i ) ) );
			ui->tableW->setItem( i, k, new QTableWidgetItem() );
			ui->tableW->item( i, k )->setTextAlignment(( Qt::AlignCenter ));
		}
	}
	ui->tableW->item( 0, 1 )->setText( "12345" );

	//ui->tableW->setItem( 0, 0, new QTableWidgetItem( "Окно" ) );
	//ui->tableW->item( 0, 0 )->setTextAlignment(( Qt::AlignCenter ));

	//ui->tableW->item( 0, 0 )->setTextAlignment( Qt::AlignVCenter );
	// Убрать все границы
	//ui->tableW->setShowGrid( false );
	//ui->tableW->setStyleSheet( "QTableWidget::item { border-left: 1px solid white; border-right: 1px solid white; }" );

	connect( cl_socket, &socket_class::sig_received_command, this, &MainWindow::slot_set_table );
}

void MainWindow::set_table_info() {

	quint8 row = 0;
	// Заполняем таблицу до 10 элементов
	for ( auto it = _client_list.begin(); it != _client_list.end() && row < MAX_ROW; it++, row++ ) {

		ui->tableW->item( row, 0 )->setText( QString::number( it.key() ) );
		ui->tableW->item( row, 1 )->setText( QString::number( it.value() ) );
	}

	// Если элементов Мапы меньше 10, заполняем остальное пробелами.
	for ( ; row < MAX_ROW; row++ ) {

		ui->tableW->item( row, 0 )->setText( " " );
		ui->tableW->item( row, 1 )->setText( " " );
	}
}

void MainWindow::slot_set_table( const command_s* data ) {

	if ( data->command == ADD ) {

		_client_list.insert( data->numer_que, data->kassa );
		set_table_info();

	} else if ( data->command == REMOVE ) {

		_client_list.remove( data->numer_que );
		set_table_info();
	}

	qDebug() << "DONE! Slot MainWindow  " << __FILE__ << " " << __LINE__;
}

MainWindow::~MainWindow() {

	delete cl_socket;
	delete ui;
}
