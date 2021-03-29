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

#include "TcpClientSocketPlugin.h"

#include <memory>
#include <cassert>

#include "TcpClientSocket.h"

namespace cc_tools
{

namespace cc_plugin
{

namespace socket
{

TcpClientSocketPlugin::TcpClientSocketPlugin()
{
}

TcpClientSocketPlugin::~TcpClientSocketPlugin() noexcept = default;

cc_tools::cc_plugin::PluginObjectPtr TcpClientSocketPlugin::createObjectImpl()
{
    createSocketIfNeeded();
    return m_socket;
}

const QString& TcpClientSocketPlugin::getToolbarQmlElemImpl() const
{
    static const QString Str("qrc:/tcp_client_socket/qml/CC_TcpClientSocketToolbar.qml");
    return Str;
}

void TcpClientSocketPlugin::createSocketIfNeeded()
{
    if (!m_socket) {
        m_socket = makeTcpClientSocket();
    }
}

} // namespace socket

}  // namespace cc_plugin

}  // namespace cc_tools


