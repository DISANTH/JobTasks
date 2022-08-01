#include "jobModel.h"

JobModel::JobModel(QObject *parent)
    : QAbstractListModel(parent), jobs_(nullptr)
{
    Jobs *jobs = new Jobs();
    jobs_ = jobs;
}

int JobModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !jobs_ ) {
        return 0;
    }

    return jobs_->items().size();
}

QVariant JobModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !jobs_)
        return QVariant();
    const JobItem *job = jobs_->items().at(index.row());
    switch (role) {
    case JobNameRole:
        return QVariant(job->name);
    }
    return QVariant();
}

bool JobModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!jobs_)
        return false;
    JobItem *job = jobs_->items().at(index.row());

    switch (role) {
    case JobNameRole:
        job->name = value.toString();
        break;
    }

    if (jobs_->setJobAt(index.row(), job)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags JobModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> JobModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[JobNameRole] = "name";
    return names;
}


Jobs *JobModel::getJobs() const
{
    return jobs_;
}

void JobModel::setJobs(Jobs *jobs)
{
    beginResetModel();
        if (jobs_)
            jobs_->disconnect(this);

        jobs_ = jobs;

//        if (mjobs) {
//            connect(mjobs, &jobs::prejobAppended, this, [=]() {
//                const int index = mjobs->items().size();
//                beginInsertRows(QModelIndex(), index, index);
//            });
//            connect(mjobs, &jobs::postjobAppended, this, [=]() {
//                endInsertRows();
//            });
//            connect(mjobs, &jobs::prejobRemoved, this, [=](int index) {
//                beginRemoveRows(QModelIndex(), index, index);
//            });
//            connect(mjobs, &jobs::postjobRemoved, this, [=]() {
//                endRemoveRows();
//            });
//        }

        endResetModel();
}
