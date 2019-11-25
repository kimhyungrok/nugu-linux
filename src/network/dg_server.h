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

#ifndef __NETWORK_DEVICE_GATEWAY_SERVER_H__
#define __NETWORK_DEVICE_GATEWAY_SERVER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "dg_types.h"

typedef struct _dg_server DGServer;

DGServer *dg_server_new(const struct dg_server_policy *policy);
void dg_server_free(DGServer *server);

int dg_server_connect_async(DGServer *server);
int dg_server_start_health_check(DGServer *server,
				 const struct dg_health_check_policy *policy);

int dg_server_send_event(DGServer *server, NuguEvent *nev);
int dg_server_send_attachment(DGServer *server, NuguEvent *nev, int is_end,
			      size_t length, unsigned char *data);

#ifdef __cplusplus
}
#endif

#endif