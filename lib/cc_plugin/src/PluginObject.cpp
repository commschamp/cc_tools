#include "cc_tools/cc_plugin/PluginObject.h"

namespace cc_tools
{

namespace cc_plugin
{

PluginObject::PluginObject(QObject* p) : 
    Base(p)
{
}

PluginObject::~PluginObject() = default;

PluginObject::Type PluginObject::getType() const
{
    return getTypeImpl();
}

} // namespace cc_plugin

} // namespace cc_tools
