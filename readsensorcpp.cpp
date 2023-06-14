#include "readsensorcpp.h"

ReadSensorCpp::ReadSensorCpp(QObject *parent) : QObject(parent)
{
    serial = new SerialPort();

    mItems.append({0x44, QStringLiteral("Fotoresistor"), 177});
    mItems.append({0x47, QStringLiteral("Colorsensor"), 255});
}

ReadSensorCpp::~ReadSensorCpp()
{
    if(serial != nullptr){
        delete serial;
    }
}

QVector<ReadSensorItem> ReadSensorCpp::items() const
{
    return mItems;
}

bool ReadSensorCpp::setItemAt(int index, const ReadSensorItem &item)
{
    if(index < 0 || index >= mItems.size()){
        return false;
    }

    const ReadSensorItem &oldItem = mItems.at(index);

    if(
            item.sensor_address == oldItem.sensor_address
            && item.sensor_name == oldItem.sensor_name
            && item.sensor_data == oldItem.sensor_data
      )
    {return false;}

    mItems[index] = item;

    return  true;
}

void ReadSensorCpp::appendItem()
{
    emit preItemAppended();

    ReadSensorItem item;
    item.sensor_address = 0x00;
    item.sensor_name = "SENSOR NAME";
    item.sensor_data = -1;
    mItems.append(item);
    qDebug() << "mItems.size(): " << mItems.size();

    emit postItemAppended();
}

void ReadSensorCpp::removeCompletedItems(int index)
{
    qDebug()<< "index: " << index;

    if(index < 0 || index >= mItems.size()){
        return;
    }

    emit preItemRemoved(index);
    mItems.removeAt(index);
    emit postItemRemoved();

//    for(int i = 0; i < mItems.size();){
//            if(mItems.at(i).done){
//                emit preItemRemoved(i);
//                mItems.removeAt(i);
//                emit postItemRemoved();
//            }else {
//                ++i;
//            }
    //        }
}

void ReadSensorCpp::turn_on_led()
{
    serial->on_pushButton_On_clicked();
}

void ReadSensorCpp::turn_off_led()
{
    serial->on_pushButton_Off_clicked();
}


