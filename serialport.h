#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFileInfo>
#include <QTimerEvent>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort();
public slots:
    void on_pushButton_On_clicked();
    void on_pushButton_Off_clicked();

private slots:
    void on_pushButton_send_clicked();
    void read_data();
//    void on_pushButton_On_clicked();
//    void on_pushButton_Off_clicked();

    void handleError(QSerialPort::SerialPortError error);

protected:
    void timerEvent(QTimerEvent *event);

private:
    QSerialPort* COMPORT;
    QString Data_From_SerialPort;
    bool is_Data_Recevied = false;

    QString portName;

    int id_timer_update;

};

#endif // SERIALPORT_H
