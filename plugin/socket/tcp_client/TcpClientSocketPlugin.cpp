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
#include <iostream>

#include "cc_tools/cc_plugin/PluginIntegration.h"

#include "TcpClientSocket.h"

namespace cc_tools
{

namespace cc_plugin
{

namespace socket
{

namespace 
{

const QString Iid("cc.TcpClientSocketPlugin");

} // namespace 


TcpClientSocketPlugin::TcpClientSocketPlugin() :
    m_integration(makeTcpClientSocketIntegrationObj())
{
    auto& pluginIntegration = cc_tools::cc_plugin::PluginIntegration::instance();
    pluginIntegration.registerIntegrationObject(Iid, *m_integration);

    connect(
        m_integration.get(), &TcpClientSocketIntegrationObj::sigConnectedChanged,
        this, &TcpClientSocketPlugin::socketConnectReq
    );

    connect(
        m_integration.get(), &TcpClientSocketIntegrationObj::sigSettingsDisplayedChanged,
        this, &TcpClientSocketPlugin::configDialogReq
    );   

    connect(
        m_integration.get(), &TcpClientSocketIntegrationObj::sigHostChanged,
        this, &TcpClientSocketPlugin::hostChanged
    );    

    connect(
        m_integration.get(), &TcpClientSocketIntegrationObj::sigPortChanged,
        this, &TcpClientSocketPlugin::portChanged
    );        
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

void TcpClientSocketPlugin::aboutToApplyImpl()
{
    m_integration->setApplying(true);
}

void TcpClientSocketPlugin::socketConnectReq(bool value)
{
    createSocketIfNeeded();
    if (!value) {
        m_socket->socketDisconnect();
        return;
    }

    if (!m_socket->socketConnect()) {
        if (!m_integration->getConnected()) {
            return;
        }
        
        // TODO: report error
        std::cout << __FUNCTION__ << ": Failed to connect to " << m_socket->getHost().toStdString() << ":" << m_socket->getPort() << std::endl;
        m_integration->setConnected(false);
        return;         
    }
}

void TcpClientSocketPlugin::configDialogReq(bool value)
{
    auto& pluginIntegration = cc_tools::cc_plugin::PluginIntegration::instance();
    if (!value) {
        pluginIntegration.closeCurrentDialog();
        return;
    }

    static const QString Src("qrc:/tcp_client_socket/qml/CC_TcpClientSocketConfigDialog.qml");
    pluginIntegration.activateDialog(Src);
}

void TcpClientSocketPlugin::hostChanged(const QString& value)
{
    if (m_socket) {
        m_socket->setHost(value);
    }
}

void TcpClientSocketPlugin::portChanged(int value)
{
    if (m_socket) {
        m_socket->setPort(static_cast<TcpClientSocket::PortType>(value));
    }
}


void TcpClientSocketPlugin::createSocketIfNeeded()
{
    if (!m_socket) {
        m_socket = makeTcpClientSocket();
        m_socket->setHost(m_integration->getHost());
        m_socket->setPort(m_integration->getPort());

        m_socket->setDisconnectedReportCallback(
            [this]()
            {
                m_integration->setConnected(false);
                // TODO: report socket disconnected
            });
    }
}

} // namespace socket

}  // namespace cc_plugin

}  // namespace cc_tools


