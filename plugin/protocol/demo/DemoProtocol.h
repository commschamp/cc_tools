//
// Copyright 2021 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#pragma once

#include <list>

#include <QtCore/QTimer>

#include "cc_tools/cc_plugin/Protocol.h"

namespace cc_tools
{

namespace cc_plugin
{

namespace protocol
{


class DemoProtocol : public cc_tools::cc_plugin::Protocol
{
    Q_OBJECT

public:
    DemoProtocol();
    ~DemoProtocol() noexcept;

private:
};

inline
cc_tools::cc_plugin::ProtocolPtr makeDemoProtocol()
{
    return cc_tools::cc_plugin::ProtocolPtr(new DemoProtocol());
}

} // namespace protocol

} // namespace cc_plugin

}  // namespace cc_tools


