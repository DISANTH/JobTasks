#ifndef JOBMODEL_H
#define JOBMODEL_H

#include <QAbstractListModel>
#include "job.h"

class Jobs;

class JobModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Jobs *jobs_ READ getJobs WRITE setJobs)
public:
    explicit JobModel(QObject *parent = nullptr);

    enum {
        JobNameRole = Qt::UserRole};
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Jobs *getJobs() const;
    void setJobs(Jobs *jobs);

private:
    Jobs *jobs_;
};

#endif // JOBMODEL_H
