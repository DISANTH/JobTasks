#ifndef PATHMODEL_H
#define PATHMODEL_H
#include <QAbstractListModel>
#include "path.h"
#include "job.h"
#include "task.h"

class Paths;

class PathModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Paths *paths READ getPaths WRITE setPaths)
public:
    explicit PathModel(QObject *parent = nullptr);
    enum {
        PathNameRole = Qt::UserRole,
    };
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

//    bool setData(const QModelIndex &index, const QVariant &value,
//                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Paths *getPaths() const;
    void setPaths(Paths *paths);

private:
    Paths *paths;

};

#endif // PATHMODEL_H
