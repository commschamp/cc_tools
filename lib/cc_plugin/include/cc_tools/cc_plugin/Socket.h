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

#include <cstdint>
#include <cstddef>
#include <vector>
#include <functional>

#include <QtCore/QString>

#include "cc_tools/cc_plugin/Api.h"
#include "cc_tools/cc_plugin/DataInfo.h"
#include "cc_tools/cc_plugin/PluginObject.h"

namespace cc_tools
{

namespace cc_plugin
{

/// @brief Main polymorphic interface class for sockets.
/// @details It is used to drive low level I/O operations.
/// @headerfile cc_tools/cc_plugin/Socket.h
class CC_PLUGIN_API Socket : public PluginObject
{
    using Base = PluginObject;
public:

    /// @brief Constructor
    explicit Socket(QObject* p = nullptr);

    /// @brief Destructor
    virtual ~Socket() noexcept;

    /// @brief Start socket's operation
    /// @details Prior to being started, the socket is not allowed to generate
    ///     any events. The function invokes virtual startImpl() which can
    ///     be overriden by the derived class.
    /// @return true in case the socket's operation has been successfully started,
    ///     false otherwise.
    bool start();

    /// @brief Stop socket's operation.
    /// @details After being stopped, the socket is not allowed to generate any
    ///     events. The function invokes virtual stopImpl(), which can be
    ///     overriden by the derived class
    void stop();

    /// @brief Report whether the socket has been properly started.
    bool isRunning() const;

    /// @brief Connect socket
    /// @details After the socket has been successfully started (see start()), the driving
    ///     application invokes this function as well. It can be used to open
    ///     the I/O device and/or connect to remote host (in case of network socket).
    ///     The function invokes virtual socketConnectImpl(), which can be overridden by
    ///     the derived class.
    /// @return true in case the operation is successful, false otherwise.
    bool socketConnect();

    /// @brief Disconnect socket
    /// @details This function is used to close the opened I/O device and/or
    ///     to disconnect from the remote host (in case of network socket).
    ///     The function invokes virtual socketDisconnectImpl(), which can be overridden by
    ///     the derived class.
    void socketDisconnect();

    /// @brief Check socket connected
    bool isSocketConnected() const;

    /// @brief Request socket to send data
    /// @details Invokes the sendDataImpl(), which must be implemented in
    ///     the derived class.
    /// @param[in] Information about outging data
    void sendData(DataInfoPtr dataPtr);

    /// @brief Callback to report incoming data.
    using DataReceivedCallback = std::function<void (DataInfoPtr)>;

    /// @brief Set callback to report incoming data
    /// @details The callback must have the same signature as @ref DataReceivedCallback.
    template <typename TFunc>
    void setDataReceivedCallback(TFunc&& func)
    {
        m_dataReceivedCallback = std::forward<TFunc>(func);
    }

    /// @brief Callback to report errors
    using ErrorReportCallback = std::function<void (const QString& msg)>;

    /// @brief Set callback to report errors
    /// @details The callback must have the same signature as @ref ErrorReportCallback
    template <typename TFunc>
    void setErrorReportCallback(TFunc&& func)
    {
        m_errorReportCallback = std::forward<TFunc>(func);
    }

    /// @brief Callback to report socket disconnection
    using DisconnectedReportCallback = std::function <void ()>;

    /// @brief Set callback to report socket disconnection
    /// @details The callback must have the same signature as @ref DisconnectedReportCallback.
    template <typename TFunc>
    void setDisconnectedReportCallback(TFunc&& func)
    {
        m_disconnectedReportCallback = std::forward<TFunc>(func);
    }

protected:
    virtual Type getTypeImpl() const override final;

    /// @brief Polymorphic start functionality implementation.
    /// @details Invoked by start() and default implementation does nothing.
    ///     It can be overrided by the derived class.
    /// @return true
    virtual bool startImpl();

    /// @brief Polymorphic stop functionality implementation.
    /// @details Invoked by stop() and default implementation does nothing.
    ///     It can be overridden by the derived class.
    virtual void stopImpl();

    /// @brief Polymorphic socket connection functionality implementation.
    /// @details Invoked by socketConnect() and default implementation does nothing.
    ///     It can be overridden by the derived class.
    /// @return true
    virtual bool socketConnectImpl();

    /// @brief Polymorphic socket disconnection functionality implementation.
    /// @details Invoked by socketDisconnect() and default implementation does nothing.
    ///     It can be overridden by the derived class.
    virtual void socketDisconnectImpl();

    /// @brief Polymorphic data send functionality implementation.
    /// @details Invoked by sendData(). It must be overridden and implemented in
    ///     the derived class.
    virtual void sendDataImpl(DataInfoPtr dataPtr) = 0;

    /// @brief Report new data has been received.
    /// @details This function needs to be invoked by the derived class when
    ///     new data has been received from the I/O link. This function
    ///     will invoke callback set by setDataReceivedCallback().
    /// @param[in] New data information.
    void reportDataReceived(DataInfoPtr dataPtr);

    /// @brief Report I/O operation error.
    /// @details This function is expected to be invoked by the derived class,
    ///     when I/O error is detected. This function will invoke
    ///     callback set by setErrorReportCallback().
    /// @param[in] Error message.
    void reportError(const QString& msg);

    /// @brief Report socket disconnection.
    /// @details Sometimes socket may get unexpectedly disconnected. When such
    ///     situation is discovered, it should be reported to the running
    ////    application. This function is expected to be invoked by the
    ///     derived class and it will invoke callback set by setDisconnectedReportCallback().
    void reportDisconnected();

private:
    DataReceivedCallback m_dataReceivedCallback;
    ErrorReportCallback m_errorReportCallback;
    DisconnectedReportCallback m_disconnectedReportCallback;

    bool m_running = false;
    bool m_connected = false;
};

/// @brief Pointer to @ref Socket object.
using SocketPtr = std::shared_ptr<Socket>;

} // namespace cc_plugin

}  // namespace cc_tools

