#ifndef READSENSORMODEL_H
#define READSENSORMODEL_H

#include <QAbstractListModel>

class ReadSensorModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ReadSensorModel(QObject *parent = nullptr);

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

private:
};

#endif // READSENSORMODEL_H
