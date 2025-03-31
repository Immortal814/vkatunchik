#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QByteArray>
#include <QMainWindow>
#include <QMap>
#include <QUdpSocket>
#include "data_types.hpp"
#include "socket_class.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr );
    ~MainWindow();

private:
	Ui::MainWindow* ui;
	socket_class* cl_socket;
	QUdpSocket _udp_socket;
	QMap<quint16, quint16> _client_list;

private:

        void set_table_info();

private slots:

        void slot_set_table( const command_s* );

};
#endif // MAINWINDOW_HPP
