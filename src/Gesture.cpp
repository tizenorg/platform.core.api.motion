/*
 * motion
 *
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
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
#include "GestureProxy.h"

#define FEATURE_GESTURE "tizen.org/feature/sensor.gesture_recognition"

using namespace motion;

struct _gesture_handle_s {
	GestureProxy *proxy;
};

EXTAPI int gesture_is_supported(gesture_type_e gesture, bool* supported)
{
	if (supported)
		*supported = false;

	ASSERT_SUPPORTED(FEATURE_GESTURE);
	ASSERT_NOT_NULL(supported);

	*supported = GestureProxy::isSupported(gesture);
	return ERR_NONE;
}

EXTAPI int gesture_create(gesture_h *handle)
{
	ASSERT_SUPPORTED(FEATURE_GESTURE);
	ASSERT_NOT_NULL(handle);

	_gesture_handle_s *hdl = static_cast<gesture_h>(malloc(sizeof(_gesture_handle_s)));
	IF_FAIL_RETURN_TAG(hdl, ERR_OPERATION_FAILED, _E, "Memory allocation failed");

	hdl->proxy = new(std::nothrow) GestureProxy();
	if (hdl->proxy == NULL) {
		_E("Memory allocation failed");
		free(hdl);
		return ERR_OPERATION_FAILED;
	}

	*handle = hdl;
	return ERR_NONE;
}

EXTAPI int gesture_release(gesture_h handle)
{
	ASSERT_SUPPORTED(FEATURE_GESTURE);
	ASSERT_NOT_NULL(handle);

	delete handle->proxy;
	free(handle);

	return ERR_NONE;
}

EXTAPI int gesture_start_recognition(gesture_h handle, gesture_type_e gesture, gesture_option_e option, gesture_recognition_cb callback, void *user_data)
{
	ASSERT_SUPPORTED(FEATURE_GESTURE);
	ASSERT_NOT_NULL(handle);
	ASSERT_NOT_NULL(callback);

	if (!handle->proxy->setGesture(gesture)) {
		return ERR_INVALID_PARAMETER;
	}

	if (option == GESTURE_OPTION_DEFAULT) {
		handle->proxy->setPowerSave(true);
	} else if (option == GESTURE_OPTION_ALWAYS_ON) {
		handle->proxy->setPowerSave(false);
	} else {
		return ERR_INVALID_PARAMETER;
	}

	handle->proxy->setCb(callback);
	handle->proxy->setUserData(user_data);

	if (!handle->proxy->start()) {
		return ERR_OPERATION_FAILED;
	}

	return ERR_NONE;
}

EXTAPI int gesture_stop_recognition(gesture_h handle)
{
	ASSERT_SUPPORTED(FEATURE_GESTURE);
	ASSERT_NOT_NULL(handle);
	handle->proxy->stop();
	return ERR_NONE;
}

EXTAPI int gesture_get_event(const gesture_data_h data, gesture_event_e *event)
{
	ASSERT_SUPPORTED(FEATURE_GESTURE);
	ASSERT_NOT_NULL(data);
	ASSERT_NOT_NULL(event);

	if (data->gesture == GESTURE_TILT)
		return GESTURE_ERROR_NOT_SUPPORTED;

	*event = static_cast<gesture_event_e>(data->event);

	return ERR_NONE;
}

EXTAPI int gesture_get_tilt(const gesture_data_h data, int *x, int *y)
{
	ASSERT_SUPPORTED(FEATURE_GESTURE);
	ASSERT_NOT_NULL(data);
	ASSERT_NOT_NULL(x);
	ASSERT_NOT_NULL(y);

	if (data->gesture != GESTURE_TILT)
		return ERR_NOT_SUPPORTED;

	*x = data->tilt_x;
	*y = data->tilt_y;

	return ERR_NONE;
}
