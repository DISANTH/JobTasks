#ifndef PATH_H
#define PATH_H

#include <QObject>
#include <QVector>
#include <QDir>

#include "job.h"
#include "task.h"

struct PathItem {
    QString name;
    Jobs* jobs;
};

class Paths : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int activePath READ activePath WRITE activePath)
    Q_PROPERTY(int activeJob READ activeJob WRITE activeJob)
    Q_PROPERTY(Jobs* activeJobs READ activeJobs)
    Q_PROPERTY(Task* activeTasks READ activeTasks)

public:
    explicit Paths(QObject *parent = nullptr);
    QList<PathItem*> items() const;

    int activePath() const;
    void activePath(int currentPath);

    int activeJob() const;
    void activeJob(int currentJob);

    Jobs* activeJobs() const;
    Task* activeTasks() const;

    int setJobs();
    int setTasks();


signals:

public slots:

private:
    QList<PathItem*> paths;
    int _activePath;
    int _activeJob;
};

#endif // PATH_H
