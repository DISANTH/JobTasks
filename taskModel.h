#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QAbstractListModel>
#include "task.h"

class Task;

class TaskModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Task* tasks READ getTasks WRITE setTasks)
public:
    explicit TaskModel(QObject *parent = nullptr);

    enum {
        TaskNameRole = Qt::UserRole,
    };
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Task* getTasks() const;
    void setTasks(Task *tasks);

private:
    Task* tasks;
};

#endif // TASKMODEL_H
