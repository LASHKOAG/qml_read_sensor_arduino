#ifndef READSENSORMODEL_H
#define READSENSORMODEL_H

#include <QAbstractListModel>

#include "readsensorcpp.h"

class ReadSensorModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ReadSensorModel(QObject *parent = nullptr);

    Q_PROPERTY(ReadSensorCpp * sensorList READ sensorList WRITE setSensorList NOTIFY sensorListChanged)

    enum {
        SensorAddresssRole = Qt::UserRole,
        SensorNameRole,
        SensorDataRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    ReadSensorCpp* sensorList() const;
    void setSensorList(ReadSensorCpp *newSensorList);

    Q_INVOKABLE int get_size();

signals:
    void sensorListChanged();

private:
    ReadSensorCpp *mSensorList;

};

#endif // READSENSORMODEL_H
