#include "task.h"

Task::Task(QObject *parent) : QObject(parent)
{

}

QVector<QString> Task::items() const
{
    return tasks;
}

bool Task::setTask(QVector<QString> taskItems)
{
    tasks = taskItems;
    return true;
}

bool Task::setTaskAt(int i,QString task)
{
    if(tasks.size() > i){
        tasks[i] = task;
        return true;
    }
    return false;
}

void Task::clear()
{
    tasks.clear();
}

Task::~Task()
{
    clear();
}

void Task::appendTask(QString task)
{
    emit preTaskAppended();
    tasks.append(task);
    emit postTaskAppended();
}
