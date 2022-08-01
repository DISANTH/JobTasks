#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


#include "job.h"
#include "path.h"
#include "task.h"
#include "jobModel.h"
#include "pathModel.h"
#include "taskModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<PathModel>("Path", 1, 0, "PathModel");
    qmlRegisterType<JobModel>("Job", 1, 0, "JobModel");
    qmlRegisterType<TaskModel>("Task", 1, 0, "TaskModel");

    qmlRegisterUncreatableType<Paths>("Path", 1, 0, "Paths",
        QStringLiteral("Paths should not be created in QML"));

    qmlRegisterUncreatableType<Jobs>("Job", 1, 0, "Jobs",
        QStringLiteral("Jobs should not be created in QML"));

    qmlRegisterUncreatableType<Task>("Task", 1, 0, "Task",
        QStringLiteral("Task should not be created in QML"));

    Paths paths;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("paths"), &paths);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
