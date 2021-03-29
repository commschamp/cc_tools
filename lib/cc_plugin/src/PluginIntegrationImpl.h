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

#include <map>

#include <QtCore/QObject>

namespace cc_tools
{

namespace cc_plugin
{

class PluginIntegrationImpl : public QObject
{
    Q_OBJECT
public:
    PluginIntegrationImpl();
    virtual ~PluginIntegrationImpl() noexcept;

    void registerIntegrationObject(const QString& iid, QObject& obj);
    QObject* getIntegrationObject(const QString& iid);
    void aboutToUnloadPlugin(const QString& iid);

signals:
    void sigNewIntegrationObject(QObject* obj);    

private:

    struct PluginInfo
    {
        QObject* m_obj = nullptr;
    };

    std::map<QString, PluginInfo> m_infos;
};

} // namespace cc_plugin

}  // namespace cc_tools



