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


#include <QtCore/QObject>
#include <QtCore/QtPlugin>
#include <QtCore/QVariantMap>

#include "cc_tools/cc_plugin/Api.h"
#include "cc_tools/cc_plugin/PluginObject.h"

namespace cc_tools
{

namespace cc_plugin
{

/// @brief Interface class for plugin definition
/// @headerfile cc_tools/cc_plugin/Plugin.h
class CC_PLUGIN_API Plugin : public QObject
{
    Q_OBJECT
public:
    /// @brief Constructor
    Plugin();

    /// @brief Destructor
    virtual ~Plugin() noexcept;

    void getCurrentConfig(QVariantMap& config);
    QVariantMap getCurrentConfig();
    void reconfigure(const QVariantMap& config);

    PluginObjectPtr createObject();

protected:
    virtual void getCurrentConfigImpl(QVariantMap& config);
    virtual void reconfigureImpl(const QVariantMap& config);
    virtual PluginObjectPtr createObjectImpl() = 0;
};

} // namespace cc_plugin

}  // namespace cc_tools

Q_DECLARE_INTERFACE(cc_tools::cc_plugin::Plugin, "cc.Plugin")


