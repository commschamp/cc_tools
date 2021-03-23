#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>

#include "common_defs.h"

namespace cc_tools
{

namespace cc_view
{

class GuiState : public QObject
{
    Q_OBJECT    

    Q_PROPERTY(QString dialogQml READ getDialogQml WRITE setDialogQml NOTIFY sigDialogQmlChanged)
    Q_PROPERTY(QString socketPluginName READ getSocketPluginName WRITE setSocketPluginName NOTIFY sigSocketPluginNameChanged)
    Q_PROPERTY(QString socketPluginIid READ getSocketPluginIid WRITE setSocketPluginIid NOTIFY sigSocketPluginIidChanged)
    Q_PROPERTY(QString protocolPluginName READ getProtocolPluginName WRITE setProtocolPluginName NOTIFY sigProtocolPluginNameChanged)
    Q_PROPERTY(QString protocolPluginIid READ getProtocolPluginIid WRITE setProtocolPluginIid NOTIFY sigProtocolPluginIidChanged)
    Q_PROPERTY(QStringList filterPluginsIids READ getFilterPluginsIids WRITE setFilterPluginsIids NOTIFY sigFilterPluginsIidsChanged)
    
public:
    enum DialogType 
    {
        DialogType_None,
        DialogType_PluginsSelection,
        DialogType_PluginsReloadConfirmation,
        DialogType_PluginsReloadError,
        DialogType_NumOfValues
    };
    Q_ENUM(DialogType);

    ~GuiState();

    static GuiState& instance();
    static GuiState* instancePtr();

    Q_INVOKABLE void activateDialog(DialogType type);

    CC_MEMBER(QString, DialogQml)
    CC_MEMBER(QString, SocketPluginName)
    CC_MEMBER(QString, SocketPluginIid)
    CC_MEMBER(QString, ProtocolPluginName)
    CC_MEMBER(QString, ProtocolPluginIid)
    CC_MEMBER(QStringList, FilterPluginsIids)

signals:
    void sigDialogQmlChanged(const QString& value);    
    void sigSocketPluginNameChanged(const QString& value);
    void sigSocketPluginIidChanged(const QString& value);
    void sigProtocolPluginNameChanged(const QString& value);
    void sigProtocolPluginIidChanged(const QString& value);
    void sigFilterPluginsIidsChanged(const QStringList& value);

private:
    GuiState();    
};

} // namespace cc_view

} // namespace cc_tools
