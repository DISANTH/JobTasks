#include "path.h"
#include <QDebug>

Paths::Paths(QObject *parent) : QObject(parent)
{
    QDir directory("/home/callippus/Documents/MyDocuments");
    QStringList csvFiles = directory.entryList(QStringList() << "*.csv",QDir::Files);
    foreach(QString filename, csvFiles) {
        PathItem *pathItem = new PathItem();
        pathItem->name =filename;
        paths.append(pathItem);
    }
}

QList<PathItem*> Paths::items() const
{
    return paths;
}

int Paths::activePath() const
{
    return _activePath;
}

void Paths::activePath(int currentPath)
{
    _activePath = currentPath;
    setJobs();
}

int Paths::activeJob() const
{
    return _activeJob;
}

void Paths::activeJob(int currentJob)
{
    this->_activeJob = currentJob;
    setTasks();
}

Jobs *Paths::activeJobs() const
{
    if ( _activePath >= 0 && _activePath <= paths.size()) {
        return paths[_activePath]->jobs;
    }
    else {
        return  nullptr;
    }
}

Task *Paths::activeTasks() const
{
    if ( _activePath >= 0 && _activePath <= paths.size()) {
        int noOfJobs = 0;
        Jobs* jobs = paths[_activePath]->jobs;
        if(!jobs)
            noOfJobs = jobs->items().size();
        if(_activeJob >= 0 && _activeJob <= noOfJobs){
            return paths[_activePath]->jobs->items().at(_activeJob)->tasks;
        }
        else {
            return  nullptr;
        }
    }
    else {
        return  nullptr;
    }
}

int Paths::setJobs()
{
    if ( _activePath >= 0 && _activePath <= paths.size()) {
        QString fileName = paths.at(_activePath)->name;
        QFile file(QString("/home/callippus/Documents/MyDocuments/%1").arg(fileName));
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << file.errorString();
            return 1;
        }
        Jobs* jobs= paths[_activePath]->jobs;
        if(!jobs){
            jobs = new Jobs();
        }
        else
            jobs->clear();
        QSet<QString> setData;
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            QString job = line.split(',')[0];
            setData.insert(job);
        }
        file.close();
        for(auto& val:setData)
        {
            JobItem *jobItem = new JobItem();
            jobItem->name = val;
            jobItem->area = 50000;
            jobs->appendJob(jobItem);
        }
        paths[_activePath]->jobs = jobs;
        return 0;
    }
    return -1;
}

int Paths::setTasks()
{
    if ( _activePath >= 0 && _activePath <= paths.size()) {
        if(_activeJob >= 0 && _activeJob <= paths[_activePath]->jobs->items().size()){
            QString fileName = paths.at(_activePath)->name;
            QFile file(QString("/home/callippus/Documents/MyDocuments/%1").arg(fileName));
            if (!file.open(QIODevice::ReadOnly)) {
                qDebug() << file.errorString();
                return 1;
            }
            JobItem* jobs = paths[_activePath]->jobs->items().at(_activeJob);
            Task* tasks= jobs->tasks;
            if(tasks)
                tasks->clear();
            else
                tasks = new Task;
            while (!file.atEnd()) {               
                QByteArray line = file.readLine();
                QString jobName = line.split(',')[0];
                QString taskName = line.split(',')[1];
                if(jobName.compare(jobs->name,Qt::CaseInsensitive) == 0){
//                    TaskItem* task = new TaskItem();
//                    task->name = taskName;
                    tasks->appendTask(taskName);
                }
            }
            file.close();

            paths[_activePath]->jobs->items().at(_activeJob)->tasks = tasks;
            return 0;
        }
    }
    return -1;
}
