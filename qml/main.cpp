//#include "mainwindow.h"
//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
//}


#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "apiscontroller.h"
#include "apielementscontroller.h"
#include "database.h"
#include "apicacheupdatedaemon.h"
#include "apielementcommentmodel.h"

Database db;
ApiCacheUpdateDaemon *daemon;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<ApisController>("MyControllers", 1, 0, "ApisController");
    qmlRegisterType<ApiElementsController>("MyControllers", 1, 0, "ApiElementsController");
    qmlRegisterType<ApiElementCommentModel>("MyControllers", 1, 0, "ApiElementCommentModel");

    daemon = new ApiCacheUpdateDaemon();
    QObject::connect(&app, &QGuiApplication::aboutToQuit, &app, [daemon](){
        daemon->finish();
    });
    daemon->start();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
