#ifndef STORAGE_CLASS_HPP
#define STORAGE_CLASS_HPP

#include <QMap>
#include <QObject>
#include <QPair>
#include <QQueue>
#include "consumer.hpp"
#include "data_types.hpp"

class storage_class : public QObject
{
	Q_OBJECT
public:
	explicit storage_class( QObject* parent = nullptr );
	void set_que_data( quint8, quint32 );
	//void erase_client( quint8, quint32 );
	~storage_class();

private:

	QQueue<QPair<quint8, quint32>> kassa_list[ 4 ];
	//QMap<quint32, quint8> kassa_map[ 4 ];
	consumer* consum_cl;

private slots:

	void slot_get_client( quint8 );
	void slot_erase_client( quint8 );

signals:
};

#endif // STORAGE_CLASS_HPP
