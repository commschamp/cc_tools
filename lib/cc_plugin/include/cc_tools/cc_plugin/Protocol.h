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

/// @brief Main polymorphic interface class for protocols.
/// @details It is used to create selected protocol messages.
/// @headerfile cc_tools/cc_plugin/Protocol.h
class CC_PLUGIN_API Protocol : public PluginObject
{
    using Base = PluginObject;
public:

    /// @brief Constructor
    explicit Protocol(QObject* p = nullptr);

    /// @brief Destructor
    virtual ~Protocol() noexcept;

protected:
    virtual Type getTypeImpl() const override final;
    
private:
};

/// @brief Pointer to @ref Protocol object.
using ProtocolPtr = std::shared_ptr<Protocol>;

} // namespace cc_plugin

}  // namespace cc_tools

