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

#include <QtCore/QObject>

namespace cc_tools
{

namespace cc_plugin
{

namespace socket
{

class TcpClientSocketIntegrationObj : public QObject
{
    Q_OBJECT
    using Base = QObject;

    Q_PROPERTY(QString host READ getHost WRITE setHost NOTIFY sigHostChanged);
    Q_PROPERTY(unsigned short port READ getPort WRITE setPort NOTIFY sigPortChanged);
    Q_PROPERTY(bool connected READ getConnected WRITE setConnected NOTIFY sigConnectedChanged);
    Q_PROPERTY(bool settingsDisplayed READ getSettingsDisplayed WRITE setSettingsDisplayed NOTIFY sigSettingsDisplayedChanged);
    Q_PROPERTY(bool applying READ getApplying WRITE setApplying NOTIFY sigApplyingChanged);

public:
    typedef unsigned short PortType;

    TcpClientSocketIntegrationObj();
    ~TcpClientSocketIntegrationObj() noexcept;

    void setHost(const QString& value);
    const QString& getHost() const;

    void setPort(PortType value);
    PortType getPort() const;

    void setConnected(bool value);
    bool getConnected() const;

    void setSettingsDisplayed(bool value);
    bool getSettingsDisplayed() const;

    void setApplying(bool value);
    bool getApplying() const;

signals:
    void sigHostChanged(const QString& value);
    void sigPortChanged(PortType value);  
    void sigConnectedChanged(bool value); 
    void sigSettingsDisplayedChanged(bool value); 
    void sigApplyingChanged(bool value);

private:
    QString m_host;
    PortType m_port = 0;
    bool m_connected = false;
    bool m_settingsDisplayed = false;
    bool m_applying = false;
};

using TcpClientSocketIntegrationObjPtr = std::unique_ptr<TcpClientSocketIntegrationObj>;

inline
TcpClientSocketIntegrationObjPtr makeTcpClientSocketIntegrationObj()
{
    return TcpClientSocketIntegrationObjPtr(new TcpClientSocketIntegrationObj);
}


} // namespace socket

} // namespace cc_plugin

} // namespace cc_tools
