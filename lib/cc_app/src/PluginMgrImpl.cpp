//
// Copyright 2021 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "PluginMgrImpl.h"

#include <cassert>
#include <algorithm>
#include <type_traits>
#include <iostream>

#include <QtCore/QString>
#include <QtCore/QVariantList>
#include <QtCore/QDir>
#include <QtCore/QJsonArray>
#include <QtCore/QVariantList>

#include "cc_tools/cc_plugin/Plugin.h"
#include "cc_tools/cc_plugin/PluginIntegration.h"

namespace cc_tools
{

namespace cc_app
{


namespace
{

const QString PluginsKey("cc_plugins_list");
const QString IidMetaKey("IID");
const QString MetaDataMetaKey("MetaData");
const QString NameMetaKey("name");
const QString DescMetaKey("desc");
const QString TypeMetaKey("type");

void aboutToUnloadPlugin(const QString& iid)
{
    cc_tools::cc_plugin::PluginIntegration::instance().aboutToUnloadPlugin(iid);
}

struct PluginLoaderDeleter
{
    void operator()(QPluginLoader* loader)
    {
        assert(loader != nullptr);
        std::unique_ptr<QPluginLoader> loaderPtr(loader);

        if (!loader->isLoaded()) {
            return;
        }        

        do {
            auto metaData = loader->metaData();
            if (metaData.isEmpty()) {
                break;
            }     

            auto iid = metaData.value(IidMetaKey).toString();
            if (!iid.isEmpty()) {
                break;
            }       

            aboutToUnloadPlugin(iid);
        } while (false);

        loader->unload();
    }
};

cc_tools::cc_plugin::Plugin* getPlugin(QPluginLoader& loader)
{
    auto* inst = loader.instance();
    auto* plugin = qobject_cast<cc_tools::cc_plugin::Plugin*>(loader.instance());

    do {
        if (plugin != nullptr) {
            break;
        }

        if (inst == nullptr) {
            std::cerr << "ERROR: The selected library \"" <<
                loader.fileName().toStdString() << "\" is not a Qt5 plugin: " <<
                loader.errorString().toStdString() << std::endl;
            break;
        }

        std::cerr << "ERROR: The selected library \"" <<
            loader.fileName().toStdString() << "\" is not a CommsChampion plugin!" << std::endl;
    } while (false);
    return plugin;
}

PluginMgrImpl::PluginInfo::Type parseType(const QString& val)
{
    static const QString Values[] = {
        QString(),
        "socket",
        "filter",
        "protocol"
    };

    static_assert(
        std::extent<decltype(Values)>::value == static_cast<std::size_t>(PluginMgrImpl::PluginInfo::Type::NumOfValues),
        "The Values array must be adjusted.");

    auto iter = std::find(std::begin(Values), std::end(Values), val);
    if (iter == std::end(Values)) {
        return PluginMgrImpl::PluginInfo::Type::Invalid;
    }

    return static_cast<PluginMgrImpl::PluginInfo::Type>(std::distance(std::begin(Values), iter));
}


}  // namespace

PluginMgrImpl::PluginMgrImpl() = default;

PluginMgrImpl::~PluginMgrImpl() noexcept
{
    for (auto& pluginInfoPtr : m_plugins) {
        assert(pluginInfoPtr);
        assert(pluginInfoPtr->m_loader);
        if (pluginInfoPtr->m_loader->isLoaded()) {
            aboutToUnloadPlugin(pluginInfoPtr->m_iid);
            pluginInfoPtr->m_loader->unload();
        }
    }
}

void PluginMgrImpl::setPluginsDir(const QString& pluginDir)
{
    m_pluginDir = pluginDir;
}

const PluginMgrImpl::ListOfPluginInfos& PluginMgrImpl::getAvailablePlugins()
{
    if (!m_plugins.empty()) {
        return m_plugins;
    }

    do {
        QDir pluginDir(m_pluginDir);
        auto files =
            pluginDir.entryList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name);

        for (auto& f : files) {
            auto infoPtr = readPluginInfo(pluginDir.filePath(f));
            if (!infoPtr) {
                continue;
            }

            if (infoPtr->getType() == PluginInfo::Type::Invalid) {
                std::cerr << "WARNING: plugin " << f.toStdString() << " doesn't specify its type, use either "
                    "\"socket\", or \"filter\", or \"protocol\"."<< std::endl;
                continue;
            }

            m_plugins.push_back(std::move(infoPtr));
        }
    } while (false);

    return m_plugins;
}

const PluginMgrImpl::ListOfPluginInfos& PluginMgrImpl::getAppliedPlugins() const
{
    return m_appliedPlugins;
}

void PluginMgrImpl::setAppliedPlugins(const ListOfPluginInfos& plugins)
{
    m_appliedPlugins = plugins;
}

PluginMgrImpl::ListOfPluginInfos PluginMgrImpl::loadPluginsFromConfig(
    const QVariantMap& config)
{
    ListOfPluginInfos pluginInfos;
    do {
        auto listVar = config.value(PluginsKey);
        if ((!listVar.isValid()) || (!listVar.canConvert<QVariantList>())) {
            break;
        }

        auto varList = listVar.value<QVariantList>();
        auto& availPlugins = getAvailablePlugins();
        for (auto& iidVar : varList) {
            if ((!iidVar.isValid()) || (!iidVar.canConvert<QString>())) {
                continue;
            }

            auto iid = iidVar.toString();
            auto iter =
                std::find_if(
                    availPlugins.begin(), availPlugins.end(),
                    [&iid](const PluginInfoPtr& i) -> bool
                    {
                        return i->m_iid == iid;
                    });

            if (iter == m_plugins.end()) {
                continue;
            }

            auto pluginInfoPtr = *iter;
            assert(pluginInfoPtr);
            assert(pluginInfoPtr->m_loader);
            auto* pluginPtr = getPlugin(*pluginInfoPtr->m_loader);
            assert(pluginPtr != nullptr);
            if (config.contains(iid)) {
                pluginPtr->reconfigure(config[iid].value<QVariantMap>());
            }

            pluginInfos.push_back(*iter);
        }

    } while (false);

    return pluginInfos;
}

PluginMgrImpl::ListOfPluginInfos PluginMgrImpl::loadPluginsFromConfigFile(
    const QString& filename)
{
    auto config = m_configMgr.loadConfig(filename);
    if (config.isEmpty()) {
        return ListOfPluginInfos();
    }

    return loadPluginsFromConfig(config);
}

bool PluginMgrImpl::savePluginsToConfigFile(
    const ListOfPluginInfos& infos,
    const QString& filename)
{
    auto config = getConfigForPlugins(infos);
    return m_configMgr.saveConfig(filename, config);
}

cc_tools::cc_plugin::Plugin* PluginMgrImpl::loadPlugin(const PluginInfo& info)
{
    return getPlugin(*info.m_loader);
}

bool PluginMgrImpl::hasAppliedPlugins() const
{
    return !m_appliedPlugins.empty();
}

bool PluginMgrImpl::needsReload(const ListOfPluginInfos& infos) const
{
    assert(!infos.empty());
    return (!m_appliedPlugins.empty()) &&
           (m_appliedPlugins != infos);
}

bool PluginMgrImpl::isProtocolChanging(const ListOfPluginInfos& infos) const
{
    auto findProtocolFunc =
        [](const ListOfPluginInfos& l) -> PluginInfoPtr
        {
            auto iter =
                std::find_if(l.rbegin(), l.rend(),
                    [](const PluginInfoPtr& ptr) -> bool
                    {
                        return ptr->getType() == PluginMgr::PluginInfo::Type::Protocol;
                    });

            if (iter == l.rend()) {
                return PluginInfoPtr();
            }

            return *iter;
        };

    auto newProtocol = findProtocolFunc(infos);
    auto appliedProtocol = findProtocolFunc(m_appliedPlugins);
    return newProtocol != appliedProtocol;
}

void PluginMgrImpl::unloadNotApplied()
{
    for (auto& p : m_plugins) {
        auto& iid = p->getIid();
        bool unload = 
            std::none_of(
                m_appliedPlugins.begin(), m_appliedPlugins.end(),
                [&iid](auto& appliedInfo) 
                {
                    return iid == appliedInfo->getIid();
                });

        if (unload) {
            aboutToUnloadPlugin(iid);
            p->m_loader->unload();            
        }
    }
}

// bool PluginMgrImpl::unloadAppliedPlugin(const PluginInfo& info)
// {
//     auto iter =
//         std::find_if(
//             m_appliedPlugins.begin(), m_appliedPlugins.end(),
//             [&info](const PluginInfoPtr& ptr) -> bool
//             {
//                 return ptr.get() == &info;
//             });

//     if (iter == m_appliedPlugins.end()) {
//         return false;
//     }

//     auto pluginInfoPtr = *iter;
//     m_appliedPlugins.erase(iter);

//     assert(pluginInfoPtr);
//     assert(pluginInfoPtr->m_loader);
//     assert (pluginInfoPtr->m_loader->isLoaded());
//     aboutToUnloadPlugin(pluginInfoPtr->m_iid);
//     pluginInfoPtr->m_loader->unload();
//     return true;
// }

QVariantMap PluginMgrImpl::getConfigForPlugins(
    const ListOfPluginInfos& infos)
{
    QVariantMap config;
    QVariantList pluginsList;
    for (auto& pluginInfoPtr : infos) {
        assert(pluginInfoPtr);
        assert(!pluginInfoPtr->m_iid.isEmpty());
        pluginsList.append(QVariant::fromValue(pluginInfoPtr->m_iid));

        assert(pluginInfoPtr->m_loader);
        auto* pluginPtr = getPlugin(*pluginInfoPtr->m_loader);
        assert(pluginPtr != nullptr);
        QVariantMap pluginConfig;
        pluginPtr->getCurrentConfig(pluginConfig);
        if (!pluginConfig.isEmpty()) {
            config[pluginPtr->getIid()] = std::move(pluginConfig);
        }
    }

    config.insert(PluginsKey, QVariant::fromValue(pluginsList));
    return config;
}

const QString& PluginMgrImpl::getLastFile() const
{
    return m_configMgr.getLastFile();
}

const QString& PluginMgrImpl::getFilesFilter()
{
    return ConfigMgr::getFilesFilter();
}

PluginMgrImpl::PluginInfoPtr PluginMgrImpl::readPluginInfo(const QString& filename)
{
    PluginInfoPtr ptr;

    do {
        PluginLoaderPtr loader(new QPluginLoader(filename));
        assert(!loader->isLoaded());
        auto metaData = loader->metaData();
        assert(!loader->isLoaded());

        if (metaData.isEmpty()) {
            break;
        }

        auto iidJsonVal = metaData.value(IidMetaKey);
        if (!iidJsonVal.isString()) {
            break;
        }

        ptr.reset(new PluginInfo());
        ptr->m_iid = iidJsonVal.toString();
        ptr->m_loader = std::move(loader);

        auto extraMeta = metaData.value(MetaDataMetaKey);
        if (!extraMeta.isObject()) {
            ptr->m_name = ptr->m_iid;
            break;
        }

        auto extraMetaObj = extraMeta.toObject();
        auto nameJsonVal = extraMetaObj.value(NameMetaKey);
        if (!nameJsonVal.isString()) {
            ptr->m_name = ptr->m_iid;
        }

        auto nameStr = nameJsonVal.toString();
        if (nameStr.isEmpty()) {
            ptr->m_name = ptr->m_iid;
        }
        else {
            ptr->m_name = nameStr;
        }

        auto descJsonVal = extraMetaObj.value(DescMetaKey);
        if (descJsonVal.isString()) {
            ptr->m_desc = descJsonVal.toString();
        }
        else if (descJsonVal.isArray()) {
            auto descVarList = descJsonVal.toArray().toVariantList();
            for (auto& descPartVar : descVarList) {
                if ((descPartVar.isValid()) &&
                    (descPartVar.canConvert<QString>())) {
                    ptr->m_desc.append(descPartVar.toString());
                }
            }
        }

        auto typeJsonVal = extraMetaObj.value(TypeMetaKey);
        ptr->m_type = parseType(typeJsonVal.toString().toLower());

    } while (false);
    return ptr;
}

} // namespace cc_app

} // namespace cc_tools


