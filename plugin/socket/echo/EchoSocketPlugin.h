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

#include "cc_tools/cc_plugin/Plugin.h"
#include "cc_tools/cc_plugin/Socket.h"

namespace cc_tools
{

namespace cc_plugin
{

namespace socket
{

class EchoSocketPlugin final: public cc_tools::cc_plugin::Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cc.EchoSocketPlugin" FILE "echo_socket.json")
    Q_INTERFACES(cc_tools::cc_plugin::Plugin)

public:
    EchoSocketPlugin();
    ~EchoSocketPlugin() noexcept;

protected:
    virtual const QString& getIidImpl() const override;
    virtual cc_tools::cc_plugin::PluginObjectPtr createObjectImpl() override;
    virtual void releaseObjectImpl() override;
};

} // namespace socket

}  // namespace cc_plugin

}  // namespace cc_tools




