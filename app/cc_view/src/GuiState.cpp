#include "GuiState.h"

#include <cassert>
#include <type_traits>

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
        /* DialogType_PluginSelection */ "qrc:/qml/CC_PluginSelectDialog.qml",
    };
    static const std::size_t MapSize = std::extent<decltype(Map)>::value;
    static_assert(MapSize == DialogType_NumOfValues, "Invalid map");

    auto idx = static_cast<unsigned>(type);
    if (MapSize <= idx) {
        assert(!"Should not happen");
        setDialogQml(EmptyStr);
        return;
    }

    setDialogQml(Map[idx]);
}

GuiState::GuiState()
{
}

} // namespace cc_view

} // namespace cc_tools
