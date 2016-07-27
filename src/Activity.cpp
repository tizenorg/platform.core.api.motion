/*
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
#include "ActivityProxy.h"

#define FEATURE_ACTIVITY "tizen.org/feature/sensor.activity_recognition"

#define ACTIVITY_FIRST	ACTIVITY_STATIONARY
#define ACTIVITY_LAST	ACTIVITY_IN_VEHICLE
#define IS_VALID_ACTIVITY(X)	(ACTIVITY_FIRST <= (X) && (X) <= ACTIVITY_LAST)

using namespace motion;

struct _activity_handle_s {
	ActivityProxy *proxy;
};

EXTAPI int activity_is_supported(activity_type_e activity, bool* supported)
{
	if (supported)
		*supported = false;

	ASSERT_SUPPORTED(FEATURE_ACTIVITY);
	ASSERT_NOT_NULL(supported);
	IF_FAIL_RETURN(IS_VALID_ACTIVITY(activity), ERR_INVALID_PARAMETER);

	*supported = ActivityProxy::isSupported(activity);
	return ERR_NONE;
}

EXTAPI int activity_create(activity_h *handle)
{
	ASSERT_SUPPORTED(FEATURE_ACTIVITY);
	ASSERT_NOT_NULL(handle);

	_activity_handle_s *hdl = static_cast<activity_h>(malloc(sizeof(_activity_handle_s)));
	IF_FAIL_RETURN_TAG(hdl, ERR_OPERATION_FAILED, _E, "Memory allocation failed");

	hdl->proxy = new(std::nothrow) ActivityProxy();
	if (hdl->proxy == NULL) {
		_E("Memory allocation failed");
		free(hdl);
		return ERR_OPERATION_FAILED;
	}

	*handle = hdl;
	return ERR_NONE;
}

EXTAPI int activity_release(activity_h handle)
{
	ASSERT_SUPPORTED(FEATURE_ACTIVITY);
	ASSERT_NOT_NULL(handle);

	delete handle->proxy;
	free(handle);

	return ERR_NONE;
}

EXTAPI int activity_start_recognition(activity_h handle, activity_type_e activity, activity_recognition_cb callback, void *user_data)
{
	ASSERT_SUPPORTED(FEATURE_ACTIVITY);
	ASSERT_NOT_NULL(handle);
	ASSERT_NOT_NULL(callback);
	IF_FAIL_RETURN(IS_VALID_ACTIVITY(activity), ERR_INVALID_PARAMETER);

	if (!handle->proxy->setActivity(activity)) {
		return ERR_INVALID_PARAMETER;
	}

	handle->proxy->setPowerSave(false);
	handle->proxy->setCb(callback);
	handle->proxy->setUserData(user_data);

	if (!handle->proxy->start()) {
		return ERR_OPERATION_FAILED;
	}

	return ERR_NONE;
}

EXTAPI int activity_stop_recognition(activity_h handle)
{
	ASSERT_SUPPORTED(FEATURE_ACTIVITY);
	ASSERT_NOT_NULL(handle);

	IF_FAIL_RETURN(handle->proxy->stop(), ACTIVITY_ERROR_NOT_STARTED);

	return ERR_NONE;
}

EXTAPI int activity_get_accuracy(const activity_data_h data, activity_accuracy_e *accuracy)
{
	ASSERT_SUPPORTED(FEATURE_ACTIVITY);
	ASSERT_NOT_NULL(data);
	ASSERT_NOT_NULL(accuracy);

	*accuracy = static_cast<activity_accuracy_e>(data->accuracy);

	return ERR_NONE;
}
