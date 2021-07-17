#include "AppMgr.h"

#include <algorithm>
#include <iostream>

#include <QtCore/QUrl>
#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtQml/QQmlApplicationEngine>

#include "cc_tools/cc_plugin/PluginIntegration.h"
#include "GuiState.h"

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

QStringList preparePluginsList(
    const QString& socketIid,
    const QStringList& filtersIids,
    const QString& pluginIid)
{
    QStringList pluginIidsList;
    if (!socketIid.isEmpty()) {
        pluginIidsList.append(socketIid);
    }

    if (!filtersIids.isEmpty()) {
        pluginIidsList.append(filtersIids);
    }
    
    if (!pluginIid.isEmpty()) {
        pluginIidsList.append(pluginIid);
    }

    return pluginIidsList;
}

AppMgr::ListOfPluginInfos::const_iterator findPluginInfo(
    const AppMgr::ListOfPluginInfos& list,
    const QString& iid)
{
    return 
        std::find_if(
            list.begin(), list.end(),
            [&iid](auto& p)
            {
                return iid == p->getIid();
            });
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
    QStringList pluginIidsList = preparePluginsList(socketIid, filtersIids, pluginIid);

    GuiState::instance().setExtraToolbarElements(QStringList());
    m_pluginMgr.unloadApplied();

    auto infos = getPluginInfos(pluginIidsList);

    bool result = true;
    QStringList toolbarElems;
    for (auto& i : infos) {
        auto* plugin = m_pluginMgr.loadPlugin(*i);
        if (plugin == nullptr) {
            std::cerr << "ERROR: Failed to load plugin: " << i->getIid().toStdString() << std::endl;
            assert(!"Should not happen");
            result = false;
            break;
        }

        std::cout << "Loaded: " << i->getIid().toStdString() << std::endl;
        plugin->aboutToApply();
        auto obj = plugin->createObject();
        static_cast<void>(obj);

        // TODO: manage the created objects

        auto toolbarElem = plugin->getToolbarQmlElem();
        if (!toolbarElem.isEmpty()) {
            toolbarElems.append(toolbarElem);
        }
    }

    if (result) {
        m_pluginMgr.setAppliedPlugins(infos);
        GuiState::instance().setExtraToolbarElements(toolbarElems);
    }

    return result;
}

bool AppMgr::savePluginsConfig(
    const QString& filename,
    const QString& socketIid,
    const QStringList& filtersIids,
    const QString& pluginIid)
{
    QStringList pluginIidsList = preparePluginsList(socketIid, filtersIids, pluginIid);
    auto infos = getPluginInfos(pluginIidsList);
    return m_pluginMgr.savePluginsToConfigFile(infos, QUrl(filename).path());
}

bool AppMgr::loadPluginsConfig(const QString& filename)
{
    auto infos = m_pluginMgr.loadPluginsFromConfigFile(QUrl(filename).path());

    QString socket;
    QString protocol;
    QStringList filters;
    for (auto iter = infos.begin(); iter != infos.end(); ++iter) {
        auto& info = **iter;
        if (socket.isEmpty() && (info.getType() == PluginMgr::PluginInfo::Type::Socket)) {
            socket = info.getIid();
            continue;
        }

        if (protocol.isEmpty() && (info.getType() == PluginMgr::PluginInfo::Type::Protocol)) {
            protocol = info.getIid();
            continue;
        } 

        if (info.getType() != PluginMgr::PluginInfo::Type::Filter) {
            continue;
        }       

        filters.append(info.getIid());
    }

    auto& st = GuiState::instance();
    st.setSelectedSocketPluginIid(socket);
    st.setSelectedProtocolPluginIid(protocol);
    st.setSelectedFilterPluginsIids(filters);
    return true;
}

void AppMgr::newPluginIntegrationObject(QObject* obj)
{
    QQmlEngine::setObjectOwnership(obj, QQmlEngine::CppOwnership);
}

void AppMgr::selectedSocketPluginIidChanged(const QString& value)
{
    QString configQml = getPluginConfigQml(value);
    GuiState::instance().setSelectedSocketPluginConfigQml(configQml);
}

void AppMgr::selectedProtocolPluginIidChanged(const QString& value)
{
    QString configQml = getPluginConfigQml(value);
    GuiState::instance().setSelectedProtocolPluginConfigQml(configQml);
}

void AppMgr::selectedFilterPluginsIidsChanged(const QStringList& values)
{
    QStringList configQmls;
    for (auto& v : values) {
        configQmls.append(getPluginConfigQml(v));
    }
    GuiState::instance().setSelectedFilterPluginConfigQmls(configQmls);
}

AppMgr::AppMgr()
{
    m_pluginMgr.setPluginsDir(getPluginsDir());

    auto* pluginIntegration = cc_tools::cc_plugin::PluginIntegration::instancePtr();
    auto* guiState = GuiState::instancePtr();

    connect(
        pluginIntegration, &cc_tools::cc_plugin::PluginIntegration::sigNewIntegrationObject,
        this, &AppMgr::newPluginIntegrationObject);

    connect(
        pluginIntegration, &cc_tools::cc_plugin::PluginIntegration::sigActivateDialog,
        guiState, &GuiState::activateDialogByResourceAppend);    

    connect(
        pluginIntegration, &cc_tools::cc_plugin::PluginIntegration::sigCloseCurrentDialog,
        guiState, &GuiState::closeCurrentDialog); 

    connect(
        guiState, &GuiState::sigSelectedSocketPluginIidChanged,
        this, &AppMgr::selectedSocketPluginIidChanged
    );

    connect(
        guiState, &GuiState::sigSelectedProtocolPluginIidChanged,
        this, &AppMgr::selectedProtocolPluginIidChanged
    ); 

    connect(
        guiState, &GuiState::sigSelectedFilterPluginsIidsChanged,
        this, &AppMgr::selectedFilterPluginsIidsChanged
    );     
}

AppMgr::ListOfPluginInfos AppMgr::getPluginInfos(const QStringList& pluginIids)
{
    ListOfPluginInfos result;
    auto& availableInfos = m_pluginMgr.getAvailablePlugins();

    for (auto& p : pluginIids) {
        auto iter = findPluginInfo(availableInfos, p);
        if (iter == availableInfos.end()) {
            std::cerr << "ERROR: Failed to find plugin " << p.toStdString() << std::endl;
            assert(!"Should not happen");
            continue;
        }

        result.push_back(*iter);
    }
    return result;
}

const QString& AppMgr::getPluginConfigQml(const QString& iid)
{
    static const QString DefaultConfigQml;
    const QString* configQml = &DefaultConfigQml;
    do {
        auto& availableInfos = m_pluginMgr.getAvailablePlugins();
        auto iter = findPluginInfo(availableInfos, iid);
        if (iter == availableInfos.end()) {
            assert(!"Should not happen");
            break;
        }

        auto* pl = m_pluginMgr.loadPlugin(**iter);
        if (pl == nullptr) {
            assert(!"Should not happen");
            break;
        }

        configQml = &(pl->getConfigQmlElem());
    } while (false);

    if (configQml->isEmpty()) {
        configQml = &DefaultConfigQml;
    }

    return *configQml;
}


} // namespace cc_view

} // namespace cc_tools
