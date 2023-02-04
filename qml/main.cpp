
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include "apiscontroller.h"
#include "apielementscontroller.h"
#include "database.h"
#include "apicacheupdatedaemon.h"
#include "apielementcommentmodel.h"

Database db;
ApiCacheUpdateDaemon daemon;

void aboutToQuitHandler()
{
    daemon.finish();
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<ApisController>("MyControllers", 1, 0, "ApisController");
    qmlRegisterType<ApiElementsController>("MyControllers", 1, 0, "ApiElementsController");
    qmlRegisterType<ApiElementCommentModel>("MyControllers", 1, 0, "ApiElementCommentModel");


    QObject::connect(&app, &QCoreApplication::aboutToQuit, &aboutToQuitHandler);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject *apiElementsView = engine.rootObjects().at(0)->findChild<QObject*>("apiElementsView");
    ApiElementsController *apiElementsController = apiElementsView->findChild<ApiElementsController*>("controller");
    QObject::connect(&daemon, &ApiCacheUpdateDaemon::updated, apiElementsController, &ApiElementsController::refreshModel);
    daemon.start();


    return app.exec();
}
