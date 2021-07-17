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

    Q_INVOKABLE bool savePluginsConfig(
        const QString& filename,
        const QString& socketIid,
        const QStringList& filtersIids,
        const QString& pluginIid); 

    Q_INVOKABLE bool loadPluginsConfig(const QString& filename);

private slots:
    void newPluginIntegrationObject(QObject* obj);        
    void selectedSocketPluginIidChanged(const QString& value);
    void selectedProtocolPluginIidChanged(const QString& value);
    void selectedFilterPluginsIidsChanged(const QStringList& values);

private:
    AppMgr();

    ListOfPluginInfos getPluginInfos(const QStringList& pluginIids);
    const QString& getPluginConfigQml(const QString& iid);

    PluginMgr m_pluginMgr;
};

} // namespace cc_view

} // namespace cc_tools
