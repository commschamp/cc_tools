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

#include "cc_tools/cc_plugin/Plugin.h"

#include <cassert>

namespace cc_tools
{

namespace cc_plugin
{

Plugin::Plugin() = default;
Plugin::~Plugin() noexcept = default;

const QString& Plugin::getIid() const
{
    return getIidImpl();
}

void Plugin::getCurrentConfig(QVariantMap& config)
{
    getCurrentConfigImpl(config);
}

QVariantMap Plugin::getCurrentConfig()
{
    QVariantMap config;
    getCurrentConfig(config);
    return config;
}

void Plugin::reconfigure(const QVariantMap& config)
{
    reconfigureImpl(config);
}

void Plugin::aboutToApply()
{
    aboutToApplyImpl();
}

PluginObjectPtr Plugin::createObject()
{
    auto obj = createObjectImpl();
    assert(obj);
    return obj;
}

void Plugin::releaseObject()
{
    releaseObjectImpl();
}

const QString& Plugin::getToolbarQmlElem() const
{
    return getToolbarQmlElemImpl();
}

const QString& Plugin::getConfigQmlElem() const
{
    return getConfigQmlElemImpl();
}

void Plugin::getCurrentConfigImpl(QVariantMap& config)
{
    static_cast<void>(config);
}

void Plugin::reconfigureImpl(const QVariantMap& config)
{
    static_cast<void>(config);
}

const QString& Plugin::getToolbarQmlElemImpl() const
{
    static const QString Str;
    return Str;
}

const QString& Plugin::getConfigQmlElemImpl() const
{
    static const QString Str;
    return Str;
}

void Plugin::aboutToApplyImpl()
{
    // Do nothing
}

} // namespace cc_plugin

}  // namespace cc_tools


