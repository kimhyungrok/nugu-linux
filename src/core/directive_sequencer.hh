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

#ifndef __NUGU_DIRECTIVE_SEQUENCER_H__
#define __NUGU_DIRECTIVE_SEQUENCER_H__

#include <deque>
#include <map>
#include <vector>

#include <glib.h>

#include "clientkit/directive_sequencer_interface.hh"

namespace NuguCore {

using namespace NuguClientKit;

class DirectiveSequencer : public IDirectiveSequencer {

public:
    DirectiveSequencer();
    virtual ~DirectiveSequencer();

    void reset();
    void addListener(const std::string& name_space, IDirectiveSequencerListener* listener) override;
    void removeListener(const std::string& name_space, IDirectiveSequencerListener* listener) override;

    bool addPolicy(const std::string& name_space, const std::string& name, BlockingPolicy policy) override;
    BlockingPolicy getPolicy(const std::string& name_space, const std::string& name) override;

    bool cancel(const std::string& dialog_id) override;
    bool complete(NuguDirective* ndir) override;
    bool add(NuguDirective* ndir) override;

    using BlockingPolicyMap = std::map<std::string, std::map<std::string, BlockingPolicy>>;
    using DialogQueueMap = std::map<std::string, std::deque<NuguDirective*>>;
    using MsgidDirectiveMap = std::map<std::string, NuguDirective*>;

private:
    /**
     * ["namespace"] = [
     *   "name1" = BlockingPolicy,
     *   "name2" = BlockingPolicy
     * ]
     */
    BlockingPolicyMap policy_map;

    /**
     * ["namespace"] = IDirectiveSequencerListener*
     */
    std::map<std::string, std::vector<IDirectiveSequencerListener*>> listeners_map;

    /**
     * Lookup table for directive searching when receive an attachment
     * ["message-id"] = NuguDirective*
     */
    MsgidDirectiveMap msgid_directive_map;

    /**
     * Pending directive queue for dialog-id
     *   audio_map["dialog-id-a"] = [
     *     directive-1(block), directive-2(non-block)
     *   ]
     *   audio_map["dialog-id-b"] = [ directive-4(block) ]
     *   visual_map["dialog-id-a"] = [ directive-3(block) ]
     *   visual_map["dialog-id-b"] = []
     */
    DialogQueueMap audio_map;
    DialogQueueMap visual_map;

    /**
     * Scheduled directive lists to handle in next idle time
     */
    std::vector<NuguDirective*> scheduled_list;
    guint idler_src;

    void assignPolicy(NuguDirective* ndir);

    bool preHandleDirective(NuguDirective* ndir);
    void handleDirective(NuguDirective* ndir);
    void cancelDirective(NuguDirective* ndir);

    /* Network manager callback */
    static void onDirective(NuguDirective* ndir, void* userdata);
    static void onAttachment(const char* parent_msg_id, int seq, int is_end,
        const char* media_type, size_t length,
        const void* data, void* userdata);

    /* GMainLoop idle callback */
    static gboolean onNext(gpointer userdata);
};

} // NuguCore

#endif /* __NUGU_DIRECTIVE_SEQUENCER_H__ */
