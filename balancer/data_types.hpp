#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

#include <QtGlobal>

namespace constant {

	const quint16 port_term_to_que = 12400;
	const quint16 port_que_listen = 12401;

	const quint16 port_balans_to_board = 12402;
	const quint16 port_listen_board = 12403;

	const quint16 port_operator_consumer = 12405;
	const quint16 port_consumer_operator = 12406;

} // namespace constant

#pragma pack( push, 1 )
struct command_s
{
	quint8 command = 0;
	quint8 kassa;
	quint32 numer_que = 1;
};
#pragma pack( pop )

enum terminal_type_e : quint8 {

	CREDIT = 0,
	KASSA,
	PAYMENT,
	CARD

};

enum commands_e : quint8 {

	ADD = 0x01,
	REMOVE = 0x02,
	C_REQUEST = 0x03

};

#endif // DATA_TYPES_HPP
