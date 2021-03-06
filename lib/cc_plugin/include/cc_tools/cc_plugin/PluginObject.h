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
#include <QtCore/QString>

#include "cc_tools/cc_plugin/Api.h"

namespace cc_tools
{

namespace cc_plugin
{

class CC_PLUGIN_API PluginObject : public QObject
{
    using Base = QObject;
    
public:
    enum class Type
    {
        Invalid,
        Socket,
        Filter,
        Protocol,
        NumOfValues
    };

    explicit PluginObject(QObject* p = nullptr);

    virtual ~PluginObject() noexcept;

    Type getType() const;

protected:
    virtual Type getTypeImpl() const = 0;
};

using PluginObjectPtr = std::shared_ptr<PluginObject>;

} // namespace cc_plugin

}  // namespace cc_tools

