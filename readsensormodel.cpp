#include "readsensormodel.h"

ReadSensorModel::ReadSensorModel(QObject *parent)
    : QAbstractListModel(parent), mSensorList(nullptr)
{
}

int ReadSensorModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mSensorList)
        return 0;

    // FIXME: Implement me!
    return mSensorList->items().size();
}

QVariant ReadSensorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mSensorList)
        return QVariant();

    const ReadSensorItem item = mSensorList->items().at(index.row());

    //    // FIXME: Implement me!
    //    switch (role) {
    //    case SensorAddresssRole:
    //        return QVariant(0);
    //    case SensorNameRole:
    //        return QVariant(QStringLiteral("SENSOR NAME"));
    //    case SensorDataRole:
    //        return QVariant(357);
    //    }

    switch (role) {
    case SensorAddresssRole:
        return QVariant(item.sensor_address);
    case SensorNameRole:
        return QVariant(item.sensor_name);
    case SensorDataRole:
        return QVariant(item.sensor_data);
    }

    return QVariant();
}

bool ReadSensorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mSensorList){
        return false;
    }

    ReadSensorItem item = mSensorList->items().at(index.row());

    switch (role) {
    case SensorAddresssRole:
        item.sensor_address = value.toInt();
        break;
    case SensorNameRole:
        item.sensor_name = value.toString();
        break;
    case SensorDataRole:
        item.sensor_name = value.toInt();
        break;
    }

    if(mSensorList->setItemAt(index.row(), item)){
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ReadSensorModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> ReadSensorModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[SensorAddresssRole] = "sensor_address";
    names[SensorNameRole] = "sensor_name";
    names[SensorDataRole] = "sensor_data";

    return names;
}


ReadSensorCpp *ReadSensorModel::sensorList() const
{
    return mSensorList;
}

void ReadSensorModel::setSensorList(ReadSensorCpp *newSensorList)
{
//    if (mSensorList == newSensorList)
//        return;
//    mSensorList = newSensorList;
//    emit sensorListChanged();

    beginResetModel();

    if(mSensorList){
        mSensorList->disconnect(this);
    }

    mSensorList = newSensorList;

    if(mSensorList){
        connect(mSensorList, &ReadSensorCpp::preItemAppended, this, [=](){
            const int index = mSensorList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mSensorList, &ReadSensorCpp::postItemAppended, this, [=](){
            endInsertRows();
        });
        connect(mSensorList, &ReadSensorCpp::preItemRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mSensorList, &ReadSensorCpp::postItemRemoved, this, [=](){
            endRemoveRows();
        });
    }

    endResetModel();
}
