//
// Copyright 2016 - 2020 (C). Alex Robenko. All rights reserved.
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

#include "cc_tools/cc_plugin/Socket.h"

namespace cc_tools
{

namespace cc_plugin
{

Socket::Socket(QObject* p) : 
    Base(p)
{
}

Socket::~Socket() noexcept = default;

bool Socket::start()
{
    m_running = startImpl();
    return m_running;
}

void Socket::stop()
{
    if (m_connected) {
        socketDisconnect();
        reportDisconnected();
    }
    m_running = false;
    stopImpl();
}

bool Socket::isRunning() const
{
    return m_running;
}

bool Socket::socketConnect()
{
    m_connected = socketConnectImpl();
    return m_connected;
}

void Socket::socketDisconnect()
{
    socketDisconnectImpl();
    m_connected = false;
}

bool Socket::isSocketConnected() const
{
    return m_connected;
}

void Socket::sendData(DataInfoPtr dataPtr)
{
    if (!isSocketConnected()) {
        return;
    }

    if (dataPtr->m_timestamp == DataInfo::Timestamp()) {
        dataPtr->m_timestamp = DataInfo::TimestampClock::now();
    }

    sendDataImpl(std::move(dataPtr));
}

bool Socket::startImpl()
{
    return true;
}

void Socket::stopImpl()
{
}

bool Socket::socketConnectImpl()
{
    return true;
}

void Socket::socketDisconnectImpl()
{
}

void Socket::reportDataReceived(DataInfoPtr dataPtr)
{
    if ((!m_running) || (!m_dataReceivedCallback)) {
        return;
    }

    if (dataPtr->m_timestamp == DataInfo::Timestamp()) {
        dataPtr->m_timestamp = DataInfo::TimestampClock::now();
    }

    m_dataReceivedCallback(std::move(dataPtr));
}

void Socket::reportError(const QString& msg)
{
    if (m_running && m_errorReportCallback) {
        m_errorReportCallback(msg);
    }
}

void Socket::reportDisconnected()
{
    m_connected = false;
    if (m_running && m_disconnectedReportCallback) {
        m_disconnectedReportCallback();
    }
}

}  // namespace cc_plugin

}  // namespace cc_tools
