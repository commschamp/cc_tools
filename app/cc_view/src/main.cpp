#include <QtWidgets/QApplication>
#include <QtGui/QIcon>
#include <QQmlApplicationEngine>

#include "GuiState.h"

namespace 
{

QObject *getGuiState(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    auto* st = cc_tools::cc_view::GuiState::instancePtr();
    QQmlEngine::setObjectOwnership(st, QQmlEngine::CppOwnership);
    return st;
}

void qmlRegisterGuiStateSingleton()
{
    qmlRegisterSingletonType<cc_tools::cc_view::GuiState>("CC", 1, 0, "CC_GuiState", &getGuiState);
}

} // namespace 


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/image/app_icon.png"));

    qmlRegisterGuiStateSingleton();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}