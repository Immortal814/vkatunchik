#include "socket_class.hpp"

socket_class::socket_class( QObject *parent )
    : QObject{ parent } {

	_udp_socket.bind( QHostAddress::LocalHost, constant::port_balans_to_board );
	connect( &_udp_socket, &QUdpSocket::readyRead, this, &socket_class::slot_data_received );
}

void socket_class::slot_data_received() {

	QByteArray data;
	//QHostAddress sender;
	//quint16 send_port;
	qDebug() << "HERE";

	while ( _udp_socket.hasPendingDatagrams() ) {

		data.resize( _udp_socket.pendingDatagramSize() );

		qDebug() << "SIZE DATA: " << data.size();

		_udp_socket.readDatagram( data.data(), data.size() );

		std::memcpy( &data_struct, data.data(), sizeof( command_s ) );

		if ( data_struct.command == ADD ) {

			// qDebug() << "ADD/n/n"; //qDebug() << "KASSA: " << static_cast<int>( data[ 1 ] );
			// qDebug() << "KASSA: " << data.toHex( ' ' );
			// qDebug() << "NUM: " << ( int )data[ 1 ];
			qDebug() << "KASSA: " << data_struct.kassa;
			qDebug() << "NUM: " << data_struct.numer_que;
			emit sig_received_command( &data_struct );

		} else if ( data_struct.command == REMOVE ) {

			qDebug() << "REMOVE!!!";
			emit sig_received_command( &data_struct );
		}
	} // while
}
