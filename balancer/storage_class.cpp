#include "storage_class.hpp"

storage_class::storage_class( QObject* parent ) : QObject{ parent } {

	consum_cl = new consumer;

	connect( consum_cl, &consumer::sig_erase_client, this, &storage_class::slot_erase_client );
	// Принимается сигнал, чтобы передать в функцию данные Хэх
	connect( consum_cl, &consumer::sig_get_client, this, &storage_class::slot_get_client );
}

void storage_class::set_que_data( quint8 kassa, quint32 num ) {

	//kassa_list[ kassa ].enqueue( QPair( kassa, num ) );
	// Добавляем элемент в нужную мапу
	kassa_list[ kassa ].enqueue( QPair( kassa, num ) );

	//kassa_map[ kassa ].insert( num, kassa );
	// Для отправки оператору
}

void storage_class::slot_get_client( quint8 kassa ) {

	consum_cl->set_consum_que( kassa_list[ kassa ].head() );

	//QPair<quint8, quint32> test = kassa_list[ kassa ].head();
}

void storage_class::slot_erase_client( quint8 kassa ) {

	kassa_list[ kassa ].dequeue();
	//kassa_map[ kassa ].remove( client_num );
}

storage_class::~storage_class() {

	delete consum_cl;
}
