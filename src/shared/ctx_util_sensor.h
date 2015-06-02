/*
 * motion
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __CONTEXT_UTIL_SENSOR_H__
#define __CONTEXT_UTIL_SENSOR_H__

#include <sensor_internal.h>

namespace ctx { namespace sensor {

	int connect(int *handle, sensor_type_t sensor, unsigned int event, int option, sensor_cb_t cb, void *user_data);
	void disconnect(int *handle, sensor_type_t sensor, unsigned int event);

} }	 /* namespace ctx::sensor */

#endif /* __CONTEXT_UTIL_SENSOR_H__ */

