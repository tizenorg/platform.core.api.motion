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

#include <stdlib.h>
#include <ctx_error.h>
#include <ctx_util_misc.h>
#include <ctx_types_private.h>
#include <handle_map.h>
#include "motion_engine.h"
#include "gesture.h"

static ctx::handle_map_t<_cx_gesture_h> handle_map;

void cx_gesture_deliver_data(int req_id, _cx_gesture_data data, double timestamp, int error)
{
	_cx_gesture_h *handle = NULL;

	handle = handle_map.get_copy(req_id);
	try_return_void_tag(handle, LOGD, "No matching handle found");

	if (handle->callback) {
		data.gesture = handle->gesture;
		handle->callback(static_cast<gesture_type_e>(data.gesture), &data,
				timestamp, static_cast<gesture_error_e>(error), handle->user_data);
	}

	free(handle);
}

EXTAPI int gesture_is_supported(gesture_type_e gesture, bool* supported)
{
	if (supported)
		*supported = false;

	ASSERT_SUPPORTED(FEATURE_KEY_GESTURE);
	ASSERT_NULL(supported);

	if (!ctx::gesture::me_check_coverage(gesture))
		return GESTURE_ERROR_NONE;

	int ret = ctx::gesture::me_is_supported(gesture);
	if (ret == GESTURE_ERROR_NONE)
		*supported = true;

	return GESTURE_ERROR_NONE;
}

EXTAPI int gesture_create(gesture_h *handle)
{
	ASSERT_SUPPORTED(FEATURE_KEY_GESTURE);
	ASSERT_HANDLE;

	*handle = static_cast<gesture_h>(malloc(sizeof(_cx_gesture_h)));
	ASSERT_ALLOC(*handle);

	(*handle)->req_id		= CTX_VALUE_UNDEFINED;
	(*handle)->gesture		= CTX_VALUE_UNDEFINED;
	(*handle)->callback		= NULL;
	(*handle)->user_data	= NULL;

	(*handle)->me_handle	= CTX_VALUE_UNDEFINED;
	(*handle)->me_event		= CTX_VALUE_UNDEFINED;

	return GESTURE_ERROR_NONE;
}

EXTAPI int gesture_release(gesture_h handle)
{
	ASSERT_SUPPORTED(FEATURE_KEY_GESTURE);
	ASSERT_HANDLE;
	gesture_stop_recognition(handle);
	free(handle);
	return GESTURE_ERROR_NONE;
}

EXTAPI int gesture_start_recognition(gesture_h handle, gesture_type_e gesture, gesture_option_e option, gesture_recognition_cb callback, void *user_data)
{
	ASSERT_SUPPORTED(FEATURE_KEY_GESTURE);
	if (gesture == GESTURE_WRIST_UP) {
		ASSERT_SUPPORTED(FEATURE_KEY_WRISTUP);
	}
	ASSERT_HANDLE;
	ASSERT_NULL(callback);

	if (handle_map.find(handle->req_id) != NULL) {
		LOGW("The handle is being used");
		return GESTURE_ERROR_ALREADY_STARTED;
	}

	handle->gesture		= gesture;
	handle->user_data	= user_data;
	handle->callback	= callback;

	int ret;

	if (ctx::gesture::me_check_coverage(gesture)) {
		ret = ctx::gesture::me_start(handle, gesture, option);
	} else {
		ret = GESTURE_ERROR_INVALID_PARAMETER;
	}

	if (ret == GESTURE_ERROR_NONE)
		handle_map.insert(handle->req_id, handle);

	return ret;
}

EXTAPI int gesture_stop_recognition(gesture_h handle)
{
	ASSERT_SUPPORTED(FEATURE_KEY_GESTURE);
	ASSERT_HANDLE;
	int ret = GESTURE_ERROR_NOT_STARTED;

	if (handle_map.find(handle->req_id) != NULL) {
		if (ctx::gesture::me_check_coverage(handle->gesture))
			ctx::gesture::me_stop(handle);

		handle_map.remove(handle->req_id);
		ret = GESTURE_ERROR_NONE;
	}

	handle->req_id		= CTX_VALUE_UNDEFINED;
	handle->gesture		= CTX_VALUE_UNDEFINED;
	handle->callback	= NULL;
	handle->user_data	= NULL;

	return ret;
}

EXTAPI int gesture_get_event(const gesture_data_h data, gesture_event_e *event)
{
	ASSERT_SUPPORTED(FEATURE_KEY_GESTURE);
	ASSERT_NULL(data);
	ASSERT_NULL(event);

	if (data->gesture == GESTURE_TILT)
		return GESTURE_ERROR_NOT_SUPPORTED;

	*event = static_cast<gesture_event_e>(data->event);

	return GESTURE_ERROR_NONE;
}

EXTAPI int gesture_get_tilt(const gesture_data_h data, int *x, int *y)
{
	ASSERT_SUPPORTED(FEATURE_KEY_GESTURE);
	ASSERT_NULL(data);
	ASSERT_NULL(x);
	ASSERT_NULL(y);

	if (data->gesture != GESTURE_TILT)
		return GESTURE_ERROR_NOT_SUPPORTED;

	*x = data->tilt_x;
	*y = data->tilt_y;

	return GESTURE_ERROR_NONE;
}
