#ifndef READSENSORCPP_H
#define READSENSORCPP_H

#include <QObject>
#include <QVector>

#include <QDebug>

#include "serialport.h"

// этот класс должен уметь:
// изменять
// добавлять элемент
// удалять элемент

struct ReadSensorItem {
    int sensor_address;
    QString sensor_name;
    int sensor_data;
};

class ReadSensorCpp : public QObject
{
    Q_OBJECT
public:
    explicit ReadSensorCpp(QObject *parent = nullptr);

    //getter
    QVector<ReadSensorItem> items() const;

    //setter
    bool setItemAt(int index, const ReadSensorItem &item);

signals:
    void preItemAppended();

    void postItemAppended();


    void preItemRemoved(int index);

    void postItemRemoved();

public slots:

    void appendItem();

    void removeCompletedItems(int index);

private:
    QVector<ReadSensorItem> mItems;
    SerialPort* serial;

};

#endif // READSENSORCPP_H
