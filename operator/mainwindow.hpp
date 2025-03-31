#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QByteArray>
#include <QDebug>
#include <QMainWindow>
#include <QMap>
#include <QPushButton>
#include <QUdpSocket>
#include "data_types.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow( QWidget* parent = nullptr );
	~MainWindow();

private:
	Ui::MainWindow* ui;
	QUdpSocket udp_socket;
	QUdpSocket udp_send;
	command_s data_struct;
	QByteArray b_array[ 4 ];
	QVector<QPushButton*> vec_but;
	QVector<QPushButton*> vec_cl_but;
	QMap<quint32, quint8> all_client_map;

private slots:

	void slot_request_client();
	void slot_remove_client();
};
#endif // MAINWINDOW_HPP
