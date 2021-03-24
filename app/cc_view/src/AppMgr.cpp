#include "AppMgr.h"

#include <algorithm>
#include <iostream>

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
    QStringList pluginIidsList;
    pluginIidsList.append(socketIid);
    pluginIidsList.append(filtersIids);
    pluginIidsList.append(pluginIid);

    auto infos = getPluginInfos(pluginIidsList);
    return m_pluginMgr.needsReload(infos);
}


bool AppMgr::loadPlugins(
    const QString& socketIid,
    const QStringList& filtersIids,
    const QString& pluginIid)
{
    QStringList pluginIidsList;
    pluginIidsList.append(socketIid);
    pluginIidsList.append(filtersIids);
    pluginIidsList.append(pluginIid);

    auto infos = getPluginInfos(pluginIidsList);
    m_pluginMgr.unloadApplied();


    bool result = true;
    for (auto& i : infos) {
        auto* plugin = m_pluginMgr.loadPlugin(*i);
        if (plugin == nullptr) {
            std::cerr << "ERROR: Failed to load plugin: " << i->getIid().toStdString() << std::endl;
            assert(!"Should not happen");
            result = false;
            break;
        }

        std::cout << "Loaded: " << i->getIid().toStdString() << std::endl;
        auto obj = plugin->createObject();
        static_cast<void>(obj);
        // TODO
    }

    if (result) {
        m_pluginMgr.setAppliedPlugins(infos);
    }

    return result;
}

AppMgr::AppMgr()
{
    m_pluginMgr.setPluginsDir(getPluginsDir());
}

AppMgr::ListOfPluginInfos AppMgr::getPluginInfos(const QStringList& pluginIids)
{
    ListOfPluginInfos result;
    auto& availableInfos = m_pluginMgr.getAvailablePlugins();

    for (auto& p : pluginIids) {
        auto iter = 
            std::find_if(
                availableInfos.begin(), availableInfos.end(),
                [&p](auto& info)
                {
                    return p == info->getIid();
                });

        if (iter == availableInfos.end()) {
            std::cerr << "ERROR: Failed to find plugin " << p.toStdString() << std::endl;
            assert(!"Should not happen");
            continue;
        }

        result.push_back(*iter);
    }
    return result;
}


} // namespace cc_view

} // namespace cc_tools
