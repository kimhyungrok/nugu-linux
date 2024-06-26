/*
 * Copyright (c) 2019 SK Telecom Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __NUGU_UTILITY_AGENT_H__
#define __NUGU_UTILITY_AGENT_H__

#include "capability/utility_interface.hh"
#include "clientkit/capability.hh"

namespace NuguCapability {

class UtilityAgent final : public Capability,
                           public IUtilityHandler {

public:
    UtilityAgent();
    virtual ~UtilityAgent() = default;

    void initialize() override;
    void deInitialize() override;
    void setCapabilityListener(ICapabilityListener* clistener) override;
    void updateInfoForContext(NJson::Value& ctx) override;
    void parsingDirective(const char* dname, const char* message) override;

private:
    void parsingBlock(const char* message);
    void delayReleasingBlocking(long sleep_time_msec);

    IUtilityListener* utility_listener = nullptr;
    std::unique_ptr<INuguTimer> timer = nullptr;
    std::string ps_id;
};

} // NuguCapability

#endif /* __NUGU_UTILITY_AGENT_H__ */
