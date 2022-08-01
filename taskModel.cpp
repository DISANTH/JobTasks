#include "taskModel.h"

TaskModel::TaskModel(QObject *parent)
    : QAbstractListModel(parent), tasks(nullptr)
{

}

int TaskModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !tasks ) {
        return 0;
    }

    return tasks->items().size();
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !tasks)
        return QVariant();
    const QString task = tasks->items().at(index.row());
    switch (role) {
    case TaskNameRole:
        return QVariant(task);
    }

    return QVariant();

}

bool TaskModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!tasks)
        return false;
    //TaskItem *taskItem= tasks->items().at();

    switch (role) {
    case TaskNameRole:
        tasks->setTaskAt(index.row(),value.toString());
        //taskItem->name = value.toString();
        break;
    }
    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}

Qt::ItemFlags TaskModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> TaskModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TaskNameRole] = "name";
    return names;
}

Task *TaskModel::getTasks() const
{
    return tasks;
}

void TaskModel::setTasks(Task *tasksData)
{
    beginResetModel();
    if (tasks)
        tasks->disconnect(this);

    this->tasks = tasksData;
    endResetModel();
}
