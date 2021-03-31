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

#include "cc_tools/cc_plugin/Api.h"

namespace cc_tools
{

namespace cc_plugin
{

class PluginIntegrationImpl;
class CC_PLUGIN_API PluginIntegration : public QObject
{
    Q_OBJECT
public:
    /// @brief Destructor
    virtual ~PluginIntegration() noexcept;

    static PluginIntegration& instance();
    static PluginIntegration* instancePtr();

    void registerIntegrationObject(const QString& iid, QObject& obj);
    Q_INVOKABLE QObject* getIntegrationObject(const QString& iid);
    void aboutToUnloadPlugin(const QString& iid);

    Q_INVOKABLE void activateDialog(const QString& rsrc);
    Q_INVOKABLE void closeCurrentDialog();

signals:
    void sigNewIntegrationObject(QObject* obj);
    void sigActivateDialog(const QString& rsrc);     
    void sigCloseCurrentDialog();     

private:
    PluginIntegration();

    std::unique_ptr<PluginIntegrationImpl> m_pImpl;
};

} // namespace cc_plugin

}  // namespace cc_tools



