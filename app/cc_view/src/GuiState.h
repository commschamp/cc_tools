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
public:
    enum DialogType 
    {
        DialogType_None,
        DialogType_PluginSelection,
        DialogType_NumOfValues
    };
    Q_ENUM(DialogType);

    ~GuiState();

    static GuiState& instance();
    static GuiState* instancePtr();

    Q_INVOKABLE void activateDialog(DialogType type);

    CC_MEMBER(QString, DialogQml)

signals:
    void sigDialogQmlChanged(const QString& value);    

private:
    GuiState();    
};

} // namespace cc_view

} // namespace cc_tools
