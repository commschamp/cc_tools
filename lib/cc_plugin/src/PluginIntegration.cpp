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

#include "cc_tools/cc_plugin/PluginIntegration.h"
#include "PluginIntegrationImpl.h"

namespace cc_tools
{

namespace cc_plugin
{

PluginIntegration::~PluginIntegration() noexcept = default;

PluginIntegration& PluginIntegration::instance()
{
    static PluginIntegration obj;
    return obj;
}

PluginIntegration* PluginIntegration::instancePtr()
{
    return &instance();
}

void PluginIntegration::registerIntegrationObject(const QString& iid, QObject& obj)
{
    m_pImpl->registerIntegrationObject(iid, obj);
}

QObject* PluginIntegration::getIntegrationObject(const QString& iid)
{
    return m_pImpl->getIntegrationObject(iid);
}

void PluginIntegration::aboutToUnloadPlugin(const QString& iid)
{
    m_pImpl->aboutToUnloadPlugin(iid);
}


PluginIntegration::PluginIntegration() :
    m_pImpl(std::make_unique<PluginIntegrationImpl>())
{
    connect(
        m_pImpl.get(), &PluginIntegrationImpl::sigNewIntegrationObject,
        this, &PluginIntegration::sigNewIntegrationObject);
}


}  // namespace cc_plugin

}  // namespace cc_tools
