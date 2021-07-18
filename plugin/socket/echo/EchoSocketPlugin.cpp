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

#include "EchoSocketPlugin.h"

#include <memory>
#include <cassert>

#include "EchoSocket.h"

namespace cc_tools
{

namespace cc_plugin
{

namespace socket
{

EchoSocketPlugin::EchoSocketPlugin()
{
}

EchoSocketPlugin::~EchoSocketPlugin() noexcept = default;

const QString& EchoSocketPlugin::getIidImpl() const 
{
    static const QString Iid("cc.EchoSocketPlugin");
    return Iid;
}

cc_tools::cc_plugin::PluginObjectPtr EchoSocketPlugin::createObjectImpl()
{
    return makeEchoSocket();
}

void EchoSocketPlugin::releaseObjectImpl()
{
}

} // namespace socket

}  // namespace cc_plugin

}  // namespace cc_tools


