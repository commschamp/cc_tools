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

#include "TcpClientSocketIntegrationObj.h"

#include <memory>

#include <QtCore/QObject>

namespace cc_tools
{

namespace cc_plugin
{

namespace socket
{

TcpClientSocketIntegrationObj::TcpClientSocketIntegrationObj() = default;
TcpClientSocketIntegrationObj::~TcpClientSocketIntegrationObj() noexcept = default;

void TcpClientSocketIntegrationObj::setHost(const QString& value)
{
    if (m_host == value) {
        return;
    }

    m_host = value;
    emit sigHostChanged(m_host);
}

const QString& TcpClientSocketIntegrationObj::getHost() const
{
    return m_host;
}

void TcpClientSocketIntegrationObj::setPort(PortType value)
{
    if (m_port == value) {
        return;
    }

    m_port = value;
    emit sigPortChanged(m_port);
}

TcpClientSocketIntegrationObj::PortType TcpClientSocketIntegrationObj::getPort() const
{
    return m_port;
}

void TcpClientSocketIntegrationObj::setConnected(bool value)
{
    if (m_connected == value) {
        return;
    }

    m_connected = value;
    emit sigConnectedChanged(m_connected);
}

bool TcpClientSocketIntegrationObj::getConnected() const
{
    return m_connected;
}

void TcpClientSocketIntegrationObj::setSettingsDisplayed(bool value)
{
    if (m_settingsDisplayed == value) {
        return;
    }

    m_settingsDisplayed = value;
    emit sigSettingsDisplayedChanged(m_settingsDisplayed);
}

bool TcpClientSocketIntegrationObj::getSettingsDisplayed() const
{
    return m_settingsDisplayed;
}

} // namespace socket

} // namespace cc_plugin

} // namespace cc_tools
