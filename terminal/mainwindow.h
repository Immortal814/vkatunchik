#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QByteArray>
#include <QDebug>
#include <QMainWindow>
#include <QVBoxLayout>
#include "send_class.hpp"

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

	command_s data_struct;
	Ui::MainWindow* ui;
	send_class *_send_cl;

private slots:

    void slot_click();
};
#endif // MAINWINDOW_H
