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

void GuiState::activateDialog(DialogType type)
{
    static const QString Map[] = {
        /* DialogType_None */ EmptyStr,
        /* DialogType_PluginsSelection */ "qrc:/qml/CC_PluginsSelectDialog.qml",
        /* DialogType_PluginsReloadConfirmation */ "qrc:/qml/CC_PluginsReloadConfirmDialog.qml",
        /* DialogType_PluginsReloadError */ "qrc:/qml/CC_PluginsReloadErrorDialog.qml",
    };
    static const std::size_t MapSize = std::extent<decltype(Map)>::value;
    static_assert(MapSize == DialogType_NumOfValues, "Invalid map");

    auto idx = static_cast<unsigned>(type);
    if (MapSize <= idx) {
        assert(!"Should not happen");
        return;
    }

    activateDialogByResource(Map[idx]);
}

void GuiState::activateDialogByResource(const QString& rsrc)
{
    std::cout << "!!!! Activating dialog: " << rsrc.toStdString() << std::endl;
    m_dialogsQueue.append(rsrc);
    std::cout << "!!!! Queue: " << m_dialogsQueue.size() << std::endl;
    if (m_dialogsQueue.size() == 1) {
        std::cout << "!!!! Displaying!!!!" << std::endl;
        displayNextDialog();
    }
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
