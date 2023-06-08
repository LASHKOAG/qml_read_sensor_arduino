#include "readsensormodel.h"

ReadSensorModel::ReadSensorModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ReadSensorModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return 20;
}

QVariant ReadSensorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    switch (role) {
    case SensorAddresssRole:
        return QVariant(0);
    case SensorNameRole:
        return QVariant(QStringLiteral("SENSOR NAME"));
    case SensorDataRole:
        return QVariant(357);
    }
    return QVariant();
}

bool ReadSensorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
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
