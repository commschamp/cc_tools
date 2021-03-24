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

#include <list>

#include <QtNetwork/QTcpSocket>

#include "cc_tools/cc_plugin/Socket.h"


namespace cc_tools
{

namespace cc_plugin
{

namespace socket
{

class TcpClientSocket : public cc_tools::cc_plugin::Socket
{
    Q_OBJECT
    using Base = cc_tools::cc_plugin::Socket;

public:
    typedef unsigned short PortType;

    TcpClientSocket();
    ~TcpClientSocket() noexcept;

    void setHost(const QString& value)
    {
        m_host = value;
    }

    const QString& getHost() const
    {
        return m_host;
    }

    void setPort(PortType value)
    {
        m_port = value;
    }

    PortType getPort() const
    {
        return m_port;
    }


protected:
    virtual bool socketConnectImpl() override;
    virtual void socketDisconnectImpl() override;
    virtual void sendDataImpl(DataInfoPtr dataPtr) override;

private slots:
    void socketDisconnected();
    void readFromSocket();
    void socketErrorOccurred(QAbstractSocket::SocketError err);

private:
    static const PortType DefaultPort = 20000;
    QString m_host;
    PortType m_port = DefaultPort;
    QTcpSocket m_socket;
};

using TcpClientSocketPtr = std::shared_ptr<TcpClientSocket>;

inline
TcpClientSocketPtr makeTcpClientSocket()
{
    return TcpClientSocketPtr(new TcpClientSocket);
}


} // namespace socket

} // namespace cc_plugin

} // namespace cc_tools
