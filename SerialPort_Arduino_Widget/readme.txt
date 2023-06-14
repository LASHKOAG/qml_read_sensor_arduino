подключили serialport в pro иначе #include <QSerialPort> не будет виден

mainwindow.h подключили #include <QSerialPort>


//main idea take from:
//Qt C++ GUI Application Tutorial | Qt QSerialPort | How to use and connect with SerialPort
//Qt With Ketan
//https://www.youtube.com/watch?v=LXPdOFH5NLA&list=PLh0cogPqXcJMuRUNMgGZwl5WEX6ZDGqaU&index=3

// add serialport in pro !!


Работа с com-портами в Qt / QtSerialPort
Qt Notes
https://www.youtube.com/watch?v=XQVFcEBJoEk
тут только read
//получим список доступных в системе COM портов при помощи QSerialPortInfo
    /*foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts() ) {
        QSerialPort port;
        port.setPort(info);
        if(port.open(QIODevice::ReadWrite)){
            qDebug() << "Name of COM PORT: " + info.portName() + " " + info.description() + info.manufacturer();
        }
    }*/
    
и
чтение

/*
    //other way get data from device:
    if(COMPORT->isOpen()){
        QByteArray ba;
        ba = COMPORT->readAll();
        ui->textEdit->append(ba);           //just text
        //ui->label->setText(ba.toHex());   //number in hex presentation
    }
*/

