#include "GuiState.h"

#include <cassert>
#include <type_traits>
#include <iostream>

namespace cc_tools
{

namespace cc_view
{

namespace 
{

const QString EmptyStr;

} // namespace 


GuiState::~GuiState() = default;

GuiState& GuiState::instance()
{
    static GuiState state;
    return state;
}

GuiState* GuiState::instancePtr()
{
    return &(instance());
}

void GuiState::activateDialog(DialogType type, bool pushFront)
{
    static const QString Map[] = {
        /* DialogType_None */ EmptyStr,
        /* DialogType_PluginsSelection */ "qrc:/qml/CC_PluginsSelectDialog.qml",
        /* DialogType_PluginsReloadConfirmation */ "qrc:/qml/CC_PluginsReloadConfirmDialog.qml",
        /* DialogType_PluginsReloadError */ "qrc:/qml/CC_PluginsReloadErrorDialog.qml",
        /* DialogType_PluginsConfigSave */ "qrc:/qml/CC_PluginsConfigSaveDialog.qml",
        /* DialogType_PluginsConfigSaveFailed */ "qrc:/qml/CC_PluginsConfigSaveFailedDialog.qml",
        /* DialogType_PluginsConfigLoad */ "qrc:/qml/CC_PluginsConfigLoadDialog.qml",
        /* DialogType_PluginsConfigSaveFailed */ "qrc:/qml/CC_PluginsConfigLoadFailedDialog.qml",
    };
    static const std::size_t MapSize = std::extent<decltype(Map)>::value;
    static_assert(MapSize == DialogType_NumOfValues, "Invalid map");

    auto idx = static_cast<unsigned>(type);
    if (MapSize <= idx) {
        assert(!"Should not happen");
        return;
    }

    activateDialogByResource(Map[idx], pushFront);
}

void GuiState::activateDialogAppend(DialogType type)
{
    activateDialog(type, false);
}

void GuiState::activateDialogPrepend(DialogType type)
{
    activateDialog(type, true);
}

void GuiState::activateDialogByResource(const QString& rsrc, bool pushFront)
{
    if (pushFront) {
        m_dialogsQueue.prepend(rsrc);
        displayNextDialog();
        return;
    }

    m_dialogsQueue.append(rsrc);
    if (m_dialogsQueue.size() == 1) {
        displayNextDialog();
    }
}

void GuiState::activateDialogByResourceAppend(const QString& rsrc)
{
    activateDialogByResource(rsrc, false);
}

void GuiState::activateDialogByResourcePrepend(const QString& rsrc)
{
    activateDialogByResource(rsrc, true);
}

void GuiState::closeCurrentDialog()
{
    assert(!m_dialogsQueue.isEmpty());
    m_dialogsQueue.pop_front();
    if (m_dialogsQueue.isEmpty()) {
        setDialogQml(QString());
        return;
    }

    setDialogQml(m_dialogsQueue.front());
}

GuiState::GuiState()
{
}

void GuiState::displayNextDialog()
{
    setDialogQml(m_dialogsQueue.front());
}

} // namespace cc_view

} // namespace cc_tools
