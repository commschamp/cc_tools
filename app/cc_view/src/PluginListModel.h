#pragma once

#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtCore/QAbstractListModel>

#include "cc_tools/cc_plugin/PluginObject.h"
#include "cc_tools/cc_app/PluginMgr.h"

#include "common_defs.h"

namespace cc_tools
{

namespace cc_view
{

class PluginListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int pluginType READ getPluginType WRITE setPluginType NOTIFY sigPluginTypeChanged)

    using Base = QAbstractListModel;
public:
    PluginListModel();
    virtual ~PluginListModel();

    using PluginObjectType = cc_tools::cc_plugin::PluginObject::Type;
    using PluginMgr = cc_tools::cc_app::PluginMgr;
    using ListOfPluginInfos = PluginMgr::ListOfPluginInfos;

    enum Type {
        Type_Invalid = static_cast<int>(PluginObjectType::Invalid),
        Type_Socket = static_cast<int>(PluginObjectType::Socket),
        Type_Filter = static_cast<int>(PluginObjectType::Filter),
        Type_Protocol = static_cast<int>(PluginObjectType::Protocol),
    };
    Q_ENUM(Type);

    Q_INVOKABLE QString getIidOf(int idx) const;
    Q_INVOKABLE QString getNameOf(int idx) const;
    Q_INVOKABLE QString getDescriptionOf(int idx) const;

    CC_MEMBER(int, PluginType, =Type_Invalid)

signals:
    void sigPluginTypeChanged(int value);

protected:
    virtual int rowCount(const QModelIndex &parent) const override final;    
    virtual QVariant data(const QModelIndex &index, int role) const override final;
    virtual QHash<int, QByteArray> roleNames() const override final;

private slots:
    void pluginTypeChanged(int value);    

private:
    enum Role {
        Role_Iid = Qt::UserRole,
        Role_Name,
        Role_Desc,
        NumOfRoles
    };

    ListOfPluginInfos m_availablePlugins;    
};

} // namespace cc_view


} // namespace cc_tools
