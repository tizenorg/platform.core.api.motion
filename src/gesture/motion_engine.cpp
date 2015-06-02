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
#include <ctx_types_private.h>
#include <ctx_util_misc.h>
#include <ctx_util_sensor.h>
#include "gesture.h"
#include "motion_engine.h"

static int convert_shake_data(int value)
{
	switch (value) {
	case MOTION_ENGIEN_SHAKE_NONE:
		return GESTURE_EVENT_NONE;

	case MOTION_ENGIEN_SHAKE_DETECTION:
	case MOTION_ENGIEN_SHAKE_CONTINUING:
		return GESTURE_SHAKE_DETECTED;

	case MOTION_ENGIEN_SHAKE_FINISH:
	case MOTION_ENGINE_SHAKE_BREAK:
		return GESTURE_SHAKE_FINISHED;

	default:
		return CTX_VALUE_UNDEFINED;
	}
}

static int convert_face_down_data(int value)
{
	switch (value) {
	case MOTION_ENGIEN_TOP_TO_BOTTOM_NONE:
		return GESTURE_EVENT_NONE;

	case MOTION_ENGIEN_TOP_TO_BOTTOM_DETECTION:
		return GESTURE_EVENT_DETECTED;

	default:
		return CTX_VALUE_UNDEFINED;
	}
}

static void me_sensor_event_extract_int(unsigned int event_type, sensor_data_t *event_data, _cx_gesture_data *gesture_data)
{
	gesture_data->event  = event_data->values[0];

	switch (event_type) {
		case MOTION_ENGINE_EVENT_SHAKE:
		case MOTION_ENGINE_EVENT_SHAKE_ALWAYS_ON:
			gesture_data->event = convert_shake_data(gesture_data->event);
			return;

		case MOTION_ENGINE_EVENT_TOP_TO_BOTTOM:
			gesture_data->event = convert_face_down_data(gesture_data->event);
			return;

		default:
			return;
	}
}

static void me_sensor_event_extract_tilt(sensor_data_t *event_data, _cx_gesture_data *gesture_data)
{
	try_return_void_tag(event_data->value_count >= 2, LOGW, "Invalid data count (%d)", event_data->value_count);
	gesture_data->tilt_x = event_data->values[0];
	gesture_data->tilt_y = event_data->values[1];
}

static bool me_sensor_extract_data(unsigned int event_type, sensor_data_t *event_data, _cx_gesture_data *gesture_data)
{
	if (event_type == MOTION_ENGINE_EVENT_TILT) {
		me_sensor_event_extract_tilt(event_data, gesture_data);

	} else {
		me_sensor_event_extract_int(event_type, event_data, gesture_data);
	}

	return true;
}

static void me_sensor_event_cb(sensor_t sensor, unsigned int sensor_event_type, sensor_data_t *sensor_event_data, void *user_data)
{
	try_return_void(user_data);

	int64_t ts = ctx::time::get_utc(NULL, NULL);
	int req_id = (int)user_data;
	LOGD("Received data for ReqId %d", req_id);

	_cx_gesture_data data;

	if (!me_sensor_extract_data(sensor_event_type, sensor_event_data, &data)) {
		LOGE("Failed to extract motion data from sensor event");
		return;
	}

	cx_gesture_deliver_data(req_id, data, ts/1000.0L, GESTURE_ERROR_NONE);
}

static int get_event_type(int motion)
{
	switch (motion) {
	// Mobile Lite Profile
	case GESTURE_SHAKE:
		return MOTION_ENGINE_EVENT_SHAKE;

	// Mobile Full Profile
	case GESTURE_DOUBLE_TAP:
		return MOTION_ENGINE_EVENT_DOUBLETAP;

	case GESTURE_MOVE_TO_EAR:
		return MOTION_ENGINE_EVENT_DIRECT_CALL;

	case GESTURE_NO_MOVE:
		return MOTION_ENGINE_EVENT_NO_MOVE;

	case GESTURE_PICK_UP:
		return MOTION_ENGINE_EVENT_SMART_RELAY;

	case GESTURE_SNAP:
		return MOTION_ENGINE_EVENT_SNAP;

	case GESTURE_TILT:
		return MOTION_ENGINE_EVENT_TILT;

	case GESTURE_TURN_FACE_DOWN:
		return MOTION_ENGINE_EVENT_TOP_TO_BOTTOM;

	default:
		return CTX_VALUE_UNDEFINED;
	}
}

static int get_me_option(int mode)
{
	if (mode == GESTURE_OPTION_DEFAULT) {
		return SENSOR_OPTION_DEFAULT;

	} else if (mode == GESTURE_OPTION_ALWAYS_ON) {
		return SENSOR_OPTION_ALWAYS_ON;
	}

	return CTX_VALUE_UNDEFINED;
}

bool ctx::gesture::me_check_coverage(int motion)
{
	switch (motion) {
	case GESTURE_SHAKE:
	case GESTURE_DOUBLE_TAP:
	case GESTURE_MOVE_TO_EAR:
	case GESTURE_NO_MOVE:
	case GESTURE_PICK_UP:
	case GESTURE_SNAP:
	case GESTURE_TILT:
	case GESTURE_TURN_FACE_DOWN:
		return true;

	default:
		return false;
	}
}

int ctx::gesture::me_is_supported(int motion)
{
	int handle = -1, res;
	int ev_type	= get_event_type(motion);
	res = ctx::sensor::connect(&handle, MOTION_SENSOR, ev_type, SENSOR_OPTION_DEFAULT, me_sensor_event_cb, NULL);
	ctx::sensor::disconnect(&handle, MOTION_SENSOR, ev_type);

	return res;
}

int ctx::gesture::me_start(_cx_gesture_h *handle, int gesture, int option)
{
	int req_id	= ctx::generate_rid();
	int ev_type	= get_event_type(gesture);
	int me_opt	= get_me_option(option);

	try_return_result(me_opt != CTX_VALUE_UNDEFINED, GESTURE_ERROR_INVALID_PARAMETER);

	int res = ctx::sensor::connect(&handle->me_handle, MOTION_SENSOR, ev_type, me_opt, me_sensor_event_cb, (void*)req_id);
	try_return_result(!IS_FAILED(res), res);

	LOGI("Started MotionEngine Event %d (Gesture %d)", ev_type, gesture);

	handle->req_id		= req_id;
	handle->me_event	= ev_type;

	return GESTURE_ERROR_NONE;
}

int ctx::gesture::me_stop(_cx_gesture_h *handle)
{
	LOGI("Stopping MotionEngine Event %d", handle->me_event);

	ctx::sensor::disconnect(&handle->me_handle, MOTION_SENSOR, handle->me_event);

	handle->me_handle	= CTX_VALUE_UNDEFINED;
	handle->me_event	= CTX_VALUE_UNDEFINED;

	return GESTURE_ERROR_NONE;
}
