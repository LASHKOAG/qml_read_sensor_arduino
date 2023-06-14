#include "mainwindow.h"
#include "ui_mainwindow.h"

//main idea take from:
//Qt C++ GUI Application Tutorial | Qt QSerialPort | How to use and connect with SerialPort
//Qt With Ketan
//https://www.youtube.com/watch?v=LXPdOFH5NLA&list=PLh0cogPqXcJMuRUNMgGZwl5WEX6ZDGqaU&index=3

// add serialport in pro !!


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    QObject::connect(COMPORT, SIGNAL(readyRead()), this, SLOT(Read_Data()));
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

MainWindow::~MainWindow()
{
    COMPORT->close();
    delete ui;
    delete COMPORT;
}


void MainWindow::on_pushButton_Send_clicked()
{
    if(COMPORT->isOpen()){
        //send 10 ("\n")
        //send 13 ("\r")
        COMPORT->write(ui->lineEdit_Serial_Data->text().toLatin1() + char(10));
        qDebug() << "Data from App: " << ui->lineEdit_Serial_Data->text().toLatin1() + char(10);
        COMPORT->flush();
    }
}

void MainWindow::Read_Data()
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
            ui->textEdit->append(Data_From_SerialPort);
            Data_From_SerialPort = "";
            is_Data_Recevied = false;
        }
    }else{
        qDebug() << "Serial port is not connected.";
        qDebug() << COMPORT->error();
    }

/*
    //other way get data from device:
    if(COMPORT->isOpen()){
        QByteArray ba;
        ba = COMPORT->readAll();
        ui->textEdit->append(ba);           //just text
        //ui->label->setText(ba.toHex());   //number in hex presentation
    }
*/

}


void MainWindow::on_pushButton_On_clicked()
{
    //1 ый способ - так делать не совсем верно. Физически com может существовать(например "ICP CON", это преобразователь интрфейса)
    //таким образом устройство, которое висит на ICP CON может отвалиться, но при этом /dev/ttyUSB0 будет себе существовать.
    //Однако, если у вас что то вроде ардуино, то есть устройство напрямую подключено, то такое тоже можно попробовать.
    //Отключаем физически из USB порта устройство и /dev/ttyUSB0 не должно быть.
//    QFileInfo info_about_port(portName);
    //qDebug() << "info_about_port.exists(): " << info_about_port.exists();

//    if(!info_about_port.exists()){
//        qDebug() << "Serial port is not connected.";
//        qDebug() << COMPORT->error();
//        return;
//    }

    QString str = "On";
    qint64 result = COMPORT->write(str.toLatin1() + char(10));
    qDebug() << result;
    COMPORT->flush();
}


void MainWindow::on_pushButton_Off_clicked()
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


//Система подкинет event через connect, что SIGNAL(error(QSerialPort::SerialPortError))
//Другими словами - устройство отвалилось.
//handleError() - это обработчик этой ситуации
//сигнал SIGNAL(error(QSerialPort::SerialPortError) генерируется с большой частотой
//закрываем порт
//стартуем таймер и получаем id этого таймера.
//этот таймер каждые N миллисекунд выкидывает свой event, который обрабатывается в timerEvent(QTimerEvent *event)
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if(COMPORT->isOpen()){
        qDebug() << "handleError():" << error;
        COMPORT->close();
        qDebug() << "COMPORT->isOpen():" << COMPORT->isOpen();
        id_timer_update = startTimer(2000);
    }
}


//обработчик, что делать, когда таймер выдаст свой event
//таймеров может быть много, мы отрабатываем каждый.
//Конкретно в этом случае только один таймер и его id - это id_timer_update
//пытаемся открыть порт, если не получается - пробуем это сделать на следующей итерации срабатывании таймера
//Если открыть получилось - то убиваем таймер и инициализируем id  ->-> -1
//здесь пример изменения наименование порта руками. Что некорректно, но для общего представления
void MainWindow::timerEvent(QTimerEvent *event)
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

