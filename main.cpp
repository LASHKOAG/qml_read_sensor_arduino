#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "readsensormodel.h"
#include "readsensorcpp.h"

#include <QQmlContext>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<ReadSensorModel>("ReadSensor", 1, 0, "ReadSensorModel");

    qmlRegisterUncreatableType<ReadSensorCpp>("ReadSensor", 1, 0, "ReadSensorCpp",
                           QStringLiteral("ReadSensorCpp should not be created in QML"));

    ReadSensorCpp readSensor;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(QStringLiteral("readSensor"), &readSensor);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
