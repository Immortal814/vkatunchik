#include "send_class.hpp"

send_class::send_class( QObject *parent )
    : QObject{ parent } {
    
    
}

void send_class::send_command( command_s* com ) {

	//que_num++;
	//com.append( que_num );
	QByteArray data;
	data.resize( sizeof( command_s ) );
	std::memcpy( data.data(), com, sizeof( command_s ) );
	send_socket.writeDatagram( data, QHostAddress::LocalHost, constant::port_term_to_que );
	send_socket.waitForBytesWritten( 100 );
	qDebug() << "Data send From Terminal! : "  << data.toHex(' ');
}

send_class::~send_class() {};
