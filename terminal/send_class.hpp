#ifndef SEND_CLASS_HPP
#define SEND_CLASS_HPP

#include <QByteArray>
#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include "data_types.hpp"

class send_class : public QObject
{
    Q_OBJECT
public:

    explicit send_class(QObject *parent = nullptr);
	void send_command( command_s* );
	~send_class();

private:
	// quint16 que_num = 0;
	QUdpSocket send_socket;

signals:
};

#endif // SEND_CLASS_HPP
