#include "consumer.hpp"

consumer::consumer( QObject* parent ) : QObject{ parent } {

	udp_socket.bind( QHostAddress::LocalHost, constant::port_operator_consumer );

	data_struct.command = REMOVE;

	connect( &udp_socket, &QUdpSocket::readyRead, this, &consumer::slot_from_operator );
}

// Отправка данных оператору
void consumer::set_consum_que( QPair<quint8, quint32> p_cl ) {

	QByteArray data;
	QDataStream stream( &data, QIODevice::WriteOnly );

	//QPair<quint8, quint32> test = { 0x03, 0x1234 };

	stream << p_cl.first << p_cl.second;

	udp_write.writeDatagram( data, QHostAddress::LocalHost, constant::port_consumer_operator );
}
// Обрабатываем данные от оператора
void consumer::slot_from_operator() {

	QByteArray data;

	// Читаем данные от оператора
	if ( udp_socket.hasPendingDatagrams() ) {

		data.resize( udp_socket.pendingDatagramSize() );
		udp_socket.readDatagram( data.data(), data.size() );

		// Добавляем команду на удаление и отправляем на табло
		// Если что, попробовать убрать нижнее из if
		std::memcpy( &data_struct, data.data(), sizeof( command_s ) );
		if ( data_struct.command == C_REQUEST ) {

			emit sig_get_client( data_struct.kassa );

		} else if ( data_struct.command == REMOVE ) {

			udp_write.writeDatagram( data, QHostAddress::LocalHost, constant::port_balans_to_board );
			// Вызываем сигнал для удаление из общей очереди.
			emit sig_erase_client( data_struct.kassa, data_struct.numer_que );
		}
		//data.push_front( REMOVE );
		//std::memcpy( &data_struct, data.data(), sizeof( command_s ) );
	} else
		qDebug() << "ERROR CONSUM UDP " << __FILE__ << " " << __LINE__;
}

consumer::~consumer() {}
