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

#include "PluginIntegrationImpl.h"

namespace cc_tools
{

namespace cc_plugin
{

PluginIntegrationImpl::PluginIntegrationImpl() = default;

PluginIntegrationImpl::~PluginIntegrationImpl() noexcept = default;

void PluginIntegrationImpl::registerIntegrationObject(const QString& iid, QObject& obj)
{
    assert(getIntegrationObject(iid) == nullptr);
    m_infos[iid].m_obj = &obj;
    emit sigNewIntegrationObject(&obj);
}

QObject* PluginIntegrationImpl::getIntegrationObject(const QString& iid)
{
    auto iter = m_infos.find(iid);
    if (iter == m_infos.end()) {
        return nullptr;
    }

    return iter->second.m_obj;
}

void PluginIntegrationImpl::aboutToUnloadPlugin(const QString& iid)
{
    auto iter = m_infos.find(iid);
    if (iter != m_infos.end()) {
        m_infos.erase(iter);
    }
}


}  // namespace cc_plugin

}  // namespace cc_tools
