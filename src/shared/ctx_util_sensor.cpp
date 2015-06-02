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

#include <ctx_error.h>
#include "ctx_types_private.h"
#include "ctx_util_sensor.h"

#define NUM_CONNECT_TRIAL 2

int ctx::sensor::connect(int *handle, sensor_type_t sensor, unsigned int event, int option, sensor_cb_t cb, void *user_data)
{
	sensor_t sen = sensord_get_sensor(sensor);

	for (int i=0; i < NUM_CONNECT_TRIAL && *handle < 0; ++i) {
		LOGD("Trial #%d to connect to Sensor %d", i+1, sensor);
		*handle = sensord_connect(sen);
	}

	try_return_result_tag(*handle>=0, CERR_NOT_SUPPORTED, SLOGE, "Failed to connect Sensor %d", sensor);

	bool supported = false;
	try_return_result_tag(sensord_is_supported_event_type(sen, event, &supported), CERR_OPERATION_FAILED, SLOGE, "sensord_is_supported_event_type() failed");
	try_return_result_tag(supported, CERR_NOT_SUPPORTED, SLOGD, "Sensor Event %d is not supported.", event);

	if (!sensord_register_event(*handle, event, 0, 0, cb, user_data)) {
		LOGE("Failed to register Sensor Event %d", event);
		sensord_disconnect(*handle);
		*handle = -1;
		return CERR_NOT_SUPPORTED;
	}

	if (!sensord_start(*handle, option)) {
		LOGE("Failed to start Sensor %d", sensor);
		sensord_unregister_event(*handle, event);
		sensord_disconnect(*handle);
		*handle = -1;
		return CERR_OPERATION_FAILED;
	}

	LOGI("Sensor %d (Event %#x) started (Option: %d)", sensor, event, option);
	return CERR_NONE;
}

void ctx::sensor::disconnect(int *handle, sensor_type_t sensor, unsigned int event)
{
	try_return_void(*handle >= 0);

	sensord_unregister_event(*handle, event);
	sensord_stop(*handle);
	sensord_disconnect(*handle);

	*handle = -1;

	LOGI("Sensor %d (Event %#x) stopped", sensor, event);
}
