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


#pragma once

#include <memory>
#include <list>
#include <array>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariantMap>
#include <QtCore/QPluginLoader>

#include "cc_tools/cc_plugin/Plugin.h"
#include "cc_tools/cc_app/PluginMgr.h"
#include "cc_tools/cc_app/ConfigMgr.h"


namespace cc_tools
{

namespace cc_app
{

class PluginMgrImpl
{
public:

    typedef PluginMgr::PluginLoaderPtr PluginLoaderPtr;
    typedef PluginMgr::PluginInfo PluginInfo;
    typedef PluginMgr::PluginInfoPtr PluginInfoPtr;
    typedef PluginMgr::ListOfPluginInfos ListOfPluginInfos;

    PluginMgrImpl();
    ~PluginMgrImpl() noexcept;

    void setPluginsDir(const QString& pluginDir);
    const ListOfPluginInfos& getAvailablePlugins();
    const ListOfPluginInfos& getAppliedPlugins() const;
    void setAppliedPlugins(const ListOfPluginInfos& plugins);
    ListOfPluginInfos loadPluginsFromConfig(const QVariantMap& config);
    ListOfPluginInfos loadPluginsFromConfigFile(const QString& filename);
    bool savePluginsToConfigFile(const ListOfPluginInfos& infos, const QString& filename);
    cc_tools::cc_plugin::Plugin* loadPlugin(const PluginInfo& info);
    bool hasAppliedPlugins() const;
    bool needsReload(const ListOfPluginInfos& infos) const;
    bool isProtocolChanging(const ListOfPluginInfos& infos) const;
    void unloadNotApplied();
    // bool unloadAppliedPlugin(const PluginInfo& info);
    static QVariantMap getConfigForPlugins(const ListOfPluginInfos& infos);
    const QString& getLastFile() const;
    static const QString& getFilesFilter();

private:
    typedef std::list<PluginLoaderPtr> PluginLoadersList;

    PluginInfoPtr readPluginInfo(const QString& filename);

    QString m_pluginDir;
    ListOfPluginInfos m_plugins;
    ListOfPluginInfos m_appliedPlugins;
    ConfigMgr m_configMgr;
};

} // namespace cc_app

} // namespace cc_tools


