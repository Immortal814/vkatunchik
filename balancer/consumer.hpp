#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include <QDataStream>
#include <QObject>
#include <QUdpSocket>
#include "data_types.hpp"

class consumer : public QObject
{
    Q_OBJECT
public:
    explicit consumer( QObject *parent = nullptr );
	~consumer();

public:
	// Берет данные из очереди и отправляет оператору
	void set_consum_que( QPair<quint8, quint32> );

private:

	QUdpSocket udp_socket;
	QUdpSocket udp_write;
	command_s data_struct;

private slots:

	void slot_from_operator();

signals:

	void sig_erase_client( quint8 kassa, quint32 client_num );
	void sig_get_client( quint8 kassa );
};

#endif // CONSUMER_HPP
