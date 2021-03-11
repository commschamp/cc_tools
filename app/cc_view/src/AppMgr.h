#pragma once

#include <QtCore/QObject>

#include "cc_tools/cc_app/PluginMgr.h"

namespace cc_tools
{

namespace cc_view
{

class AppMgr : public QObject
{
    Q_OBJECT
public:
    static AppMgr& instance();

    cc_tools::cc_app::PluginMgr& pluginMgr()
    {
        return m_pluginMgr;
    }

private:
    AppMgr();

    cc_tools::cc_app::PluginMgr m_pluginMgr;
};

} // namespace cc_view

} // namespace cc_tools
