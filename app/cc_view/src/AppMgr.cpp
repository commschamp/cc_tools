#include "AppMgr.h"

#include "QtCore/QDir"
#include "QtCore/QCoreApplication"

namespace cc_tools
{

namespace cc_view
{

namespace 
{

QString getRootDir()
{
    QDir appDir(qApp->applicationDirPath());
    if (!appDir.cdUp()) {
        return QString();
    }

    return appDir.path();
}

QString getPluginsDir()
{
    QDir dir(getRootDir());
    if (!dir.cd("lib")) {
        return QString();
    }

    if (!dir.cd("cc_tools")) {
        return QString();
    }

    if (!dir.cd("plugin")) {
        return QString();
    }

    return dir.path();
}


} // namespace 


AppMgr& AppMgr::instance()
{
    static AppMgr obj;
    return obj;
}

bool AppMgr::requiresPluginsReloadConfirmation(
    const QString& socketIid,
    const QStringList& filtersIids,
    const QString& pluginIid)
{
    static_cast<void>(socketIid);
    static_cast<void>(filtersIids);
    static_cast<void>(pluginIid);
    // TODO
    return true;
}


bool AppMgr::loadPlugins(
    const QString& socketIid,
    const QStringList& filtersIids,
    const QString& pluginIid)
{
    static_cast<void>(socketIid);
    static_cast<void>(filtersIids);
    static_cast<void>(pluginIid);
    // TODO:
    return false;
}

AppMgr::AppMgr()
{
    m_pluginMgr.setPluginsDir(getPluginsDir());
}


} // namespace cc_view

} // namespace cc_tools
