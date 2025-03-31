#ifndef SOCKET_CLASS_HPP
#define SOCKET_CLASS_HPP

#include <QObject>
#include <QUdpSocket>
#include "data_types.hpp"

class socket_class : public QObject
{
	Q_OBJECT
public:
	explicit socket_class( QObject *parent = nullptr );

private:

	QUdpSocket _udp_socket;
	command_s data_struct;

private slots:

	void slot_data_received();
	//void slot_remove();

signals:

	void sig_received_command( const command_s* );
};

#endif // SOCKET_CLASS_HPP
