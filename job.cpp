#include "job.h"

Jobs::Jobs(QObject *parent) : QObject(parent)
{

}

QList<JobItem*> Jobs::items() const
{
    return jobList;
}

bool Jobs::setJobAt(int index, JobItem *jobItem)
{
    if (index < 0 || index >= jobList.size())
        return false;

    const JobItem *oldJobItem = jobList.at(index);
    if (jobItem->name == oldJobItem->name && jobItem->area == oldJobItem->area)
        return  false;

    jobList[index] = jobItem;
    return true;

}

bool Jobs::setJobs(QList<JobItem*> jobList)
{
    jobList = jobList;
    return true;
}

void Jobs::clear()
{
    for(JobItem* jobItem:jobList){
        Task* tasks = jobItem->tasks;
        if(tasks)
            tasks->clear();
        delete jobItem;
    }
    jobList.clear();
}

Jobs::~Jobs()
{
    clear();
}


void Jobs::appendJob(JobItem *jobItem)
{
    emit preJobAppended();
    jobList.append(jobItem);

    emit postJobAppended();
}
