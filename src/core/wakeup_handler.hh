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

#ifndef __NUGU_WAKEUP_HANDLER_H__
#define __NUGU_WAKEUP_HANDLER_H__

#include <memory>

#include "clientkit/wakeup_interface.hh"

#include "capability_manager.hh"
#include "wakeup_detector.hh"

namespace NuguCore {

using namespace NuguClientKit;

class WakeupHandler : public IWakeupHandler,
                      public IWakeupDetectorListener {
public:
    explicit WakeupHandler(const WakeupModelFile& model_file);
    virtual ~WakeupHandler() = default;

    void setListener(IWakeupListener* listener) override;
    bool startWakeup() override;
    void stopWakeup() override;
    void onWakeupState(WakeupState state, const std::string& id, float noise, float speech) override;
    void changeModel(const WakeupModelFile& model_file) override;
    void setWakeupId(const std::string& id);

private:
    IWakeupListener* listener = nullptr;
    std::unique_ptr<WakeupDetector> wakeup_detector;
    std::string request_wakeup_id;
    int uniq;
};
} // NuguCore

#endif /* __NUGU_WAKEUP_HANDLER_H__ */
