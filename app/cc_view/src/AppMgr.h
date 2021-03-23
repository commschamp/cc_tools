#pragma once

#include <QtCore/QObject>

#include "cc_tools/cc_app/PluginMgr.h"

namespace cc_tools
{

namespace cc_view
{

class AppMgr : public QObject
{
    Q_OBJECT
public:
    using PluginMgr = cc_tools::cc_app::PluginMgr;
    using ListOfPluginInfos = PluginMgr::ListOfPluginInfos;

    static AppMgr& instance();

    PluginMgr& pluginMgr()
    {
        return m_pluginMgr;
    }

    Q_INVOKABLE bool requiresPluginsReloadConfirmation(
        const QString& socketIid,
        const QStringList& filtersIids,
        const QString& pluginIid);

    Q_INVOKABLE bool loadPlugins(
        const QString& socketIid,
        const QStringList& filtersIids,
        const QString& pluginIid);

private:
    AppMgr();

    ListOfPluginInfos getPluginInfos(const QStringList& pluginIids);

    PluginMgr m_pluginMgr;
};

} // namespace cc_view

} // namespace cc_tools
