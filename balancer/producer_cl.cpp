#include "producer_cl.hpp"

producer_cl::producer_cl( QObject *parent )
    : QObject{ parent } {

	stor_cl = new storage_class;
	_udp_socket.bind( QHostAddress::LocalHost, constant::port_term_to_que );

	connect( &_udp_socket, &QUdpSocket::readyRead, this, &producer_cl::slot_data_received );

	//ee.append( QByteArray::number( 420 ) );
	//ee.setNum( 512 );

	// QByteArray ee;
	// ee.append( ADD );
	// ee.append( 0x02 );
	// qDebug() << "IN PRODU. Array SIZE: " << ee.size();
	// qDebug() << "IN PRODU. Hex: " << ee.toHex( ' ' );
	// qDebug() << "IN PRODU. Int: " << ee.toInt();
	// _udp_to_board.writeDatagram( ee, QHostAddress::LocalHost, constant::port_balans_to_board );
}

void producer_cl::slot_data_received() {

	QByteArray data;
	// or while
	if ( _udp_socket.hasPendingDatagrams() ) {

		//QHostAddress sender;
		//quint16 send_port;
		data.resize( _udp_socket.pendingDatagramSize() );
		_udp_socket.readDatagram( data.data(), data.size() );

		// Если что, перенести вне блока
		qDebug() << "Data received FROM TERMINAL: " << data.toHex( ' ' );
		_udp_to_board.writeDatagram( data, QHostAddress::LocalHost, constant::port_balans_to_board );

		std::memcpy( &data_struct, data.data(), sizeof( command_s ) );
		stor_cl->set_que_data( data_struct.kassa, data_struct.numer_que );
	}

	//qDebug() << "QUEUE number: " << static_cast<int>( data[ 0 ] ) << "  Kassa TYPE:" << static_cast<int>( data[ 1 ] );
}

producer_cl::~producer_cl() {

	delete stor_cl;
}
