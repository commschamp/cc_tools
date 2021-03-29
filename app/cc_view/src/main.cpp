#include <QtWidgets/QApplication>
#include <QtGui/QIcon>
#include <QQmlApplicationEngine>

#include "cc_tools/cc_plugin/PluginIntegration.h"
#include "GuiState.h"
#include "AppMgr.h"
#include "PluginListModel.h"

namespace 
{

QObject *getPluginIntegration(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    auto* obj = cc_tools::cc_plugin::PluginIntegration::instancePtr();
    QQmlEngine::setObjectOwnership(obj, QQmlEngine::CppOwnership);
    return obj;
}

QObject *getGuiState(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    auto* st = cc_tools::cc_view::GuiState::instancePtr();
    QQmlEngine::setObjectOwnership(st, QQmlEngine::CppOwnership);
    return st;
}

QObject *getAppMgr(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    auto* mgr = &cc_tools::cc_view::AppMgr::instance();
    QQmlEngine::setObjectOwnership(mgr, QQmlEngine::CppOwnership);
    return mgr;
}

void qmlRegisterTypes()
{
    qmlRegisterSingletonType<cc_tools::cc_plugin::PluginIntegration>("CC", 1, 0, "CC_PluginIntegration", &getPluginIntegration);
    qmlRegisterSingletonType<cc_tools::cc_view::GuiState>("CC", 1, 0, "CC_GuiState", &getGuiState);
    qmlRegisterSingletonType<cc_tools::cc_view::AppMgr>("CC", 1, 0, "CC_AppMgr", &getAppMgr);

    qmlRegisterType<cc_tools::cc_view::PluginListModel>("CC", 1, 0, "CC_PluginListModel");
}

} // namespace 


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/image/app_icon.png"));

    qmlRegisterTypes();

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
