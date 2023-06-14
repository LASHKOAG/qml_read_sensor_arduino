#include "serialport.h"

SerialPort::SerialPort(QObject *parent) : QObject(parent)
{
    portName = "/dev/ttyUSB0";

    COMPORT = new QSerialPort();
    COMPORT->setPortName(portName);
    //COMPORT->setPortName("COM3");
    COMPORT->setBaudRate(QSerialPort::BaudRate::Baud9600);
    COMPORT->setParity(QSerialPort::Parity::NoParity);
    COMPORT->setDataBits(QSerialPort::DataBits::Data8);
    COMPORT->setStopBits(QSerialPort::StopBits::OneStop);
    COMPORT->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    COMPORT->open(QIODevice::ReadWrite);

    if(COMPORT->isOpen()){
        qDebug() << "Serial port is connected.";
        qDebug() << COMPORT->error();
    }else{
        qDebug() << "Serial port is not connected.";
        qDebug() << COMPORT->error();
    }

    QObject::connect(COMPORT, SIGNAL(readyRead()), this, SLOT(read_data()));
    QObject::connect(COMPORT, SIGNAL(error(QSerialPort::SerialPortError)), this,
                SLOT(handleError(QSerialPort::SerialPortError)));

    //получим список доступных в системе COM портов при помощи QSerialPortInfo
    /*foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts() ) {
        QSerialPort port;
        port.setPort(info);
        if(port.open(QIODevice::ReadWrite)){
            qDebug() << "Name of COM PORT: " + info.portName() + " " + info.description() + info.manufacturer();
        }
    }*/

    //получим список доступных в системе COM портов при помощи QSerialPortInfo
    //"ttyUSB0 [Busy: Yes]" - устройство подключено
    //"ttyS3 [Busy: No]"
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QString portN = QString("%1 [Busy: %2]")
                .arg(info.portName())
                .arg((info.isBusy() ? "Yes" : "No"));

        qDebug() << portN;

        //так можно автоматизировать получение наименование порта
        //Port to use:  "ttyUSB0"
        if(info.isBusy()){
            QString str = info.portName();
            qDebug() << "Port to use: " << str;
        }
    }

    // currentPortName: "/dev/ttyUSB0"
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QString currentPortName = info.systemLocation();
        qDebug() << "currentPortName: " << currentPortName;
    }

    //таймеров заводить можно много и необходимо отличать каждый от другого
    //на конкретно этот будет event периодически делать попытки открыть порт
    id_timer_update = -1;

}

SerialPort::~SerialPort()
{
    COMPORT->close();
    delete COMPORT;
}

void SerialPort::on_pushButton_send_clicked()
{
    if(COMPORT->isOpen()){
        //send 10 ("\n")
        //send 13 ("\r")
        //COMPORT->write(ui->lineEdit_Serial_Data->text().toLatin1() + char(10));
        //qDebug() << "Data from App: " << ui->lineEdit_Serial_Data->text().toLatin1() + char(10);
        COMPORT->flush();
    }
}

void SerialPort::read_data()
{
    if(COMPORT->isOpen()){
        while(COMPORT->bytesAvailable()){
            Data_From_SerialPort += COMPORT->readAll();
            if(Data_From_SerialPort.at(Data_From_SerialPort.length()-1) == char(10)){
                is_Data_Recevied = true;
            }
        }

        if(is_Data_Recevied == true){
            qDebug() << "Data from Serial Port: " << Data_From_SerialPort;
            //ui->textEdit->append(Data_From_SerialPort);
            Data_From_SerialPort = "";
            is_Data_Recevied = false;
        }
    }else{
        qDebug() << "Serial port is not connected.";
        qDebug() << COMPORT->error();
    }
}

void SerialPort::on_pushButton_On_clicked()
{
    QString str = "On";
    qint64 result = COMPORT->write(str.toLatin1() + char(10));
    qDebug() << result;
    COMPORT->flush();
}

void SerialPort::on_pushButton_Off_clicked()
{
    QFileInfo info_about_port(portName);
    //qDebug() << "info_about_port.exists(): " << info_about_port.exists();

//    if(!info_about_port.exists()){
//        qDebug() << "Serial port is not connected.";
//        qDebug() << COMPORT->error();
//        return;
//    }

    QString str = "Off";
    qint64 result = COMPORT->write(str.toLatin1() + char(10));
    qDebug() << result;
    COMPORT->flush();
}

void SerialPort::handleError(QSerialPort::SerialPortError error)
{
    if(COMPORT->isOpen()){
        qDebug() << "handleError():" << error;
        COMPORT->close();
        qDebug() << "COMPORT->isOpen():" << COMPORT->isOpen();
        id_timer_update = startTimer(2000);
    }
}

void SerialPort::timerEvent(QTimerEvent *event)
{
    qDebug() << "timerEvent(): ";

    if (event->timerId() == id_timer_update) {
        qDebug() << "id_timer_update: ";
        if(COMPORT->open(QIODevice::ReadWrite)){
            qDebug() << "COMPORT->open usb0 ";
            if (id_timer_update != -1){
                killTimer(id_timer_update);
                id_timer_update = -1;
            }
        }else{
            if(portName == "/dev/ttyUSB0"){
                portName = "/dev/ttyUSB1";
            }else{
                portName = "/dev/ttyUSB0";
            }

            if(COMPORT->open(QIODevice::ReadWrite)){
                qDebug() << "COMPORT->open usb1 ";
                if (id_timer_update != -1){
                    killTimer(id_timer_update);
                    id_timer_update = -1;
                }
            }
        }

    }

}
