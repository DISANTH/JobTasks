#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QVector>

struct TaskItem {
    QString name;
};

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = nullptr);
    QVector<QString> items() const;

    bool setTask(QVector<QString> taskItems);
    bool setTaskAt(int i,QString task);
    void clear();
    ~Task();

signals:
    void preTaskAppended();
    void postTaskAppended();

public slots:
    void appendTask(QString task);

private:
    QVector<QString> tasks;
};

#endif // TASK_H
