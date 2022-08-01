#include "pathModel.h"
#include "path.h"

#include <QDebug>

PathModel::PathModel(QObject *parent)
    : QAbstractListModel(parent), paths(nullptr)
{
    Paths *pathsData = new Paths();
    paths = pathsData;
}

int PathModel::rowCount(const QModelIndex &parent) const
{

    if (parent.isValid() || !paths ) {
        return 0;
    }

    return paths->items().size();
}

QVariant PathModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !paths)
        return QVariant();
    const PathItem *pathItem = paths->items().at(index.row());
    switch (role) {
    case PathNameRole:
        return QVariant(pathItem->name);

    }

    return QVariant();
}

Qt::ItemFlags PathModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> PathModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[PathNameRole] = "name";
    return names;
}

Paths *PathModel::getPaths() const
{
    return paths;
}

void PathModel::setPaths(Paths *pathsData)
{
    beginResetModel();
    if (paths)
        paths->disconnect(this);
    paths = pathsData;
    endResetModel();
}
