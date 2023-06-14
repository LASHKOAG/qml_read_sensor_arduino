#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Send_clicked();
    void Read_Data();
    void on_pushButton_On_clicked();
    void on_pushButton_Off_clicked();

    void handleError(QSerialPort::SerialPortError error);

protected:
    void timerEvent(QTimerEvent *event);

private:
    Ui::MainWindow *ui;
    QSerialPort* COMPORT;
    QString Data_From_SerialPort;
    bool is_Data_Recevied = false;

    QString portName;

    int id_timer_update;
};
#endif // MAINWINDOW_H
