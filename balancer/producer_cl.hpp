#ifndef PRODUCER_CL_HPP
#define PRODUCER_CL_HPP

#include <QObject>
#include <QUdpSocket>
#include "data_types.hpp"
#include "storage_class.hpp"

class producer_cl : public QObject
{
    Q_OBJECT
public:
    explicit producer_cl( QObject *parent = nullptr );
    ~producer_cl();

private:

	QUdpSocket _udp_socket;
	QUdpSocket _udp_to_board;

	QByteArray que_kassa;
	command_s data_struct;

	storage_class* stor_cl;

private slots:

	void slot_data_received();

signals:
};

#endif // PRODUCER_CL_HPP
