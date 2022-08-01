#ifndef JOB_H
#define JOB_H

#include <QObject>
#include <QVector>
#include "task.h"

struct JobItem {
    QString name;
    Task* tasks;
    int area;
};

class Jobs : public QObject
{
    Q_OBJECT
public:
    explicit Jobs(QObject *parent = nullptr);
    QList<JobItem*> items() const;

    bool setJobAt(int index, JobItem *jobItem);
    bool setJobs(QList<JobItem*> jobList);
    void clear();
    ~Jobs();

signals:
    void preJobAppended();
    void postJobAppended();

    void preJobRemoved();
    void postJobRemoved();

public slots:
    void appendJob(JobItem *jobItem);

private:
    QList<JobItem*> jobList;
};

#endif // JOB_H
