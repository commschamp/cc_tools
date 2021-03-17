#include "PluginListModel.h"

#include <algorithm>
#include <map>
#include <cassert>
#include <iostream>

#include "AppMgr.h"

namespace cc_tools
{

namespace cc_view
{

PluginListModel::PluginListModel()
{
    connect(
        this, &PluginListModel::sigPluginTypeChanged,
        this, &PluginListModel::pluginTypeChanged);
}

PluginListModel::~PluginListModel() = default;

QString PluginListModel::getIidOf(int idx) const
{
    if (m_availablePlugins.size() <= idx) {
        assert(!"Should not happen");
        return QString();
    }

    return m_availablePlugins[idx]->getIid();
}

QString PluginListModel::getNameOf(int idx) const
{
    if (m_availablePlugins.size() <= idx) {
        assert(!"Should not happen");
        return QString();
    }

    return m_availablePlugins[idx]->getName();
}

QString PluginListModel::getDescriptionOf(int idx) const
{
    if (m_availablePlugins.size() <= idx) {
        assert(!"Should not happen");
        return QString();
    }

    return m_availablePlugins[idx]->getDescription();
}


int PluginListModel::rowCount(const QModelIndex &parent) const
{
    static_cast<void>(parent);
    return m_availablePlugins.size();
}

QVariant PluginListModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    do {
        auto idx = index.row();
        if (m_availablePlugins.size() <= idx) {
            break;
        }

        using PluginInfo = PluginMgr::PluginInfo;
        using GetFunc = const QString& (PluginInfo::*)() const;
        static const std::map<int, GetFunc> Map = {
            std::make_pair(Qt::ToolTipRole, &PluginInfo::getDescription),
            std::make_pair(Role_Iid, &PluginInfo::getIid),
            std::make_pair(Role_Name, &PluginInfo::getName),
            std::make_pair(Role_Desc, &PluginInfo::getDescription),
        };

        auto iter = Map.find(role);
        if (iter == Map.end()) {
            std::cerr << "ERROR: PluginListModel: Bad request of the role: " << role << std::endl;
            break;
        }

        auto& infoPtr = m_availablePlugins[idx];
        assert(infoPtr);
        auto func = iter->second;
        result = (infoPtr.get()->*func)();
    } while (false);
    return result;
}

QHash<int, QByteArray> PluginListModel::roleNames() const
{
    auto names = Base::roleNames();
    names[Role_Iid] = "iid";
    names[Role_Name] = "name";
    names[Role_Desc] = "desc";
    return names;
}

void PluginListModel::pluginTypeChanged(int value)
{
    static_cast<void>(value);
    beginResetModel();
    auto& pluginMgr = AppMgr::instance().pluginMgr();

    m_availablePlugins = pluginMgr.getAvailablePlugins();
    m_availablePlugins.erase(
        std::remove_if(
            m_availablePlugins.begin(), m_availablePlugins.end(),
            [value](auto& infoPtr)
            {
                return infoPtr->getType() != static_cast<PluginObjectType>(value);
            }),
        m_availablePlugins.end());

    endResetModel();
}

} // namespace cc_view

} // namespace cc_tools
