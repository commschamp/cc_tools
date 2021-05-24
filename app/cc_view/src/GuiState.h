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
    Q_PROPERTY(QString socketPluginIid READ getSocketPluginIid WRITE setSocketPluginIid NOTIFY sigSocketPluginIidChanged)
    Q_PROPERTY(QString selectedSocketPluginIid READ getSelectedSocketPluginIid WRITE setSelectedSocketPluginIid NOTIFY sigSelectedSocketPluginIidChanged)
    Q_PROPERTY(QString protocolPluginIid READ getProtocolPluginIid WRITE setProtocolPluginIid NOTIFY sigProtocolPluginIidChanged)
    Q_PROPERTY(QString selectedProtocolPluginIid READ getSelectedProtocolPluginIid WRITE setSelectedProtocolPluginIid NOTIFY sigSelectedProtocolPluginIidChanged)
    Q_PROPERTY(QStringList filterPluginsIids READ getFilterPluginsIids WRITE setFilterPluginsIids NOTIFY sigFilterPluginsIidsChanged)
    Q_PROPERTY(QStringList selectedFilterPluginsIids READ getSelectedFilterPluginsIids WRITE setSelectedFilterPluginsIids NOTIFY sigSelectedFilterPluginsIidsChanged)
    Q_PROPERTY(QStringList extraToolbarElements READ getExtraToolbarElements WRITE setExtraToolbarElements NOTIFY sigExtraToolbarElementsChanged)
    
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

    CC_MEMBER(QString, DialogQml)
    CC_MEMBER(QString, SocketPluginIid)
    CC_MEMBER(QString, SelectedSocketPluginIid)
    CC_MEMBER(QString, ProtocolPluginIid)
    CC_MEMBER(QString, SelectedProtocolPluginIid)
    CC_MEMBER(QStringList, FilterPluginsIids)
    CC_MEMBER(QStringList, SelectedFilterPluginsIids)
    CC_MEMBER(QStringList, ExtraToolbarElements)

public slots:
    Q_INVOKABLE void activateDialog(DialogType type);
    Q_INVOKABLE void activateDialogByResource(const QString& rsrc);
    Q_INVOKABLE void closeCurrentDialog();

signals:
    void sigDialogQmlChanged(const QString& value);    
    void sigSocketPluginIidChanged(const QString& value);
    void sigSelectedSocketPluginIidChanged(const QString& value);
    void sigProtocolPluginIidChanged(const QString& value);
    void sigSelectedProtocolPluginIidChanged(const QString& value);
    void sigFilterPluginsIidsChanged(const QStringList& value);
    void sigSelectedFilterPluginsIidsChanged(const QStringList& value);
    void sigExtraToolbarElementsChanged(const QStringList& value);

private:
    GuiState(); 

    void displayNextDialog();   

    QStringList m_dialogsQueue;
};

} // namespace cc_view

} // namespace cc_tools
